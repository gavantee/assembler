/* A Bison parser, made by GNU Bison 3.7.6.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_INC_BISON_HPP_INCLUDED
# define YY_YY_INC_BISON_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    NUMBER = 258,                  /* NUMBER  */
    PLUS = 259,                    /* PLUS  */
    MINUS = 260,                   /* MINUS  */
    COLON = 261,                   /* COLON  */
    COMMA = 262,                   /* COMMA  */
    LPAREN = 263,                  /* LPAREN  */
    RPAREN = 264,                  /* RPAREN  */
    TIMES = 265,                   /* TIMES  */
    DOLLAR = 266,                  /* DOLLAR  */
    PERCENT = 267,                 /* PERCENT  */
    REG = 268,                     /* REG  */
    HALT = 269,                    /* HALT  */
    IRET = 270,                    /* IRET  */
    RET = 271,                     /* RET  */
    CALL = 272,                    /* CALL  */
    JMP = 273,                     /* JMP  */
    JEQ = 274,                     /* JEQ  */
    JNE = 275,                     /* JNE  */
    JGT = 276,                     /* JGT  */
    PUSH = 277,                    /* PUSH  */
    POP = 278,                     /* POP  */
    INT = 279,                     /* INT  */
    XCHG = 280,                    /* XCHG  */
    MOV = 281,                     /* MOV  */
    ADD = 282,                     /* ADD  */
    SUB = 283,                     /* SUB  */
    MUL = 284,                     /* MUL  */
    DIV = 285,                     /* DIV  */
    CMP = 286,                     /* CMP  */
    NOT = 287,                     /* NOT  */
    AND = 288,                     /* AND  */
    OR = 289,                      /* OR  */
    XOR = 290,                     /* XOR  */
    TEST = 291,                    /* TEST  */
    SHL = 292,                     /* SHL  */
    SHR = 293,                     /* SHR  */
    LDR = 294,                     /* LDR  */
    STR = 295,                     /* STR  */
    GLOBAL = 296,                  /* GLOBAL  */
    EXTERN = 297,                  /* EXTERN  */
    SECTION = 298,                 /* SECTION  */
    WORD = 299,                    /* WORD  */
    SKIP = 300,                    /* SKIP  */
    EQU = 301,                     /* EQU  */
    END = 302,                     /* END  */
    SYMBOL = 303                   /* SYMBOL  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 24 "src/parser.y"

  int ival;
  char *sval;
  std::vector<std::string> *str_list;
	long long lval;
	struct Op *op;

#line 120 "inc/bison.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_INC_BISON_HPP_INCLUDED  */
