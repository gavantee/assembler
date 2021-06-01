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
%}

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
%type <ival> instr_0 instr_jmp instr_1 instr_2 instr_mem
%type <ival> operand operand_jmp lit
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
	| EQU SYMBOL COMMA lit {
	code.addSymbol($2, "ABS", $4); }
	| END;

instruction:
	instr_0 { code.addByte($1);
		pc += 1; }
	| instr_jmp operand_jmp { code.addByte($1);
		code.addInt($2, 4);
		pc += 5; }
	| instr_1 REG { code.addByte($1);
		code.addByte($2);
		pc += 2; }
	| instr_2 REG COMMA REG { code.addByte($1);
		code.addByte(($2 << 4) + $4);
		pc += 2; }
	| instr_mem REG COMMA operand { code.addByte($1);
		int tmp = ($2 << 28) + $4;
		code.addInt(tmp, 4);
		pc += 5; }
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

instr_1: INT 	{ $$ = 0x10; };

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
	| SYMBOL { $$ = code.resolveSymbol($1, section, pc + 3); }
	| PERCENT SYMBOL { $$ = (5 << 16) + pc + 5 - code.resolveSymbol($2, section, pc + 3, true); }
	| TIMES lit { $$ = (4 << 16) + $2; }
	| TIMES SYMBOL { $$ = (4 << 16) + code.resolveSymbol($2, section, pc + 3); }
	| TIMES REG { $$ = ($2 << 24) + (1 << 16); }
	| TIMES LPAREN REG RPAREN { $$ = ($3 << 24) + (2 << 16); }
	| TIMES LPAREN REG lit RPAREN { $$ = ($3 << 24) + (3 << 16) + $4; }
	| TIMES LPAREN REG PLUS SYMBOL RPAREN { $$ = ($3 << 24) + (3 << 16) + code.resolveSymbol($5, section, pc + 3); };

operand:
       	DOLLAR lit { $$ = $2; }
	| DOLLAR SYMBOL { $$ = code.resolveSymbol($2, section, pc + 3); }
	| lit { $$ = (4 << 16) + $1; }
	| SYMBOL { $$ = (4 << 16) + code.resolveSymbol($1, section, pc + 3); }
	| PERCENT SYMBOL { $$ = (5 << 16) + (7 << 24) + pc + 5 - code.resolveSymbol($2, section, pc + 3, true); }
	| REG { $$ = ($1 << 24) + (1 << 16); }
	| LPAREN REG RPAREN { $$ = ($2 << 24) + (2 << 16); }
	| LPAREN REG lit RPAREN { $$ = ($2 << 24) + (3 << 16) + $3; }
	| LPAREN REG PLUS SYMBOL RPAREN { $$ = ($2 << 24) + (3 << 16) + code.resolveSymbol($4, section, pc + 3); }

sym_list:
	SYMBOL { $$ = new vector<string>();
		 $$->push_back($1); }
	| sym_list COMMA SYMBOL { $$->push_back($3); };

lit: NUMBER { $$ = $1; }
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
void yyerror(const char *s) {
  cout << "Parse error:" << s << endl;
  exit(-1);
}
