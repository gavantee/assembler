%{
  #include <cstdio>
  #include <iostream>
  #include <string>
  #include <vector>
  #include <cstring>

  #include "parser.h"
  #include "code.h"

  using namespace std;

  extern int yylex();
  extern int yyparse();
  extern FILE *yyin;

  int pc = 0;
  extern Code code;
  string section = "NO_SEC";

  void yyerror(const char *s);
	unsigned short reverse_bytes(unsigned short i);
%}

%union {
  int ival;
  char *sval;
  std::vector<std::string> *str_list;
	long long lval;
	struct Op *op;
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
%type <ival> instr_0 instr_jmp instr_1 instr_2 instr_mem
%type <op> operand operand_jmp
%type <ival> lit
%type <str_list> sym_list
%type <str_list> sym_lit_list
%type <sval> sym_lit
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
     SYMBOL COLON { code.addSymbol($1, section, pc); };

inst_dir:
	instruction
	| directive;

directive:
	GLOBAL sym_list {
			  for (string s : *($2))
			  	code.addSymbol(s, section, new vector<Location>(), true); }
	| EXTERN sym_list {
			    for (string s : *($2)) {
			      code.addSymbol(s, "EXT", new vector<Location>(), true); }}
	| SECTION SYMBOL { pc = 0;
	                   section = $2;
	                   code.addSymbol($2, section, pc, true);}
	| WORD sym_lit_list {
		for (string s : *($2)) {
		  int tmp;
		  if (s[0] >= '0' && s[0] <= '9') tmp = stoi(s, nullptr, 0);
		  else tmp = code.resolveSymbol(s, section, pc);
		  pc += 2;
		  code.addInt(tmp, 2);
		}
	}
	| SKIP lit { pc += $2; code.addInt(0, $2); }
	| EQU SYMBOL COMMA lit { code.addSymbol($2, "ABS", $4); }
	| END;

instruction:
	instr_0 { code.addByte($1);
		pc += 1; }
	| instr_jmp operand_jmp { code.addByte($1);
    code.addInt($2->val, $2->length);
		pc += 1 + $2->length; }
	| instr_1 REG { code.addByte($1);
		code.addByte(($2 << 4) + 0xF);
		pc += 2; }
	| instr_2 REG COMMA REG { code.addByte($1);
		code.addByte(($2 << 4) + $4);
		pc += 2; }
	| instr_mem REG COMMA operand { code.addByte($1);
		int tmp = ($2 << ($4->length * 8 - 4)) + $4->val;
		code.addInt(tmp, $4->length);
		pc += $4->length + 1; }
	| PUSH REG { code.addByte(0xB0);
		     code.addByte(($2 << 4) + 6);
		     code.addByte((1 << 4) + 2);
		     pc += 3; }
	| POP REG  { code.addByte(0xA0);
		     code.addByte(($2 << 4) + 6);
		     code.addByte((4 << 4) + 2);
		     pc += 3; };

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

instr_1: INT 	{ $$ = 0x10; }
       | NOT	{ $$ = 0x80; };

instr_2:
       XCHG  	{ $$ = 0x60; }
       | ADD 	{ $$ = 0x70; }
       | SUB 	{ $$ = 0x71; }
       | MUL	{ $$ = 0x72; }
       | DIV	{ $$ = 0x73; }
       | CMP	{ $$ = 0x74; }
       | AND	{ $$ = 0x81; }
       | OR	  { $$ = 0x82; }
       | XOR	{ $$ = 0x83; }
       | TEST	{ $$ = 0x84; }
       | SHL	{ $$ = 0x90; }
       | SHR	{ $$ = 0x91; };

instr_mem:
	LDR	  { $$ = 0xA0; }
	| STR	{ $$ = 0xB0; };

operand_jmp:
	lit { $$ = new Op((0xF << 28) + (0 << 16) + reverse_bytes($1), 4) ;}
	| SYMBOL { $$ = new Op((0xF << 28) + (0 << 16) + reverse_bytes(code.resolveSymbol($1, section, pc + 3)), 4); }
	| PERCENT SYMBOL { $$ = new Op((0xF << 28) + (7 << 24) + (5 << 16) + reverse_bytes(- 2 + code.resolveSymbol($2, section, pc + 3, true) & 0xffff), 4); }
	| TIMES lit { $$ = new Op((0xF << 28) + (4 << 16) + reverse_bytes($2), 4); }
	| TIMES SYMBOL { $$ = new Op((0xF << 28) + (4 << 16) + reverse_bytes(code.resolveSymbol($2, section, pc + 3)), 4); }
	| TIMES REG { $$ = new Op((0xF << 12) + ($2 << 8) + (1 << 0), 2); }
	| TIMES LPAREN REG RPAREN { $$ = new Op((0xF << 12) + ($3 << 8) + (2 << 0), 2); }
	| TIMES LPAREN REG lit RPAREN { $$ = new Op((0xF << 28) + ($3 << 24) + (3 << 16) + reverse_bytes($4), 4); }
	| TIMES LPAREN REG PLUS SYMBOL RPAREN { $$ = new Op((0xF << 28) + ($3 << 24) + (3 << 16) + reverse_bytes(code.resolveSymbol($5, section, pc + 3)), 4); };

operand:
       	DOLLAR lit { $$ = new Op(reverse_bytes($2), 4); }
  | DOLLAR SYMBOL { $$ = new Op(reverse_bytes(code.resolveSymbol($2, section, pc + 3)), 4); }
  | lit { $$ = new Op((4 << 16) + reverse_bytes($1), 4); }
	| SYMBOL { $$ = new Op((4 << 16) + reverse_bytes(code.resolveSymbol($1, section, pc + 3)), 4); }
	| PERCENT SYMBOL { $$ = new Op((7 << 24) + (3 << 16)  + reverse_bytes(- 2 + code.resolveSymbol($2, section, pc + 3, true) & 0xffff), 4); }
	| REG { $$ = new Op(($1 << 8) + (1 << 0), 2); }
	| LPAREN REG RPAREN { $$ = new Op(($2 << 8) + (2 << 0), 2); }
	| LPAREN REG lit RPAREN { $$ = new Op(($2 << 24) + (3 << 16) + reverse_bytes($3), 4); }
	| LPAREN REG PLUS SYMBOL RPAREN { $$ = new Op(($2 << 24) + (3 << 16) + reverse_bytes(code.resolveSymbol($4, section, pc + 3)), 4); }

sym_list:
	SYMBOL { $$ = new vector<string>();
		 $$->push_back($1); }
	| sym_list COMMA SYMBOL { $$->push_back($3); };

lit: NUMBER { $$ = $1; if ($1 > 0xffff) {
	 printf("number %d too large\n", $1);
	 exit(1); }}
	 | PLUS NUMBER { $$ = $2; }
	 | MINUS NUMBER { $$ = (1 << 16) - $2; };

sym_lit:
	SYMBOL { $$ = $1; }
	| lit  { $$ = (char *) calloc(7, sizeof(char));
		 snprintf($$, 6, "%d", $1);
		 $$[6] = '\0'; };

sym_lit_list:
	sym_lit { $$ = new vector<string>();
		  $$->push_back($1); }
	| sym_lit_list COMMA sym_lit {$$->push_back($3); };

%%

unsigned short reverse_bytes(unsigned short i) {
  return ((i & 0xff) << 8) + ((i & 0xff00) >> 8);
}
void yyerror(const char *s) {
  cout << "Parse error:" << s << endl;
  exit(-1);
}
