%{
  #include <cstdio>
  #include <iostream>
  #include <string>
  #include <vector>

  #include "parser.h"

  using namespace std;

  // Declare stuff from Flex that Bison needs to know about:
  extern int yylex();
  extern int yyparse();
  extern FILE *yyin;

  int pc = 0;
  std::vector<char> *code = new std::vector<char>();
  void push_back(std::vector<char> *v, int bytes, int size);

  void yyerror(const char *s);
%}

// Bison fundamentally works by asking flex to get the next token, which it
// returns as an object of type "yystype".  Initially (by default), yystype
// is merely a typedef of "int", but for non-trivial projects, tokens could
// be of any arbitrary data type.  So, to deal with that, the idea is to
// override yystype's default typedef to be a C union instead.  Unions can
// hold all of the types of tokens that Flex could return, and this this means
// we can return ints or floats or strings cleanly.  Bison implements this
// mechanism with the %union directive:
%union {
  int ival;
  char *sval;
  std::vector<std::string> *str_list;
}

%token <ival> NUMBER
%token PLUS MINUS COLON COMMA LPAREN RPAREN TIMES DOLLAR PERCENT
%token <ival> REG
%token HALT IRET RET
%token CALL JMP JEQ JNE JGT
%token PUSH POP INT
%token XCHG MOV ADD SUB MUL DIV CMP NOT AND OR XOR TEST SHL SHR
%token LDR STR
%token GLOBAL EXTERN SECTION WORD SKIP EQU END
%token <sval> SYMBOL
%type <sval> instruction
%type <ival> instr_0 instr_jmp instr_1 instr_2 instr_mem
%type <ival> operand operand_jmp lit
%type <str_list> sym_list
%start program

%%
program:
	line
	| line program;

line:
	label
	| inst_dir
	| label inst_dir;

label:
     SYMBOL COLON { cout << "labela: " << $1 << endl; };

inst_dir:
	instruction
	| directive;

directive:
	GLOBAL sym_list { cout << "GLOBAL ";
			  for (string s : *($2))
			  	cout << s << endl; }
	| EXTERN sym_list
	| SECTION SYMBOL { cout << "SEKCIJA " << $2 << endl; }
	| WORD sym_lit_list
	| SKIP lit
	| EQU SYMBOL COMMA lit
	| END;

instruction:
	instr_0 { code->push_back($1);
		printf("0x%02X: 0x%02X\n", pc, $1);
		pc += 1; }
	| instr_jmp operand_jmp { code->push_back($1);
		push_back(code, $2, 4);
		printf("0x%02X: 0x%02X 0x%08X\n", pc, $1, $2);
		pc += 5; }
	| instr_1 REG { code->push_back($1);
		code->push_back($2);
		printf("0x%02X: 0x%02X 0x%02X\n", pc, $1, $2);
		pc += 2; }
	| instr_2 REG COMMA REG { code->push_back($1);
		code->push_back(($2 << 4) + $4);
		printf("0x%02X: 0x%02X 0x%02X\n", pc, $1, ($2 << 4) + $4);
		pc += 2; }
	| instr_mem REG COMMA operand { code->push_back($1);
		int tmp = ($2 << 28) + $4;
		push_back(code, tmp, 4);
		printf("0x%02X: 0x%02X 0x%08X\n", pc, $1, tmp);
		pc += 5; };

instr_0:
	HALT  	{ $$ = 0x00; }
	| IRET	{ $$ = 0x20; }
	| RET 	{ $$ = 0x40; }

instr_jmp:
	CALL  	{ $$ = 0x30; }
	| JMP 	{ $$ = 0x50; }
	| JEQ 	{ $$ = 0x51; }
	| JNE 	{ $$ = 0x52; }
	| JGT 	{ $$ = 0x53; };

instr_1:
	PUSH 	{ $$ = 0xC0; }
	| POP	{ $$ = 0xC1; }
	| INT 	{ $$ = 0x10; };

instr_2:
       XCHG  	{ $$ = 0x60; }
       | ADD 	{ $$ = 0x70; }
       | SUB 	{ $$ = 0x71; }
       | MUL	{ $$ = 0x72; }
       | DIV	{ $$ = 0x73; }
       | CMP	{ $$ = 0x74; }
       | NOT	{ $$ = 0x80; }
       | AND	{ $$ = 0x81; }
       | OR	{ $$ = 0x82; }
       | XOR	{ $$ = 0x83; }
       | TEST	{ $$ = 0x84; }
       | SHL	{ $$ = 0x90; }
       | SHR	{ $$ = 0x91; };

instr_mem:
	LDR	{ $$ = 0xA0; }
	| STR	{ $$ = 0xB0; };

operand_jmp:
	lit	{ $$ = $1; }
	| SYMBOL { $$ = 0; }
	| PERCENT SYMBOL { $$ = pc; }
	| TIMES lit { $$ = (4 << 16) + $2; }
	| TIMES SYMBOL { $$ = 4 << 16; }
	| TIMES REG { $$ = ($2 << 24) + (1 << 16); }
	| TIMES LPAREN REG RPAREN { $$ = ($3 << 24) + (2 << 16); }
	| TIMES LPAREN REG lit RPAREN { $$ = ($3 << 24) + (3 << 16) + $4; }
	| TIMES LPAREN REG PLUS SYMBOL RPAREN { $$ = ($3 << 24) + (3 << 16); }

operand:
       	DOLLAR lit { $$ = $2; }
	| DOLLAR SYMBOL { $$ = 0; }
	| lit { $$ = (4 << 16) + $1; }
	| SYMBOL { $$ = 4 << 16; }
	| PERCENT SYMBOL { $$ = pc; }
	| REG { $$ = ($1 << 24) + (1 << 16); }
	| LPAREN REG RPAREN { $$ = ($2 << 24) + (2 << 16); }
	| LPAREN REG lit RPAREN { $$ = ($2 << 24) + (3 << 16) + $3; }
	| LPAREN REG PLUS SYMBOL RPAREN { $$ = ($2 << 24) + (3 << 16); }

sym_list:
	SYMBOL { $$ = new vector<string>();
		 $$->push_back($1); }
	| sym_list COMMA SYMBOL;

lit: NUMBER { $$ = $1; }
   	| PLUS NUMBER { $$ = $2; }
	| MINUS NUMBER { $$ = (1 << 16) - $2; }

sym_lit:
	SYMBOL
	| lit;

sym_lit_list:
	sym_lit
	| sym_lit_list COMMA sym_lit;

%%

/*
int main(int, char**) {
  // Open a file handle to a particular file:
  FILE *myfile = fopen("test.s", "r");
  // Make sure it is valid:
  if (!myfile) {
    return -1;
  }
  // Set Flex to read from it instead of defaulting to STDIN:
  yyin = myfile;

  // Parse through the input:
  yyparse();

}
*/

void push_back(std::vector<char> *v, int bytes, int size) {
  for (int i = size - 1; i >= 0; --i)
    v->push_back(bytes >> (i * 8));
}

void yyerror(const char *s) {
  cout << "Parse error";
  exit(-1);
}
