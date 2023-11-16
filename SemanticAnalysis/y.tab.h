
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
     NULLT = 258,
     TYPE = 259,
     INTEGER = 260,
     STRING = 261,
     FLOATING_NUM = 262,
     CHAR_CONST = 263,
     STRUCT = 264,
     UNION = 265,
     VOID = 266,
     ID = 267,
     FUN_START = 268,
     INCLUDE = 269,
     PREDEF_HEADER = 270,
     ELIF = 271,
     ELSE = 272,
     IF = 273,
     BREAK = 274,
     NOT = 275,
     FOR = 276,
     CONTINUE = 277,
     WHILE = 278,
     SWITCH = 279,
     CASE = 280,
     RETURN = 281,
     SL_COMMENT = 282,
     ML_COMMENT = 283,
     EQUALTO = 284,
     OPEN_BRACK = 285,
     OPEN_FLOWER = 286,
     OPEN_SQ = 287,
     CLOSE_BRACK = 288,
     CLOSE_FLOWER = 289,
     CLOSE_SQ = 290,
     AND = 291,
     UNARY_OP = 292,
     PLUS = 293,
     MINUS = 294,
     DIV = 295,
     MUL = 296,
     MOD = 297,
     OR = 298,
     AMPERSAND = 299,
     BIT_OR = 300,
     BIT_XOR = 301,
     SEMICOLON = 302,
     COMMA = 303,
     ISEQUALTO = 304,
     LT = 305,
     LTE = 306,
     GT = 307,
     GTE = 308,
     NE = 309,
     PLUS_ET = 310,
     MINUS_ET = 311,
     MUL_ET = 312,
     DIV_ET = 313,
     OR_ET = 314,
     AND_ET = 315,
     XOR_ET = 316,
     PRINTF = 317,
     SCANF = 318,
     MAIN = 319,
     COLON = 320,
     DEFAULT = 321,
     MALLOC = 322,
     SIZEOF = 323,
     TYPEDEF = 324,
     DOT = 325,
     ARROW = 326
   };
#endif
/* Tokens.  */
#define NULLT 258
#define TYPE 259
#define INTEGER 260
#define STRING 261
#define FLOATING_NUM 262
#define CHAR_CONST 263
#define STRUCT 264
#define UNION 265
#define VOID 266
#define ID 267
#define FUN_START 268
#define INCLUDE 269
#define PREDEF_HEADER 270
#define ELIF 271
#define ELSE 272
#define IF 273
#define BREAK 274
#define NOT 275
#define FOR 276
#define CONTINUE 277
#define WHILE 278
#define SWITCH 279
#define CASE 280
#define RETURN 281
#define SL_COMMENT 282
#define ML_COMMENT 283
#define EQUALTO 284
#define OPEN_BRACK 285
#define OPEN_FLOWER 286
#define OPEN_SQ 287
#define CLOSE_BRACK 288
#define CLOSE_FLOWER 289
#define CLOSE_SQ 290
#define AND 291
#define UNARY_OP 292
#define PLUS 293
#define MINUS 294
#define DIV 295
#define MUL 296
#define MOD 297
#define OR 298
#define AMPERSAND 299
#define BIT_OR 300
#define BIT_XOR 301
#define SEMICOLON 302
#define COMMA 303
#define ISEQUALTO 304
#define LT 305
#define LTE 306
#define GT 307
#define GTE 308
#define NE 309
#define PLUS_ET 310
#define MINUS_ET 311
#define MUL_ET 312
#define DIV_ET 313
#define OR_ET 314
#define AND_ET 315
#define XOR_ET 316
#define PRINTF 317
#define SCANF 318
#define MAIN 319
#define COLON 320
#define DEFAULT 321
#define MALLOC 322
#define SIZEOF 323
#define TYPEDEF 324
#define DOT 325
#define ARROW 326




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 413 "semanticAnalysis.y"

    char * value;
    char * type;



/* Line 1676 of yacc.c  */
#line 201 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


