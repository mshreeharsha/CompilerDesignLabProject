
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TYPE = 258,
     INTEGER = 259,
     STRING = 260,
     FLOATING_NUM = 261,
     CHAR_CONST = 262,
     STRUCT = 263,
     UNION = 264,
     VOID = 265,
     ID = 266,
     FUN_START = 267,
     INCLUDE = 268,
     PREDEF_HEADER = 269,
     ELIF = 270,
     ELSE = 271,
     IF = 272,
     BREAK = 273,
     NOT = 274,
     FOR = 275,
     CONTINUE = 276,
     WHILE = 277,
     SWITCH = 278,
     CASE = 279,
     RETURN = 280,
     SL_COMMENT = 281,
     ML_COMMENT = 282,
     EQUALTO = 283,
     OPEN_BRACK = 284,
     OPEN_FLOWER = 285,
     OPEN_SQ = 286,
     CLOSE_BRACK = 287,
     CLOSE_FLOWER = 288,
     CLOSE_SQ = 289,
     AND = 290,
     UNARY_OP = 291,
     PLUS = 292,
     MINUS = 293,
     DIV = 294,
     MUL = 295,
     MOD = 296,
     OR = 297,
     AMPERSAND = 298,
     BIT_OR = 299,
     BIT_XOR = 300,
     SEMICOLON = 301,
     COMMA = 302,
     ISEQUALTO = 303,
     LT = 304,
     LTE = 305,
     GT = 306,
     GTE = 307,
     NE = 308,
     PLUS_ET = 309,
     MINUS_ET = 310,
     MUL_ET = 311,
     DIV_ET = 312,
     OR_ET = 313,
     AND_ET = 314,
     XOR_ET = 315,
     PRINTF = 316,
     SCANF = 317,
     MAIN = 318,
     COLON = 319,
     DEFAULT = 320,
     MALLOC = 321,
     SIZEOF = 322,
     TYPEDEF = 323,
     DOT = 324,
     ARROW = 325
   };
#endif
/* Tokens.  */
#define TYPE 258
#define INTEGER 259
#define STRING 260
#define FLOATING_NUM 261
#define CHAR_CONST 262
#define STRUCT 263
#define UNION 264
#define VOID 265
#define ID 266
#define FUN_START 267
#define INCLUDE 268
#define PREDEF_HEADER 269
#define ELIF 270
#define ELSE 271
#define IF 272
#define BREAK 273
#define NOT 274
#define FOR 275
#define CONTINUE 276
#define WHILE 277
#define SWITCH 278
#define CASE 279
#define RETURN 280
#define SL_COMMENT 281
#define ML_COMMENT 282
#define EQUALTO 283
#define OPEN_BRACK 284
#define OPEN_FLOWER 285
#define OPEN_SQ 286
#define CLOSE_BRACK 287
#define CLOSE_FLOWER 288
#define CLOSE_SQ 289
#define AND 290
#define UNARY_OP 291
#define PLUS 292
#define MINUS 293
#define DIV 294
#define MUL 295
#define MOD 296
#define OR 297
#define AMPERSAND 298
#define BIT_OR 299
#define BIT_XOR 300
#define SEMICOLON 301
#define COMMA 302
#define ISEQUALTO 303
#define LT 304
#define LTE 305
#define GT 306
#define GTE 307
#define NE 308
#define PLUS_ET 309
#define MINUS_ET 310
#define MUL_ET 311
#define DIV_ET 312
#define OR_ET 313
#define AND_ET 314
#define XOR_ET 315
#define PRINTF 316
#define SCANF 317
#define MAIN 318
#define COLON 319
#define DEFAULT 320
#define MALLOC 321
#define SIZEOF 322
#define TYPEDEF 323
#define DOT 324
#define ARROW 325




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 415 ".\\semanticAnalysis.y"

    char * value;
    char * type;



/* Line 1676 of yacc.c  */
#line 199 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


