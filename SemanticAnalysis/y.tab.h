
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
     CONST = 270,
     PREDEF_HEADER = 271,
     ELIF = 272,
     ELSE = 273,
     IF = 274,
     BREAK = 275,
     NOT = 276,
     FOR = 277,
     CONTINUE = 278,
     WHILE = 279,
     SWITCH = 280,
     CASE = 281,
     RETURN = 282,
     SL_COMMENT = 283,
     ML_COMMENT = 284,
     EQUALTO = 285,
     OPEN_BRACK = 286,
     OPEN_FLOWER = 287,
     OPEN_SQ = 288,
     CLOSE_BRACK = 289,
     CLOSE_FLOWER = 290,
     CLOSE_SQ = 291,
     AND = 292,
     UNARY_OP = 293,
     PLUS = 294,
     MINUS = 295,
     DIV = 296,
     MUL = 297,
     MOD = 298,
     OR = 299,
     AMPERSAND = 300,
     BIT_OR = 301,
     BIT_XOR = 302,
     SEMICOLON = 303,
     COMMA = 304,
     ISEQUALTO = 305,
     LT = 306,
     LTE = 307,
     GT = 308,
     GTE = 309,
     NE = 310,
     PLUS_ET = 311,
     MINUS_ET = 312,
     MUL_ET = 313,
     DIV_ET = 314,
     OR_ET = 315,
     AND_ET = 316,
     XOR_ET = 317,
     PRINTF = 318,
     SCANF = 319,
     MAIN = 320,
     COLON = 321,
     DEFAULT = 322,
     MALLOC = 323,
     SIZEOF = 324,
     TYPEDEF = 325,
     DOT = 326,
     ARROW = 327
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
#define CONST 270
#define PREDEF_HEADER 271
#define ELIF 272
#define ELSE 273
#define IF 274
#define BREAK 275
#define NOT 276
#define FOR 277
#define CONTINUE 278
#define WHILE 279
#define SWITCH 280
#define CASE 281
#define RETURN 282
#define SL_COMMENT 283
#define ML_COMMENT 284
#define EQUALTO 285
#define OPEN_BRACK 286
#define OPEN_FLOWER 287
#define OPEN_SQ 288
#define CLOSE_BRACK 289
#define CLOSE_FLOWER 290
#define CLOSE_SQ 291
#define AND 292
#define UNARY_OP 293
#define PLUS 294
#define MINUS 295
#define DIV 296
#define MUL 297
#define MOD 298
#define OR 299
#define AMPERSAND 300
#define BIT_OR 301
#define BIT_XOR 302
#define SEMICOLON 303
#define COMMA 304
#define ISEQUALTO 305
#define LT 306
#define LTE 307
#define GT 308
#define GTE 309
#define NE 310
#define PLUS_ET 311
#define MINUS_ET 312
#define MUL_ET 313
#define DIV_ET 314
#define OR_ET 315
#define AND_ET 316
#define XOR_ET 317
#define PRINTF 318
#define SCANF 319
#define MAIN 320
#define COLON 321
#define DEFAULT 322
#define MALLOC 323
#define SIZEOF 324
#define TYPEDEF 325
#define DOT 326
#define ARROW 327




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 413 "semanticAnalysis.y"

    char * value;
    char * type;



/* Line 1676 of yacc.c  */
#line 203 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


