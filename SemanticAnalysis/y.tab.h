
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
     ID = 260,
     INCLUDE = 261,
     PREDEF_HEADER = 262,
     STRING = 263,
     ELIF = 264,
     ELSE = 265,
     IF = 266,
     BREAK = 267,
     NOT = 268,
     FOR = 269,
     CONTINUE = 270,
     WHILE = 271,
     SWITCH = 272,
     CASE = 273,
     STRUCT = 274,
     UNION = 275,
     RETURN = 276,
     FLOATING_NUM = 277,
     SL_COMMENT = 278,
     ML_COMMENT = 279,
     CHAR_CONST = 280,
     EQUALTO = 281,
     OPEN_BRACK = 282,
     OPEN_FLOWER = 283,
     OPEN_SQ = 284,
     CLOSE_BRACK = 285,
     CLOSE_FLOWER = 286,
     CLOSE_SQ = 287,
     AND = 288,
     UNARY_OP = 289,
     PLUS = 290,
     MINUS = 291,
     DIV = 292,
     MUL = 293,
     MOD = 294,
     OR = 295,
     AMPERSAND = 296,
     BIT_OR = 297,
     BIT_XOR = 298,
     SEMICOLON = 299,
     COMMA = 300,
     ISEQUALTO = 301,
     LT = 302,
     LTE = 303,
     GT = 304,
     GTE = 305,
     NE = 306,
     PLUS_ET = 307,
     MINUS_ET = 308,
     MUL_ET = 309,
     DIV_ET = 310,
     OR_ET = 311,
     AND_ET = 312,
     XOR_ET = 313,
     PRINTF = 314,
     SCANF = 315,
     MAIN = 316,
     FUN_START = 317,
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
#define ID 260
#define INCLUDE 261
#define PREDEF_HEADER 262
#define STRING 263
#define ELIF 264
#define ELSE 265
#define IF 266
#define BREAK 267
#define NOT 268
#define FOR 269
#define CONTINUE 270
#define WHILE 271
#define SWITCH 272
#define CASE 273
#define STRUCT 274
#define UNION 275
#define RETURN 276
#define FLOATING_NUM 277
#define SL_COMMENT 278
#define ML_COMMENT 279
#define CHAR_CONST 280
#define EQUALTO 281
#define OPEN_BRACK 282
#define OPEN_FLOWER 283
#define OPEN_SQ 284
#define CLOSE_BRACK 285
#define CLOSE_FLOWER 286
#define CLOSE_SQ 287
#define AND 288
#define UNARY_OP 289
#define PLUS 290
#define MINUS 291
#define DIV 292
#define MUL 293
#define MOD 294
#define OR 295
#define AMPERSAND 296
#define BIT_OR 297
#define BIT_XOR 298
#define SEMICOLON 299
#define COMMA 300
#define ISEQUALTO 301
#define LT 302
#define LTE 303
#define GT 304
#define GTE 305
#define NE 306
#define PLUS_ET 307
#define MINUS_ET 308
#define MUL_ET 309
#define DIV_ET 310
#define OR_ET 311
#define AND_ET 312
#define XOR_ET 313
#define PRINTF 314
#define SCANF 315
#define MAIN 316
#define FUN_START 317
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
#line 349 ".\\semanticAnalysis.y"

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


