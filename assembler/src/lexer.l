%{
  #include <iostream>
	#include <string>
	#include <vector>

	#include "bison.hpp"

	using namespace std;

	extern int yylex();
%}

%option noyywrap

digit         [0-9]
letter        [a-zA-Z_]
hex 0[xX][0-9a-fA-F]+
comment #.*\n

%%
"+"						{ return PLUS;			}
"-"						{ return MINUS;		  }
":"						{ return COLON;   	}
","						{ return COMMA;   	}
"["						{ return LPAREN;  	}
"]"						{ return RPAREN;  	}
"*"           { return TIMES;	  	}
"$"           { return DOLLAR;  	}
"%"           { return PERCENT; 	}
".global"     { return GLOBAL;  	}
".extern"     { return EXTERN;  	}
".section"    { return SECTION; 	}
".word"       { return WORD;    	}
".skip"       { return SKIP;    	}
".equ"        { return EQU;     	}
".end"        { return END;     	}
"halt"        { return HALT;    	}
"int"					{ return INT; 			}
"iret"				{ return IRET; 			}
"call"				{ return CALL; 			}
"ret"					{ return RET; 			}
"jmp"					{ return JMP; 			}
"jeq"					{ return JEQ; 			}
"jne"					{ return JNE; 			}
"jgt"					{ return JGT; 			}
"push" 				{ return PUSH;			}
"pop"					{ return POP;				}
"xchg"				{ return XCHG;			}
"add"					{ return ADD;				}
"sub"					{ return SUB;				}
"mul" 				{ return MUL;				}
"div"					{ return DIV; 			}
"cmp"					{ return CMP;				}
"not"					{ return NOT;				}
"and"					{ return AND;				}
"or"					{ return OR;				}
"xor"					{ return XOR;				}
"test"				{ return TEST;			}
"shl"					{ return SHL;				}
"shr"					{ return SHR;				}
"ldr"					{ return LDR;				}
"str"					{ return STR;				}
(r[0-7])			{ yylval.ival = atoi(yytext + 1);
							 	return REG; 	  	}
(pc|PC)				{ yylval.ival = 7;
								return REG;				}
(sp|SP)				{ yylval.ival = 6;
								return REG;				}
(PSW|psw)			{ yylval.ival = 8;
								return REG;				}
{letter}({letter}|{digit})* {
								yylval.sval = strdup(yytext);
                return SYMBOL;  	}
{digit}+      { yylval.ival = atoi(yytext);
                return NUMBER;    }
{hex}         { yylval.ival = stoi(yytext, nullptr, 16);
								return NUMBER;		}
{comment}
[ \t\n\r]     /* skip whitespace */
.             { printf("Unknown character [%c]\n", yytext[0]);}
%%
/*
int main(int, char**) {

  // open a file handle to a particular file:
  FILE *myfile = fopen("test.s", "r");
  // make sure it's valid:
  if (!myfile) {
    cout << "can't open file" << endl;
    return -1;
  }
  // set lex to read from it instead of defaulting to STDIN:
  yyin = myfile;

  // lex through the input:
  while(yylex());
}
*/
