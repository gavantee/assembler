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
  struct Node *node;
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
%type <node> instruction
%type <ival> instr_0 instr_jmp instr_1 instr_2
%type <ival> lit
%type <str_list> sym_list
%start program

%%
program:
	label_inst_dir
	| label_inst_dir program;

label_inst_dir:
	label
	| inst_dir
	| label inst_dir;

label:
     SYMBOL COLON { cout << "labela: " << $1 << endl;};

inst_dir:
	instruction
	| directive;

directive:
	GLOBAL sym_list { cout << "GLOBAL" << endl;
			  for (string s : *($2))
			  	cout << s << endl; }
	| EXTERN sym_list
	| SECTION SYMBOL { cout << "SEKCIJA " << $2 << endl; }
	| WORD sym_lit_list
	| SKIP lit
	| EQU SYMBOL COMMA lit
	| END;

instruction:
	instr_0
	| instr_jmp operand_jmp
	| instr_1 REG
	| instr_2 REG COMMA REG
	| inst_ldr_str REG COMMA operand;

instr_0:
	HALT
	| IRET
	| RET;

instr_jmp:
	CALL
	| JMP
	| JEQ
	| JNE
	| JGT;

instr_1:
	PUSH
	| POP
	| INT;

instr_2:
       XCHG { $$ = 0; cout << "XCHG"; }
       | MOV { $$ = 1; cout << "MOV"; }
       | ADD { $$ = 2; cout << "ADD"; }
       | SUB
       | MUL
       | DIV
       | CMP
       | NOT
       | AND
       | OR
       | XOR
       | TEST
       | SHL
       | SHR;

inst_ldr_str:
	LDR
	| STR;

operand_jmp:
	lit
	| SYMBOL
	| PERCENT SYMBOL
	| TIMES lit
	| TIMES SYMBOL
	| TIMES REG
	| TIMES LPAREN REG RPAREN
	| TIMES LPAREN REG PLUS lit RPAREN
	| TIMES LPAREN REG PLUS SYMBOL RPAREN;

operand:
       	DOLLAR lit
	| DOLLAR SYMBOL
	| lit
	| SYMBOL
	| PERCENT SYMBOL
	| TIMES lit
	| TIMES SYMBOL
	| REG
	| LPAREN REG RPAREN
	| LPAREN REG PLUS lit RPAREN
	| LPAREN REG PLUS SYMBOL RPAREN;

sym_list:
	SYMBOL { $$ = new vector<string>();
		 $$->push_back($1);}
	| sym_list COMMA SYMBOL;

lit: NUMBER {$$ = $1; cout << $1 << endl;};

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

void yyerror(const char *s) {
  cout << "Parse error";
  exit(-1);
}
