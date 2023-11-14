
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
     ID = 263,
     FUN_START = 264,
     INCLUDE = 265,
     PREDEF_HEADER = 266,
     ELIF = 267,
     ELSE = 268,
     IF = 269,
     BREAK = 270,
     NOT = 271,
     FOR = 272,
     CONTINUE = 273,
     WHILE = 274,
     SWITCH = 275,
     CASE = 276,
     STRUCT = 277,
     UNION = 278,
     RETURN = 279,
     SL_COMMENT = 280,
     ML_COMMENT = 281,
     EQUALTO = 282,
     OPEN_BRACK = 283,
     OPEN_FLOWER = 284,
     OPEN_SQ = 285,
     CLOSE_BRACK = 286,
     CLOSE_FLOWER = 287,
     CLOSE_SQ = 288,
     AND = 289,
     UNARY_OP = 290,
     PLUS = 291,
     MINUS = 292,
     DIV = 293,
     MUL = 294,
     MOD = 295,
     OR = 296,
     AMPERSAND = 297,
     BIT_OR = 298,
     BIT_XOR = 299,
     SEMICOLON = 300,
     COMMA = 301,
     ISEQUALTO = 302,
     LT = 303,
     LTE = 304,
     GT = 305,
     GTE = 306,
     NE = 307,
     PLUS_ET = 308,
     MINUS_ET = 309,
     MUL_ET = 310,
     DIV_ET = 311,
     OR_ET = 312,
     AND_ET = 313,
     XOR_ET = 314,
     PRINTF = 315,
     SCANF = 316,
     MAIN = 317,
     COLON = 318,
     DEFAULT = 319,
     VOID = 320,
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
#define ID 263
#define FUN_START 264
#define INCLUDE 265
#define PREDEF_HEADER 266
#define ELIF 267
#define ELSE 268
#define IF 269
#define BREAK 270
#define NOT 271
#define FOR 272
#define CONTINUE 273
#define WHILE 274
#define SWITCH 275
#define CASE 276
#define STRUCT 277
#define UNION 278
#define RETURN 279
#define SL_COMMENT 280
#define ML_COMMENT 281
#define EQUALTO 282
#define OPEN_BRACK 283
#define OPEN_FLOWER 284
#define OPEN_SQ 285
#define CLOSE_BRACK 286
#define CLOSE_FLOWER 287
#define CLOSE_SQ 288
#define AND 289
#define UNARY_OP 290
#define PLUS 291
#define MINUS 292
#define DIV 293
#define MUL 294
#define MOD 295
#define OR 296
#define AMPERSAND 297
#define BIT_OR 298
#define BIT_XOR 299
#define SEMICOLON 300
#define COMMA 301
#define ISEQUALTO 302
#define LT 303
#define LTE 304
#define GT 305
#define GTE 306
#define NE 307
#define PLUS_ET 308
#define MINUS_ET 309
#define MUL_ET 310
#define DIV_ET 311
#define OR_ET 312
#define AND_ET 313
#define XOR_ET 314
#define PRINTF 315
#define SCANF 316
#define MAIN 317
#define COLON 318
#define DEFAULT 319
#define VOID 320
#define MALLOC 321
#define SIZEOF 322
#define TYPEDEF 323
#define DOT 324
#define ARROW 325




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 410 ".\\semanticAnalysis.y"

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


