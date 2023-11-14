
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 ".\\semanticAnalysis.y"

    #include<stdio.h>
    int yylex();
    int yyerror(char const * s);
    extern FILE * yyin;
    extern char *yytext;
    extern int yylinenumber;
    extern int intval;

    #include <string.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #define TABLE_SIZE 1003
    #define MAX_SYMBOLS 1000000

    //Scope Number
    int scope=1; //Scope of Global Variables = 1
    int stIterator=0;

    int ID_dim =0 ;
    int dimbuffer[30];
    int dimit = 0;

    int PD[20];
    int pdi=0;

    //Datatypes
    char datatypesArray[][20]={"int","char","float","string"};
    char CLASS[][20]={"variable","function","array","pointer","struct","union"};
    int checkCompartibility(char *a,char *b){
        if(strcmp(a,datatypesArray[0])==0 && strcmp(b,datatypesArray[0])==0){
            return 0;
        }
        else if(strcmp(a,datatypesArray[1])==0 && strcmp(b,datatypesArray[1])==0){
            return 1;
        }
        else if(strcmp(a,datatypesArray[2])==0 && strcmp(b,datatypesArray[2])==0){
            return 2;
        }
        else if((strcmp(a,datatypesArray[0])==0 && strcmp(b,datatypesArray[1])==0) ||
        (strcmp(b,datatypesArray[0])==0 && strcmp(a,datatypesArray[1])==0)){
            return 0;
        }
        else if((strcmp(a,datatypesArray[0])==0 && strcmp(b,datatypesArray[1])==2) ||
        (strcmp(b,datatypesArray[0])==0 && strcmp(a,datatypesArray[1])==2)){
            return 2;
        }
        else if((strcmp(a,datatypesArray[0])==1 && strcmp(b,datatypesArray[1])==2) ||
        (strcmp(b,datatypesArray[0])==1 && strcmp(a,datatypesArray[1])==2)){
            return 2;
        }
        else{
            return -1;
        }
    }

    char * locations[MAX_SYMBOLS];
    int symTableSize=0;

    struct lines{
        int lineno; // stores the line-number
        struct lines*next;
    };
    struct SymbolTableEntry {
        char * name; //identifier
        char * type; //variable, array , pointer etc
        char * dataType; // int, char, float
        int dimension; // 0 for Variables, 1 for 1D arrays, 2 for 2D Arrays etc
        int * dimSize; //Array holding the size of the array
        int scope;
        int lineOfDeclaration;
        struct SymbolTableEntry * next;
        struct lines * head; //head of the linenumbers of reference list
        struct lines *  tail; //tail of the linenumbers of reference list
        int noOfParams;
        char ** paraList;
        char * paraTypes;
        int * paraDim;  //Dimension of array or pointers in function
        int symIndex;
    };

    struct SymbolTable {
        struct SymbolTableEntry * symTable[TABLE_SIZE];
    };

    struct SymbolTable Table;
    struct SymbolTable DST[10];

    //Hash Function
    int hashfunction(char *s) {
        int pp = 101;
        int mod = TABLE_SIZE;
        int val = 0;
        int n = strlen(s);
        int p = 1;
        for (int i = 0; i < n; i++) {
            int c = s[i];
            val = (val + ((c * p) % mod)) % mod;
            p = (p * pp) % mod;
        }
        return val;
    }

    // Function to insert a key-value pair (doesnt exist) into the SymbolTable 

    struct SymbolTableEntry* insertIdentifier(char* key,char * type,char * dataType,int dimension,int linenumber,int scope) {
        int index = hashfunction(key);

        // Create a new entry
        struct SymbolTableEntry* new_entry = (struct SymbolTableEntry*)malloc(sizeof(struct SymbolTableEntry));
        struct SymbolTableEntry* new_entrydst = (struct SymbolTableEntry*)malloc(sizeof(struct SymbolTableEntry));


        new_entry->name = strdup(key); // Duplicate the key string
        new_entrydst->name = strdup(key);

        new_entry->type = strdup(type); // Duplicate the string type
        new_entrydst->type = strdup(type);

        new_entry->dataType=strdup(dataType); //Duplicate the dataType of the String
        new_entrydst->dataType = strdup(dataType);

        new_entry->lineOfDeclaration=linenumber;
        new_entrydst->lineOfDeclaration = linenumber;

        new_entry->scope=scope;
        new_entrydst->scope = scope;

        new_entry->dimension=dimension;
        new_entrydst->dimension = dimension;

        new_entry->next = Table.symTable[index];
        new_entrydst->next = DST[scope].symTable[index];

        new_entry->head = (struct lines *)malloc(sizeof(struct lines));
        new_entrydst->head = (struct lines *)malloc(sizeof(struct lines));
        new_entry->head->lineno = linenumber;
        new_entrydst->head->lineno = linenumber;
        new_entry->head->next = NULL;
        new_entrydst->head->next =NULL;
        new_entry->tail = new_entry->head;
        new_entrydst->tail = new_entrydst->head;

        new_entry->dimSize=NULL;
        new_entrydst->dimSize=NULL;
        new_entry->noOfParams=-1;
        new_entrydst->noOfParams=-1;
        new_entry->paraList=NULL;
        new_entrydst->paraList=NULL;
        new_entry->paraTypes=NULL;
        new_entrydst->paraTypes=NULL;
        new_entry->paraDim=NULL;
        new_entrydst->paraDim=NULL;

        new_entrydst->symIndex=stIterator;
        new_entry->symIndex=stIterator;
        
        Table.symTable[stIterator++] = new_entry;
        DST[scope].symTable[index] = new_entrydst;

        locations[symTableSize++]=strdup(key);

        return new_entry;
    }

    struct SymbolTableEntry* insertArray(char* key,char * type,char * dataType,int dimension,int linenumber,int scope,int * dimList) {
        int index = hashfunction(key);

        // Create a new entry
        struct SymbolTableEntry* new_entry = (struct SymbolTableEntry*)malloc(sizeof(struct SymbolTableEntry));
        struct SymbolTableEntry* new_entrydst = (struct SymbolTableEntry*)malloc(sizeof(struct SymbolTableEntry));


        new_entry->name = strdup(key); // Duplicate the key string
        new_entrydst->name = strdup(key);

        new_entry->type = strdup(type); // Duplicate the string type
        new_entrydst->type = strdup(type);

        new_entry->dataType=strdup(dataType); //Duplicate the dataType of the String
        new_entrydst->dataType = strdup(dataType);

        new_entry->lineOfDeclaration=linenumber;
        new_entrydst->lineOfDeclaration = linenumber;

        new_entry->scope=scope;
        new_entrydst->scope = scope;

        new_entry->dimension=dimension;
        new_entrydst->dimension = dimension;

        new_entry->next = Table.symTable[index];
        new_entrydst->next = DST[scope].symTable[index];

        new_entry->head = (struct lines *)malloc(sizeof(struct lines));
        new_entrydst->head = (struct lines *)malloc(sizeof(struct lines));

        new_entry->head->lineno = linenumber;
        new_entrydst->head->lineno = linenumber;

        new_entry->head->next = NULL;
        new_entrydst->head->next =NULL;

        new_entry->tail = new_entry->head;
        new_entrydst->tail = new_entrydst->head;

        new_entry->dimSize=(int *)malloc(sizeof(int)*dimension);


        if(dimList != NULL)
        {        
            for(int i=0;i<dimension;i++){
                new_entry->dimSize[i]=dimList[i];
            }

            new_entrydst->dimSize=(int *)malloc(sizeof(int)*dimension);
            for(int i=0;i<dimension;i++){
                new_entrydst->dimSize[i]=dimList[i];
            }
        }


        new_entry->noOfParams=-1;
        new_entrydst->noOfParams=-1;
        new_entry->paraList=NULL;
        new_entrydst->paraList=NULL;
        new_entry->paraDim=NULL;
        new_entrydst->paraDim=NULL;

        new_entrydst->symIndex=stIterator;
        new_entry->symIndex=stIterator;
        
        Table.symTable[stIterator++] = new_entry;
        DST[scope].symTable[index] = new_entrydst;

        locations[symTableSize++]=strdup(key);

        return new_entry;
    }

    struct SymbolTableEntry* insertFunction(char* key,char * type,char * dataType,int dimension,int linenumber,int scope,int params,char parList[20][20],char paraTypes[20]) {
        int index = hashfunction(key);

        // Create a new entry
        struct SymbolTableEntry* new_entry = (struct SymbolTableEntry*)malloc(sizeof(struct SymbolTableEntry));
        struct SymbolTableEntry* new_entrydst = (struct SymbolTableEntry*)malloc(sizeof(struct SymbolTableEntry));


        new_entry->name = strdup(key); // Duplicate the key string
        new_entrydst->name = strdup(key);

        new_entry->type = strdup(type); // Duplicate the string type
        new_entrydst->type = strdup(type);

        new_entry->dataType=strdup(dataType); //Duplicate the dataType of the String
        new_entrydst->dataType = strdup(dataType);

        new_entry->lineOfDeclaration=linenumber;
        new_entrydst->lineOfDeclaration = linenumber;

        new_entry->scope=scope;
        new_entrydst->scope = scope;

        new_entry->dimension=dimension;
        new_entrydst->dimension = dimension;

        new_entry->next = Table.symTable[index];
        new_entrydst->next = DST[scope].symTable[index];

        new_entry->head = (struct lines *)malloc(sizeof(struct lines));
        new_entrydst->head = (struct lines *)malloc(sizeof(struct lines));
        new_entry->head->lineno = linenumber;
        new_entrydst->head->lineno = linenumber;
        new_entry->head->next = NULL;
        new_entrydst->head->next =NULL;
        new_entry->tail = new_entry->head;
        new_entrydst->tail = new_entrydst->head;

        new_entry->dimSize=NULL;
        new_entrydst->dimSize=NULL;
        new_entry->noOfParams=params;
        new_entrydst->noOfParams=params;

        new_entry->paraList=(char **)malloc(sizeof(char*)*params);
        for(int i=0;i<params;i++){
            new_entry->paraList[i]=(char *)malloc(20*sizeof(char));
            strcpy(new_entry->paraList[i],parList[i]);
        }
        
        new_entrydst->paraList=(char **)malloc(sizeof(char*)*params);
        for(int i=0;i<params;i++){
            new_entrydst->paraList[i]=(char *)malloc(20*sizeof(char));
            strcpy(new_entrydst->paraList[i],parList[i]);
        }

        new_entry->paraTypes=(char *)malloc(sizeof(char)*params);
        for(int i=0;i<params;i++){
            new_entry->paraTypes[i]=paraTypes[i];
        }

        new_entrydst->paraTypes=(char *)malloc(sizeof(char)*params);
        for(int i=0;i<params;i++){
            new_entrydst->paraTypes[i]=paraTypes[i];
        }

        new_entry->paraDim=(int *)malloc(sizeof(int)*params);
        for(int i=0;i<params;i++){
            new_entry->paraDim[i]=PD[i];
        }

        new_entrydst->paraDim=(int *)malloc(sizeof(int)*params);
        for(int i=0;i<params;i++){
            new_entrydst->paraDim[i]=PD[i];
        }

        new_entrydst->symIndex=stIterator;
        new_entry->symIndex=stIterator;

        Table.symTable[stIterator++] = new_entry;
        DST[scope].symTable[index] = new_entrydst;

        locations[symTableSize++]=strdup(key);

        return new_entry;
    }
    
    //Function to append an entry for key-value pair that already exists in the SymbolTable
    void update(struct SymbolTableEntry* entry,int linenumber){
        
        struct SymbolTableEntry* Entry=Table.symTable[entry->symIndex];
        struct lines * new_node = (struct lines *)malloc(sizeof(struct lines));
        new_node->lineno = linenumber;
        new_node->next = NULL;
        Entry->tail->next = new_node;
        Entry->tail = new_node;
    }

    // Function to Lookup
    struct SymbolTableEntry *  lookup(char* key,int scope,bool insertion) {
        int index = hashfunction(key);
        if(insertion){
            struct SymbolTableEntry* entry = DST[scope].symTable[index];
            while(entry != NULL){
                if(strcmp(entry->name,key) == 0)return entry;
                entry = entry->next;
            }
        }
        else{
            int tempscope = scope;
            while(tempscope>=1){
                struct SymbolTableEntry* entry = DST[tempscope].symTable[index];
                while(entry != NULL){
                    if(strcmp(entry->name,key) == 0)return entry;
                    entry = entry->next;

                }
                tempscope--;
            }
        }

        // Key not found
        return NULL;
    }

    void deleteDMT(int scope)
    {
        for(int i =0;i<TABLE_SIZE;i++)
        {
            struct SymbolTableEntry * temp = DST[scope].symTable[i];
            while(temp != NULL)
            {
                struct SymbolTableEntry * tempnext = temp;
                free(tempnext);
                temp = temp->next;

            }
            DST[scope].symTable[i] = NULL;
        }
    }


    struct SymbolTableEntry * varDecArray[100];
    int index=0;

    
    //To store type
    char typeBuffer[10];
    char IDBuffer[30];

    char funTypeBuffer[30];
    char funNameBuffer[30];

    //Global Variables for func parameters
    int noOfParameters=0;
    char PL[20][20];
    char PTL[20];

    struct SymbolTableEntry * forFunc;
    char pt;
    
    int arrayInFunc[100];
    int dimOfArrayInFunc=0;

    int parD[10];
    int parDi=0;

    //start globalVarDec startGlobal DG optionsG main mainParameters start1 varDec D options header newHeader file Exp function_declaration function_call function_defn parameter_list choice item params for while varDecF ExpF print printExpr printArguments printContent scanf scanfArguments scanfContent scanfExpr dimension BOX BALANCED_BRACK arrayElement arrayInitial arrayDeclr arrayAsAParameter arrayParams_unend higherDimention pointerAsAParameter PTR_DECLR PTR_EXP PTR_INITIAL PTR_STAR PTR_TYPE switch switchcase default comp ifElseLadder matched S elif unmatched userDefDataType userTypeDeclaration userTypeDefination userTypeInitialization userTypeObj userTypeParams


/* Line 189 of yacc.c  */
#line 483 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


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

/* Line 214 of yacc.c  */
#line 410 ".\\semanticAnalysis.y"

    char * value;
    char * type;



/* Line 214 of yacc.c  */
#line 666 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 678 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   831

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  71
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  82
/* YYNRULES -- Number of rules.  */
#define YYNRULES  206
/* YYNRULES -- Number of states.  */
#define YYNSTATES  463

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   325

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     7,    11,    13,    14,    16,    18,    20,
      22,    24,    27,    28,    35,    41,    46,    47,    50,    51,
      58,    60,    61,    63,    65,    67,    69,    71,    73,    78,
      82,    86,    89,    92,    95,    98,   100,   103,   106,   109,
     112,   115,   116,   118,   125,   131,   132,   133,   141,   146,
     147,   150,   151,   158,   159,   164,   165,   167,   169,   171,
     175,   179,   183,   187,   191,   195,   199,   203,   207,   211,
     214,   217,   220,   224,   228,   232,   236,   240,   244,   248,
     252,   256,   260,   264,   268,   272,   276,   278,   279,   283,
     285,   287,   289,   295,   299,   302,   308,   312,   314,   318,
     320,   321,   322,   330,   331,   338,   340,   342,   346,   348,
     350,   352,   354,   356,   358,   370,   380,   392,   402,   411,
     418,   424,   429,   431,   432,   439,   441,   444,   448,   451,
     453,   455,   462,   465,   470,   474,   478,   481,   483,   485,
     488,   493,   497,   499,   501,   506,   511,   515,   517,   526,
     534,   536,   539,   547,   554,   560,   564,   569,   575,   577,
     581,   586,   588,   589,   593,   598,   606,   613,   620,   623,
     625,   628,   630,   632,   645,   657,   667,   673,   674,   678,
     679,   681,   683,   685,   687,   689,   702,   711,   712,   721,
     731,   740,   746,   750,   756,   761,   764,   769,   771,   775,
     776,   781,   785,   794,   801,   808,   810
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      72,     0,    -1,    73,    76,    80,    -1,    10,    75,    74,
      -1,    73,    -1,    -1,     5,    -1,    11,    -1,    97,    -1,
      77,    -1,   147,    -1,   150,    76,    -1,    -1,    83,     8,
      79,    78,    45,    76,    -1,     8,    79,    78,    45,    76,
      -1,    46,     8,    79,    78,    -1,    -1,    27,    94,    -1,
      -1,    62,    81,    31,    92,    82,    93,    -1,    99,    -1,
      -1,    84,    -1,   112,    -1,   116,    -1,   101,    -1,   109,
      -1,   108,    -1,    24,   111,    45,    82,    -1,    18,    45,
      82,    -1,    15,    45,    82,    -1,    25,    82,    -1,    26,
      82,    -1,   124,    82,    -1,   127,    82,    -1,   138,    -1,
     134,    82,    -1,   133,    82,    -1,   142,    82,    -1,   150,
      82,    -1,   151,    82,    -1,    -1,     3,    -1,    83,    91,
      88,    87,    45,    82,    -1,    96,    88,    87,    45,    82,
      -1,    -1,    -1,    96,    85,   125,    88,    45,    86,    82,
      -1,    46,    91,    88,    87,    -1,    -1,    27,    94,    -1,
      -1,    27,     8,    89,    28,   105,    31,    -1,    -1,     8,
      90,    28,    31,    -1,    -1,     8,    -1,    29,    -1,    32,
      -1,    28,    94,    31,    -1,    94,    36,    94,    -1,    94,
      37,    94,    -1,    94,    39,    94,    -1,    94,    38,    94,
      -1,    94,    40,    94,    -1,    94,    41,    94,    -1,    94,
      34,    94,    -1,    94,    44,    94,    -1,    94,    42,    94,
      -1,    94,    35,    -1,    35,    94,    -1,    16,    94,    -1,
      94,    43,    94,    -1,    94,    47,    94,    -1,    94,    48,
      94,    -1,    94,    49,    94,    -1,    94,    50,    94,    -1,
      94,    51,    94,    -1,    94,    52,    94,    -1,    94,    53,
      94,    -1,    94,    54,    94,    -1,    94,    55,    94,    -1,
      94,    56,    94,    -1,    94,    57,    94,    -1,    94,    58,
      94,    -1,    94,    59,    94,    -1,    96,    -1,    -1,    96,
      95,   125,    -1,     4,    -1,     7,    -1,     8,    -1,    98,
      92,    82,    93,    76,    -1,   107,    99,    31,    -1,   107,
      31,    -1,    99,    46,    83,     8,   100,    -1,    99,    46,
     132,    -1,   132,    -1,    83,     8,   100,    -1,   130,    -1,
      -1,    -1,   104,    28,   105,    31,   102,    45,    82,    -1,
      -1,   104,    28,    31,   103,    45,    82,    -1,     8,    -1,
     106,    -1,   105,    46,   106,    -1,     8,    -1,     4,    -1,
       5,    -1,     7,    -1,     6,    -1,     9,    -1,    17,    28,
     110,   111,    45,   111,    31,    92,    82,    93,    82,    -1,
      17,    28,   110,   111,    45,   111,    31,    45,    82,    -1,
      17,    28,    45,   111,    45,   111,    31,    92,    82,    93,
      82,    -1,    17,    28,    45,   111,    45,   111,    31,    45,
      82,    -1,    19,    28,   111,    31,    92,    82,    93,    82,
      -1,    19,    28,   111,    31,    45,    82,    -1,    83,     8,
      88,    87,    45,    -1,     8,    88,    87,    45,    -1,    94,
      -1,    -1,    60,    28,   113,    31,    45,    82,    -1,     5,
      -1,     5,   114,    -1,    46,   115,   114,    -1,    46,   115,
      -1,    94,    -1,   120,    -1,    61,    28,   117,    31,    45,
      82,    -1,     5,   118,    -1,    46,    42,     8,   118,    -1,
      46,    42,     8,    -1,    46,   119,   118,    -1,    46,   119,
      -1,     8,    -1,   120,    -1,     8,   121,    -1,   122,    94,
      33,   121,    -1,   122,    94,    33,    -1,    30,    -1,     8,
      -1,    83,   123,   125,    45,    -1,   125,   122,   126,    33,
      -1,   122,   126,    33,    -1,     4,    -1,    83,   123,   125,
      27,    92,   128,    93,    45,    -1,    83,   123,   125,    27,
      92,    93,    45,    -1,   129,    -1,   129,    46,    -1,   129,
      46,    92,   128,    93,    46,   128,    -1,   129,    46,    92,
     128,    93,    46,    -1,   129,    46,    92,   128,    93,    -1,
      92,   128,    93,    -1,    92,   128,    93,    46,    -1,    92,
     128,    93,    46,   128,    -1,     4,    -1,   129,    46,     4,
      -1,    30,   126,    33,   131,    -1,   125,    -1,    -1,   136,
     135,     8,    -1,   136,   135,     8,    45,    -1,   136,   135,
       8,    27,    42,     8,    45,    -1,   136,   135,     8,    27,
       8,    45,    -1,   136,   135,     8,    27,   137,    45,    -1,
     135,    39,    -1,    39,    -1,   152,     8,    -1,    83,    -1,
      65,    -1,    28,   136,   135,    31,    66,    28,    67,    28,
     136,   135,    31,    31,    -1,    28,   136,   135,    31,    66,
      28,    67,    28,   136,    31,    31,    -1,    20,    28,     8,
      31,    92,   139,   140,    93,    82,    -1,    21,   141,    63,
      82,   139,    -1,    -1,    64,    63,    82,    -1,    -1,     7,
      -1,     4,    -1,   143,    -1,   144,    -1,   146,    -1,    14,
      28,    94,    31,    92,    82,    93,   145,    13,    92,    82,
      93,    -1,    12,    28,    94,    31,    92,    82,    93,   145,
      -1,    -1,    14,    28,    94,    31,    92,    82,    93,   145,
      -1,    68,   152,     8,    92,   148,    93,   149,    45,    76,
      -1,   152,     8,    92,   148,    93,   149,    45,    76,    -1,
      83,     8,   131,    45,   148,    -1,   132,    45,   148,    -1,
     152,     8,     8,    45,   148,    -1,    83,     8,   131,    45,
      -1,   132,    45,    -1,   152,     8,     8,    45,    -1,     8,
      -1,   149,    46,     8,    -1,    -1,   152,     8,     8,    45,
      -1,     8,     8,    45,    -1,   152,     8,     8,    27,    92,
     105,    93,    45,    -1,     8,    69,     8,    27,   106,    45,
      -1,     8,    70,     8,    27,   106,    45,    -1,    22,    -1,
      23,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   437,   437,   438,   439,   439,   440,   440,   442,   442,
     442,   442,   442,   444,   445,   446,   446,   447,   447,   449,
     450,   450,   452,   452,   452,   452,   452,   452,   453,   453,
     453,   454,   454,   454,   454,   455,   455,   455,   455,   456,
     456,   456,   458,   463,   464,   465,   465,   465,   485,   485,
     486,   486,   486,   496,   496,   506,   508,   520,   521,   523,
     524,   525,   526,   527,   528,   529,   530,   531,   532,   533,
     534,   535,   536,   537,   538,   539,   540,   541,   542,   543,
     544,   545,   546,   547,   548,   549,   550,   551,   551,   552,
     552,   554,   569,   570,   580,   590,   623,   624,   625,   645,
     648,   651,   651,   685,   685,   731,   748,   753,   758,   781,
     782,   783,   784,   786,   819,   820,   821,   822,   824,   825,
     827,   828,   830,   830,   832,   833,   834,   835,   836,   837,
     837,   839,   840,   841,   842,   843,   844,   845,   845,   847,
     848,   848,   850,   852,   865,   867,   867,   869,   870,   870,
     871,   872,   873,   874,   875,   876,   877,   878,   879,   879,
     881,   882,   882,   884,   886,   887,   887,   887,   888,   888,
     889,   889,   889,   890,   891,   893,   894,   894,   895,   895,
     896,   896,   898,   899,   899,   900,   901,   901,   902,   904,
     904,   905,   906,   907,   908,   909,   910,   911,   911,   911,
     912,   912,   913,   914,   915,   917,   917
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TYPE", "INTEGER", "STRING",
  "FLOATING_NUM", "CHAR_CONST", "ID", "FUN_START", "INCLUDE",
  "PREDEF_HEADER", "ELIF", "ELSE", "IF", "BREAK", "NOT", "FOR", "CONTINUE",
  "WHILE", "SWITCH", "CASE", "STRUCT", "UNION", "RETURN", "SL_COMMENT",
  "ML_COMMENT", "EQUALTO", "OPEN_BRACK", "OPEN_FLOWER", "OPEN_SQ",
  "CLOSE_BRACK", "CLOSE_FLOWER", "CLOSE_SQ", "AND", "UNARY_OP", "PLUS",
  "MINUS", "DIV", "MUL", "MOD", "OR", "AMPERSAND", "BIT_OR", "BIT_XOR",
  "SEMICOLON", "COMMA", "ISEQUALTO", "LT", "LTE", "GT", "GTE", "NE",
  "PLUS_ET", "MINUS_ET", "MUL_ET", "DIV_ET", "OR_ET", "AND_ET", "XOR_ET",
  "PRINTF", "SCANF", "MAIN", "COLON", "DEFAULT", "VOID", "MALLOC",
  "SIZEOF", "TYPEDEF", "DOT", "ARROW", "$accept", "start", "header",
  "newHeader", "file", "startGlobal", "globalVarDec", "DG", "optionsG",
  "main", "mainParameters", "start1", "type", "varDec", "$@1", "$@2", "D",
  "options", "$@3", "$@4", "id", "open_flower", "close_flower", "Exp",
  "$@5", "id3", "function_defn", "function_declaration", "parameter_list",
  "choice", "function_call", "$@6", "$@7", "funName", "params", "item",
  "fun_start", "for", "while", "varDecF", "ExpF", "print", "printExpr",
  "printArguments", "printContent", "scanf", "scanfExpr", "scanfArguments",
  "scanfContent", "arrayElement", "dimension", "open_sq", "ID2",
  "arrayDeclr", "BOX", "integer_dim", "arrayInitial", "BALANCED_BRACK",
  "arrayParams_unend", "arrayAsAParameter", "higherDimention",
  "pointerAsAParameter", "PTR_DECLR", "PTR_INITIAL", "PTR_STAR",
  "PTR_TYPE", "PTR_EXP", "switch", "switchcase", "default", "comp",
  "ifElseLadder", "S", "matched", "elif", "unmatched",
  "userTypeDefination", "userTypeParams", "userTypeObj",
  "userTypeDeclaration", "userTypeInitialization", "userDefDataType", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    71,    72,    73,    74,    74,    75,    75,    76,    76,
      76,    76,    76,    77,    77,    78,    78,    79,    79,    80,
      81,    81,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    83,    84,    84,    85,    86,    84,    87,    87,
      88,    89,    88,    90,    88,    88,    91,    92,    93,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    95,    94,    94,
      94,    96,    97,    98,    98,    99,    99,    99,    99,   100,
     100,   102,   101,   103,   101,   104,   105,   105,   106,   106,
     106,   106,   106,   107,   108,   108,   108,   108,   109,   109,
     110,   110,   111,   111,   112,   113,   113,   114,   114,   115,
     115,   116,   117,   118,   118,   118,   118,   119,   119,   120,
     121,   121,   122,   123,   124,   125,   125,   126,   127,   127,
     128,   128,   128,   128,   128,   128,   128,   128,   129,   129,
     130,   131,   131,   132,   133,   134,   134,   134,   135,   135,
     136,   136,   136,   137,   137,   138,   139,   139,   140,   140,
     141,   141,   142,   143,   143,   144,   145,   145,   146,   147,
     147,   148,   148,   148,   148,   148,   148,   149,   149,   149,
     150,   150,   151,   151,   151,   152,   152
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     3,     1,     0,     1,     1,     1,     1,
       1,     2,     0,     6,     5,     4,     0,     2,     0,     6,
       1,     0,     1,     1,     1,     1,     1,     1,     4,     3,
       3,     2,     2,     2,     2,     1,     2,     2,     2,     2,
       2,     0,     1,     6,     5,     0,     0,     7,     4,     0,
       2,     0,     6,     0,     4,     0,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     1,     0,     3,     1,
       1,     1,     5,     3,     2,     5,     3,     1,     3,     1,
       0,     0,     7,     0,     6,     1,     1,     3,     1,     1,
       1,     1,     1,     1,    11,     9,    11,     9,     8,     6,
       5,     4,     1,     0,     6,     1,     2,     3,     2,     1,
       1,     6,     2,     4,     3,     3,     2,     1,     1,     2,
       4,     3,     1,     1,     4,     4,     3,     1,     8,     7,
       1,     2,     7,     6,     5,     3,     4,     5,     1,     3,
       4,     1,     0,     3,     4,     7,     6,     6,     2,     1,
       2,     1,     1,    12,    11,     9,     5,     0,     3,     0,
       1,     1,     1,     1,     1,    12,     8,     0,     8,     9,
       8,     5,     3,     5,     4,     2,     4,     1,     3,     0,
       4,     3,     8,     6,     6,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,    12,     6,     7,     5,     1,    42,    18,
     113,   205,   206,     0,     0,     9,     0,     8,     0,     0,
      10,    12,     0,     4,     3,     0,     0,    16,     0,    21,
       2,    18,    57,    41,    94,   172,   171,     0,    97,     0,
       0,    11,     0,   201,    89,    90,    91,     0,     0,     0,
      17,    86,     0,     0,     0,     0,    20,    16,    91,     0,
       0,     0,     0,     0,     0,   123,    41,    41,     0,     0,
       0,   171,    22,    55,    25,     0,    27,    26,    23,    24,
      41,    41,    41,    41,     0,    35,    41,   182,   183,   184,
      41,    41,     0,   100,    93,     0,   169,     0,   170,     0,
       0,    71,     0,    70,     0,    69,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    18,
      12,     0,     0,     0,     0,     0,     0,    41,     0,    41,
     123,     0,   122,     0,    31,    32,     0,     0,    58,    12,
      56,    55,     0,    53,     0,     0,    49,     0,    33,    34,
      37,    36,     0,    38,    39,    40,   170,     0,    98,    99,
     171,    96,   163,   168,   200,   171,     0,     0,     0,    59,
      66,    60,    61,    63,    62,    64,    65,    68,    72,    67,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,   142,     0,    88,    16,    14,     0,    41,
      12,     0,     0,     0,    30,    55,   123,     0,   123,    29,
       0,     0,    41,   125,     0,     0,     0,    92,    49,     0,
       0,    91,    50,    55,     0,     0,   109,   110,   112,   111,
     108,   103,     0,   106,     0,     0,   147,     0,   100,   162,
     195,   199,   170,     0,     0,    15,   199,     0,    13,     0,
       0,     0,    49,     0,    55,     0,     0,     0,    28,     0,
     126,     0,     0,   132,     0,     0,     0,   144,     0,     0,
       0,    56,    55,    41,     0,   101,     0,     0,   164,     0,
     162,    95,   161,     0,   192,   197,     0,     0,   146,     0,
       0,    19,     0,     0,    41,     0,   123,    49,   123,    41,
      41,   177,    91,   129,   128,   130,    41,   137,     0,   136,
     138,    41,    41,     0,    54,     0,    46,    49,    44,    41,
       0,   107,     0,     0,     0,     0,     0,   160,   194,    12,
       0,   196,   145,    12,   203,   204,     0,   121,     0,     0,
       0,   119,     0,     0,   179,   139,     0,   127,   124,   134,
     135,   131,    43,   158,     0,     0,     0,   150,     0,    41,
      48,   104,    41,   166,   171,     0,     0,   167,     0,   191,
     190,   198,   193,   189,   187,     0,   120,     0,    41,   181,
     180,     0,     0,     0,     0,   133,     0,   149,     0,   151,
      52,    47,   102,     0,   165,     0,     0,   188,    41,    41,
      41,    41,   118,    41,    41,    41,   141,   155,   148,   159,
       0,     0,   202,     0,     0,   117,     0,   115,     0,   177,
     178,   175,   140,   156,     0,     0,     0,    41,    41,    41,
     176,   157,   154,     0,     0,     0,   116,   114,   153,     0,
      41,   185,   152,     0,     0,     0,   187,     0,     0,   186,
     174,     0,   173
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    24,     6,    14,    15,    53,    27,    30,
      55,    70,    71,    72,   155,   369,   235,   156,   279,   230,
     151,   364,   149,   142,   128,    51,    17,    18,    37,   168,
      74,   330,   284,    75,   242,   243,    19,    76,    77,   218,
     143,    78,   224,   270,   314,    79,   226,   273,   319,   315,
     355,   204,   152,    80,   292,   247,    81,   366,   367,   169,
     293,   176,    82,    83,    97,    84,   335,    85,   354,   393,
     391,    86,    87,    88,   407,    89,    20,   177,   296,    90,
      91,    92
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -335
static const yytype_int16 yypact[] =
{
       7,   217,    90,    49,  -335,  -335,     7,  -335,  -335,   103,
    -335,  -335,  -335,   176,    38,  -335,    41,  -335,    92,    45,
    -335,    49,   126,  -335,  -335,   104,   150,   124,   155,    28,
    -335,   167,  -335,   498,  -335,  -335,   200,    52,  -335,   188,
     225,  -335,    26,  -335,  -335,  -335,  -335,   150,   150,   150,
     731,   219,   242,   206,    92,   221,   209,   124,     5,   230,
     212,   232,   214,   233,   244,   150,   498,   498,   246,   247,
     248,   262,  -335,   137,  -335,   253,  -335,  -335,  -335,  -335,
     498,   498,   498,   498,   188,  -335,   498,  -335,  -335,  -335,
     498,   498,   274,   254,  -335,    28,  -335,    48,  -335,   240,
      28,   251,   530,  -335,   150,  -335,   150,   150,   150,   150,
     150,   150,   150,   150,   150,   150,   150,   150,   150,   150,
     150,   150,   150,   150,   150,   150,   150,   150,   257,   167,
      49,    28,    92,   249,   283,   284,   150,   498,    39,   498,
     150,   288,   731,   264,  -335,  -335,   305,   311,  -335,    49,
     289,   123,   257,  -335,   168,   257,   272,   134,  -335,  -335,
    -335,  -335,    55,  -335,  -335,  -335,   316,   321,  -335,  -335,
     318,  -335,  -335,  -335,  -335,   319,   286,   248,   320,  -335,
     612,   196,   196,   251,   251,   251,   578,   779,   447,   557,
     388,   267,   267,   229,   229,   388,   757,   757,   757,   757,
     731,   731,   731,  -335,   321,   257,   124,  -335,   248,   498,
      49,   302,   307,   648,  -335,   123,   150,   324,   150,  -335,
     310,   312,   498,   304,   322,   306,   323,  -335,   272,   117,
     327,   328,   731,   153,   349,   313,  -335,  -335,  -335,  -335,
    -335,  -335,   156,  -335,    51,    58,  -335,   326,   254,   257,
      28,   352,   353,   329,   321,  -335,   352,   248,  -335,   238,
     238,    92,   272,   330,   123,   331,    -8,    92,  -335,   202,
    -335,   332,    12,  -335,   333,   334,    92,  -335,   335,   336,
     337,  -335,   123,   498,   338,  -335,   238,    80,  -335,    92,
     257,  -335,   257,   339,  -335,  -335,   179,   340,  -335,   348,
     194,  -335,   346,   350,   498,   351,   150,   272,   150,   498,
     498,   342,   257,   731,   304,  -335,   498,   257,   357,   306,
    -335,   498,   498,   119,  -335,   238,  -335,   272,  -335,   498,
     355,  -335,   359,    28,   361,   360,   238,  -335,    28,    49,
     363,    28,  -335,    49,  -335,  -335,   248,  -335,   366,   362,
     367,  -335,   248,   175,   344,  -335,   150,  -335,  -335,   306,
    -335,  -335,  -335,  -335,    35,   364,   248,   368,   159,   498,
    -335,  -335,   498,  -335,  -335,   188,   365,  -335,   149,  -335,
    -335,  -335,  -335,  -335,   387,   144,  -335,   148,   498,  -335,
    -335,   343,   356,   248,   704,  -335,   248,  -335,   370,    62,
    -335,  -335,  -335,   161,  -335,   375,   384,   400,   498,   498,
     498,   498,  -335,   498,   498,   498,   257,   376,  -335,  -335,
      35,   377,  -335,   150,    92,  -335,   248,  -335,   248,   342,
    -335,  -335,  -335,    35,   248,   393,   677,   498,   498,   498,
    -335,  -335,   386,   374,    92,   248,  -335,  -335,    35,   402,
     498,  -335,  -335,    28,   248,   181,   387,   403,   190,  -335,
    -335,   411,  -335
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -335,  -335,   427,  -335,  -335,    -6,  -335,   -53,   -17,  -335,
    -335,   231,    -3,  -335,  -335,  -335,  -218,  -108,  -335,  -335,
     210,   -13,  -155,   354,  -335,   -21,  -335,  -335,   416,   198,
    -335,  -335,  -335,  -335,  -110,  -100,  -335,  -335,  -335,  -335,
    -137,  -335,  -335,   133,  -335,  -335,  -335,  -279,  -335,   177,
      32,  -197,  -335,  -335,   -23,  -181,  -335,  -334,  -335,  -335,
     162,     9,  -335,  -335,   -82,   -18,  -335,  -335,    22,  -335,
    -335,  -335,  -335,  -335,    -2,  -335,  -335,  -124,   199,     3,
    -335,     6
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -144
static const yytype_int16 yytable[] =
{
      16,    39,   162,   220,   133,    33,    21,   208,   254,    22,
     275,    39,    73,    25,    57,    41,    36,     1,    16,    28,
     317,    32,   251,   253,    21,    40,    36,    22,    38,   100,
     396,     8,   254,  -105,    99,    40,   254,   309,    38,   363,
     360,   131,     8,   228,   305,    73,    73,   215,     8,    31,
      11,    12,     8,   256,   318,    32,   172,     9,    10,    73,
      73,    73,    73,   244,    32,    73,   419,    11,    12,    73,
      73,    11,    12,   299,   134,   135,    34,    39,   287,   263,
     395,   265,    39,    94,   216,   289,   434,   173,   332,   349,
       7,    32,   170,    35,   173,   254,   288,   175,    95,   441,
      29,    40,   301,   174,   171,   205,   178,   262,   333,   370,
      35,    25,   206,    39,   452,   356,    73,    13,    73,   209,
     356,    32,   334,   363,   207,   280,   294,    16,   175,   229,
      26,   153,   233,    21,    42,   217,    22,   178,   236,   237,
     238,   239,   240,   227,   276,   153,    16,   203,    32,    43,
     154,   148,    21,   255,    44,    22,   307,    45,    46,   302,
     303,   153,   277,    54,   154,   241,    47,   -45,   365,   348,
      52,   350,    44,    32,   327,    45,   231,    32,    48,   389,
     154,   148,   390,   203,    47,    49,   331,   285,    73,   408,
     400,   384,   421,   410,    26,   286,    48,   388,    11,    12,
     173,    73,   286,    49,   258,   286,    44,    16,    93,    45,
     312,   398,   457,    21,   379,   368,    22,   382,    47,   356,
      96,   461,     4,   405,   339,   340,   378,    96,     5,   173,
      48,   105,    39,    98,   108,   109,   110,    49,   415,   343,
     340,   417,   236,   237,   238,   239,   240,   175,   304,   -87,
     129,   130,   132,   310,   311,    95,   178,   137,   136,   139,
     138,   140,    73,   323,   105,   106,   107,   108,   109,   110,
     150,   438,   141,   439,   146,   147,   336,   116,   117,   442,
     148,   157,   166,    73,   167,   174,   105,   203,    73,    73,
     451,   211,   212,   403,   210,    73,   221,   144,   145,   456,
      73,    73,   105,   106,   107,   108,   109,   110,    73,   222,
     223,   158,   159,   160,   161,   375,   225,   163,   234,  -143,
      39,   164,   165,    39,   245,   246,   248,   249,   252,   259,
     374,   250,   264,   380,   260,   175,    16,   383,   175,    40,
      16,   266,    21,   267,   178,    22,    21,   178,    73,    22,
     269,    73,   272,   271,   274,   278,   -51,   281,   283,   290,
     295,   297,   298,   353,   325,   359,   324,    73,   214,   376,
     219,   381,   409,   458,   411,   306,   308,   316,   321,   322,
      50,   342,   326,   329,   338,   341,   420,    73,    73,    73,
      73,   344,    73,    73,    73,   345,   347,   385,   387,   406,
     372,   101,   102,   103,   373,   377,   413,   386,   392,   397,
     404,   437,   423,   424,   399,   418,    73,    73,    73,   414,
     422,   443,   433,   105,   106,   107,   108,   109,   110,    73,
     453,   450,   448,    23,   460,   455,   116,   117,   118,   119,
     257,   449,   462,   435,   282,    56,   291,   357,   432,   320,
     374,   440,   337,   268,   459,   300,     0,     0,   180,    40,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   105,   106,   107,   108,   109,   110,     0,   112,
     213,   114,     0,     0,   115,   116,   117,   118,   119,   120,
       0,     8,     0,     0,     0,     0,    58,     0,   232,     0,
       0,     0,    59,    60,   328,    61,    62,    63,    64,     0,
      11,    12,    65,    66,    67,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   346,     0,     0,     0,     0,
     351,   352,     0,     0,     0,     0,     0,   358,     0,     0,
       0,     0,   361,   362,     0,     0,     0,     0,    68,    69,
     371,   179,     0,    35,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,     0,     0,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
       0,     0,   105,   106,   107,   108,   109,   110,     0,   112,
     401,     0,     0,   402,   115,   116,   117,   118,   119,   120,
       0,     0,   104,   105,   106,   107,   108,   109,   110,   412,
     112,   113,   114,   313,     0,   115,   116,   117,   118,   119,
     120,     0,     0,     0,     0,     0,     0,     0,     0,   425,
     426,   427,   428,     0,   429,   430,   431,   105,   106,   107,
     108,   109,   110,     0,   112,   113,   114,     0,     0,   115,
     116,   117,   118,   119,   120,     0,     0,     0,   445,   446,
     447,     0,     0,     0,     0,     0,     0,     0,     0,   261,
       0,   454,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,     0,     0,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   444,     0,
     394,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,     0,     0,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   416,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,     0,
       0,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,     0,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,     0,   436,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,     0,     0,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   105,   106,   107,   108,   109,   110,
       0,     0,     0,     0,     0,     0,   115,   116,   117,   118,
     119,   120
};

static const yytype_int16 yycheck[] =
{
       3,    19,    84,   140,    57,    18,     3,   131,   205,     3,
     228,    29,    33,     8,    31,    21,    19,    10,    21,    13,
       8,    29,   177,   204,    21,    19,    29,    21,    19,    42,
     364,     3,   229,    28,     8,    29,   233,    45,    29,     4,
     319,    54,     3,   151,   262,    66,    67,     8,     3,     8,
      22,    23,     3,   208,    42,    29,     8,     8,     9,    80,
      81,    82,    83,     8,    29,    86,     4,    22,    23,    90,
      91,    22,    23,   254,    69,    70,    31,    95,    27,   216,
     359,   218,   100,    31,    45,    27,   420,    39,     8,   307,
       0,    29,    95,    65,    39,   292,    45,   100,    46,   433,
      62,    95,   257,    45,    95,   128,   100,   215,    28,   327,
      65,     8,   129,   131,   448,   312,   137,    68,   139,   132,
     317,    29,    42,     4,   130,   233,   250,   130,   131,   152,
      27,     8,   155,   130,     8,   138,   130,   131,     4,     5,
       6,     7,     8,   149,    27,     8,   149,    30,    29,    45,
      27,    32,   149,   206,     4,   149,   264,     7,     8,   259,
     260,     8,    45,     8,    27,    31,    16,    30,   323,   306,
      46,   308,     4,    29,   282,     7,     8,    29,    28,     4,
      27,    32,     7,    30,    16,    35,   286,    31,   209,    45,
      31,   346,    31,    45,    27,    46,    28,   352,    22,    23,
      39,   222,    46,    35,   210,    46,     4,   210,     8,     7,
       8,   366,    31,   210,   338,   325,   210,   341,    16,   416,
      39,    31,     5,   378,    45,    46,   336,    39,    11,    39,
      28,    35,   250,     8,    38,    39,    40,    35,   393,    45,
      46,   396,     4,     5,     6,     7,     8,   250,   261,    30,
       8,    45,    31,   266,   267,    46,   250,    45,    28,    45,
      28,    28,   283,   276,    35,    36,    37,    38,    39,    40,
       8,   426,    28,   428,    28,    28,   289,    48,    49,   434,
      32,    28,     8,   304,    30,    45,    35,    30,   309,   310,
     445,     8,     8,   375,    45,   316,     8,    66,    67,   454,
     321,   322,    35,    36,    37,    38,    39,    40,   329,    45,
       5,    80,    81,    82,    83,   333,     5,    86,    46,    30,
     338,    90,    91,   341,     8,     4,     8,     8,     8,    27,
     333,    45,     8,   339,    27,   338,   339,   343,   341,   333,
     343,    31,   339,    31,   338,   339,   343,   341,   369,   343,
      46,   372,    46,    31,    31,    28,    28,     8,    45,    33,
       8,     8,    33,    21,    28,     8,    31,   388,   137,     8,
     139,     8,   385,   455,   387,    45,    45,    45,    45,    45,
      26,    33,    45,    45,    45,    45,   399,   408,   409,   410,
     411,    45,   413,   414,   415,    45,    45,    31,    31,    12,
      45,    47,    48,    49,    45,    45,    63,    45,    64,    45,
      45,   424,    28,    13,    46,    45,   437,   438,   439,    63,
      45,    28,    46,    35,    36,    37,    38,    39,    40,   450,
      28,   444,    46,     6,    31,   453,    48,    49,    50,    51,
     209,    67,    31,    66,   234,    29,   248,   314,   416,   272,
     453,   429,   290,   222,   456,   256,    -1,    -1,   104,   453,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,    35,    36,    37,    38,    39,    40,    -1,    42,
     136,    44,    -1,    -1,    47,    48,    49,    50,    51,    52,
      -1,     3,    -1,    -1,    -1,    -1,     8,    -1,   154,    -1,
      -1,    -1,    14,    15,   283,    17,    18,    19,    20,    -1,
      22,    23,    24,    25,    26,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   304,    -1,    -1,    -1,    -1,
     309,   310,    -1,    -1,    -1,    -1,    -1,   316,    -1,    -1,
      -1,    -1,   321,   322,    -1,    -1,    -1,    -1,    60,    61,
     329,    31,    -1,    65,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    -1,    -1,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      -1,    -1,    35,    36,    37,    38,    39,    40,    -1,    42,
     369,    -1,    -1,   372,    47,    48,    49,    50,    51,    52,
      -1,    -1,    34,    35,    36,    37,    38,    39,    40,   388,
      42,    43,    44,   269,    -1,    47,    48,    49,    50,    51,
      52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   408,
     409,   410,   411,    -1,   413,   414,   415,    35,    36,    37,
      38,    39,    40,    -1,    42,    43,    44,    -1,    -1,    47,
      48,    49,    50,    51,    52,    -1,    -1,    -1,   437,   438,
     439,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,
      -1,   450,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    -1,    -1,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    31,    -1,
     356,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    -1,    -1,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    -1,
      -1,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    -1,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    -1,   423,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    -1,    -1,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    35,    36,    37,    38,    39,    40,
      -1,    -1,    -1,    -1,    -1,    -1,    47,    48,    49,    50,
      51,    52
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    10,    72,    73,     5,    11,    75,     0,     3,     8,
       9,    22,    23,    68,    76,    77,    83,    97,    98,   107,
     147,   150,   152,    73,    74,     8,    27,    79,   152,    62,
      80,     8,    29,    92,    31,    65,    83,    99,   132,   136,
     152,    76,     8,    45,     4,     7,     8,    16,    28,    35,
      94,    96,    46,    78,     8,    81,    99,    79,     8,    14,
      15,    17,    18,    19,    20,    24,    25,    26,    60,    61,
      82,    83,    84,    96,   101,   104,   108,   109,   112,   116,
     124,   127,   133,   134,   136,   138,   142,   143,   144,   146,
     150,   151,   152,     8,    31,    46,    39,   135,     8,     8,
      92,    94,    94,    94,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    95,     8,
      45,    92,    31,    78,    69,    70,    28,    45,    28,    45,
      28,    28,    94,   111,    82,    82,    28,    28,    32,    93,
       8,    91,   123,     8,    27,    85,    88,    28,    82,    82,
      82,    82,   135,    82,    82,    82,     8,    30,   100,   130,
      83,   132,     8,    39,    45,    83,   132,   148,   152,    31,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    30,   122,   125,    79,    76,   148,    92,
      45,     8,     8,    94,    82,     8,    45,    83,   110,    82,
     111,     8,    45,     5,   113,     5,   117,    76,    88,   125,
      90,     8,    94,   125,    46,    87,     4,     5,     6,     7,
       8,    31,   105,   106,     8,     8,     4,   126,     8,     8,
      45,    93,     8,   126,   122,    78,    93,    82,    76,    27,
      27,    31,    88,   111,     8,   111,    31,    31,    82,    46,
     114,    31,    46,   118,    31,    87,    27,    45,    28,    89,
      88,     8,    91,    45,   103,    31,    46,    27,    45,    27,
      33,   100,   125,   131,   148,     8,   149,     8,    33,   126,
     149,    93,   106,   106,    92,    87,    45,    88,    45,    45,
      92,    92,     8,    94,   115,   120,    45,     8,    42,   119,
     120,    45,    45,    92,    31,    28,    45,    88,    82,    45,
     102,   106,     8,    28,    42,   137,    92,   131,    45,    45,
      46,    45,    33,    45,    45,    45,    82,    45,   111,    87,
     111,    82,    82,    21,   139,   121,   122,   114,    82,     8,
     118,    82,    82,     4,    92,    93,   128,   129,   105,    86,
      87,    82,    45,    45,    83,   136,     8,    45,   105,   148,
      76,     8,   148,    76,    93,    31,    45,    31,    93,     4,
       7,   141,    64,   140,    94,   118,   128,    45,    93,    46,
      31,    82,    82,   135,    45,    93,    12,   145,    45,    92,
      45,    92,    82,    63,    63,    93,    33,    93,    45,     4,
      92,    31,    45,    28,    13,    82,    82,    82,    82,    82,
      82,    82,   121,    46,   128,    66,    94,    92,    93,    93,
     139,   128,    93,    28,    31,    82,    82,    82,    46,    67,
      92,    93,   128,    28,    82,   136,    93,    31,   135,   145,
      31,    31,    31
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 437 ".\\semanticAnalysis.y"
    {printf("Syntax is Correct\n");return;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 458 ".\\semanticAnalysis.y"
    {
            strcpy(typeBuffer,(yyvsp[(1) - (1)].type));
            (yyval.type)=malloc(strlen((yyvsp[(1) - (1)].type))+1);
            strcpy((yyval.type),(yyvsp[(1) - (1)].type));
        }
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 465 ".\\semanticAnalysis.y"
    {dimit = 0;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 465 ".\\semanticAnalysis.y"
    {
            struct SymbolTableEntry * entry=lookup(IDBuffer,scope,false);            
            if(entry->dimension != dimit)
            {
                char const errorMessage[100]="Dimension doesnt match!";
                int a=yyerror(errorMessage);
                return -1;
            }
            for(int i =0;i<dimit;i++)
            {
                if(entry->dimSize[i] <= dimbuffer[i] || dimbuffer[i] < 0)
                {
                    char const errorMessage[100]="Invalid Access";
                    int a=yyerror(errorMessage);
                    return -1;
                }
            }
            dimit = 0;
        }
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 486 ".\\semanticAnalysis.y"
    {
    struct SymbolTableEntry * search=lookup((yyvsp[(2) - (2)].value),scope,false);
    if(search==NULL){
        char message[30]="Function Not Declared";
        int res=yyerror(message);
        return -1;
    }
    else{
        update(search,yylinenumber);
    }
}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 496 ".\\semanticAnalysis.y"
    {
    struct SymbolTableEntry * search=lookup((yyvsp[(1) - (1)].value),scope,false);
    if(search==NULL){
        char message[30]="Function Not Declared";
        int res=yyerror(message);
        return -1;
    }
    else{
        update(search,yylinenumber);
    }
}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 508 ".\\semanticAnalysis.y"
    {
    struct SymbolTableEntry * search=lookup((yyvsp[(1) - (1)].value),scope,true);
    if(search!=NULL){
        char message[30]="Variable Already Declared";
        int res=yyerror(message);
        return -1;
    }
    else{
        struct SymbolTableEntry*new_entry=insertIdentifier((yyvsp[(1) - (1)].value),CLASS[0],typeBuffer,0,yylinenumber,scope);
    }
}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 520 ".\\semanticAnalysis.y"
    {scope++;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 521 ".\\semanticAnalysis.y"
    {deleteDMT(scope);scope--;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 550 ".\\semanticAnalysis.y"
    {dimit = 0;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 551 ".\\semanticAnalysis.y"
    {dimit = 0;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 554 ".\\semanticAnalysis.y"
    {

    struct SymbolTableEntry * found=lookup((yyvsp[(1) - (1)].value),scope,false);
        strcpy(IDBuffer,(yyvsp[(1) - (1)].value));
        if(found==NULL){
            char const errorMessage[100]="Variable Not Declared!!";
            int a=yyerror(errorMessage);
            return -1;
        }
        else{
            update(found,yylinenumber);
        }
    }
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 570 ".\\semanticAnalysis.y"
    {
    struct SymbolTableEntry * entry = lookup(funNameBuffer,1,true);
    if(entry!=NULL){
        char message[40]="Function name is Already Declared";
        int res=yyerror(message);
        return -1;
    }
    struct SymbolTableEntry* new_entry = insertFunction(funNameBuffer,CLASS[1],funTypeBuffer,0,yylinenumber,scope,noOfParameters,PL,PTL);
    noOfParameters=0;
}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 580 ".\\semanticAnalysis.y"
    {
                        struct SymbolTableEntry * entry = lookup(funNameBuffer,1,true);
                        if(entry!=NULL){
                            char message[40]="Function name is Already Declared";
                            int res=yyerror(message);
                            return -1;
                        }
                        struct SymbolTableEntry* new_entry = insertFunction(funNameBuffer,CLASS[1],funTypeBuffer,0,yylinenumber,scope,noOfParameters,PL,PTL);
                        noOfParameters=0;
                      }
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 590 ".\\semanticAnalysis.y"
    {
    char flag;
    if(strcmp((yyvsp[(5) - (5)].type),"array")==0){
        flag='a';
    }
    else{
        flag='v';
    }
    char T[10];
    if(flag=='v'){
        strcpy(T,CLASS[0]);
    }
    else{
        strcpy(T,CLASS[2]);
    }
    struct SymbolTableEntry * search=lookup((yyvsp[(4) - (5)].value),scope+1,true);
    if(search!=NULL){
        char message[30]="Variable Already Declared";
        int res=yyerror(message);
        return -1;
    }
    else if(strcmp(T,"variable")==0){
        struct SymbolTableEntry*new_entry = insertIdentifier((yyvsp[(4) - (5)].value),T,(yyvsp[(3) - (5)].type),0,yylinenumber,scope+1);
    }
    else if(strcmp(T,"array")==0){
        struct SymbolTableEntry*new_entry = insertArray((yyvsp[(4) - (5)].value),T,(yyvsp[(3) - (5)].type),dimit,yylinenumber,scope+1,dimbuffer);
    }
    PD[noOfParameters]=dimit;
    dimit=0;
    strcpy(PL[noOfParameters],(yyvsp[(3) - (5)].type));
    PTL[noOfParameters]=flag;
    noOfParameters++;
}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 625 ".\\semanticAnalysis.y"
    {
                    struct SymbolTableEntry * search=lookup((yyvsp[(2) - (3)].value),scope+1,true);
                    if(search!=NULL){
                        char message[30]="Variable Already Declared";
                        int res=yyerror(message);
                        return -1;
                    }
                    else if(strcmp((yyvsp[(3) - (3)].type),"variable")==0){
                        struct SymbolTableEntry*new_entry = insertIdentifier((yyvsp[(2) - (3)].value),(yyvsp[(3) - (3)].type),(yyvsp[(1) - (3)].type),0,yylinenumber,scope+1);
                    }
                    else if(strcmp((yyvsp[(3) - (3)].type),"array")==0){
                        struct SymbolTableEntry*new_entry = insertArray((yyvsp[(2) - (3)].value),(yyvsp[(3) - (3)].type),(yyvsp[(1) - (3)].type),dimit,yylinenumber,scope+1,dimbuffer);
                    }
                    PD[noOfParameters]=dimit;
                    dimit=0;
                    strcpy(PL[noOfParameters],(yyvsp[(1) - (3)].type));
                    if(strcmp((yyvsp[(3) - (3)].type),"array")==0)PTL[noOfParameters]='a';
                    else if(strcmp((yyvsp[(3) - (3)].type),"variable")==0) PTL[noOfParameters]='v';
                    noOfParameters++;
                }
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 645 ".\\semanticAnalysis.y"
    {
    (yyval.type)=malloc(strlen("array")+1);strcpy((yyval.type),"array");

    }
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 648 ".\\semanticAnalysis.y"
    {(yyval.type)=malloc(strlen("variable")+1);strcpy((yyval.type),"variable");}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 651 ".\\semanticAnalysis.y"
    {
    int nop=forFunc->noOfParams;
    if(noOfParameters!=nop){
        char message[50]="No of Parameters of the Function Does not match";
        int res=yyerror(message);
        return -1;
    }
 
    for(int i=0;i<nop;i++){
        if(strcmp(PL[i],forFunc->paraList[i])!=0){
            char message[50]="DataTypes of Parameters did not match";
            int res=yyerror(message);
            return -1;
        }
    }
    
    for(int i=0;i<nop;i++){
        if(PTL[i]!=forFunc->paraTypes[i]){
            char message[40]="Type(Class) of Parameters did not match";
            int res=yyerror(message);
            return -1;
        }
    }

    for(int i=0;i<nop;i++){
        if(parD[i]!=forFunc->paraDim[i]){
            char message[40]="Dimension does not match";
            int res=yyerror(message);
            return -1;
        }
    }
    parDi=0;
    noOfParameters=0;
}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 685 ".\\semanticAnalysis.y"
    {
                    int nop=forFunc->noOfParams;
                    
                    if(noOfParameters!=nop){
                        char message[50]="No of Parameters of the Function Does not match";
                        int res=yyerror(message);
                        return -1;
                    }
                    char temp[20];
                    char t;
                    for(int i=0;i<nop/2;i++){
                        strcpy(temp,PL[i]);
                        strcpy(PL[i],PL[nop-i-1]);
                        strcpy(PL[nop-i-1],temp);
                        t=PTL[i];
                        PTL[i]=PTL[nop-i-1];
                        PTL[nop-i-1]=t;
                    }

                    for(int i=0;i<nop;i++){
                        if(strcmp(PTL[i],forFunc->paraList[i])!=0){
                            char message[40]="DataTypes of Parameters did not match";
                            int res=yyerror(message);
                            return -1;
                        }
                    }

                    for(int i=0;i<nop;i++){
                        if(PTL[i]!=forFunc->paraTypes[i]){
                            char message[40]="Type(Class) of Parameters did not match";
                            int res=yyerror(message);
                            return -1;
                        }
                    }
                    for(int i=0;i<nop;i++){
                        if(parD[i]!=forFunc->paraDim[i]){
                            char message[40]="Dimension does not match";
                            int res=yyerror(message);
                            return -1;
                        }
                    }

                    parDi=0;
                    noOfParameters=0;
                }
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 731 ".\\semanticAnalysis.y"
    {
    forFunc = lookup((yyvsp[(1) - (1)].value),1,true);
    if(forFunc==NULL){
        char message[40]="Function is not Declared/Defined";
        int res=yyerror(message);
        return -1;
    }
    else if(strcmp(forFunc->type,CLASS[1])!=0){
        char message[40]="Function is not Declared/Defined";
        int res=yyerror(message);
        return -1;
    }
    else{
        //Update line number
        update(forFunc,yylinenumber);
    }
}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 748 ".\\semanticAnalysis.y"
    {
    strcpy(PL[noOfParameters],(yyvsp[(1) - (1)].type));
    PTL[noOfParameters]=pt;
    noOfParameters++;
}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 753 ".\\semanticAnalysis.y"
    {
            strcpy(PL[noOfParameters],(yyvsp[(3) - (3)].type));
            PTL[noOfParameters]=pt;
            noOfParameters++;
        }
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 758 ".\\semanticAnalysis.y"
    {
    struct SymbolTableEntry * entry = lookup((yyvsp[(1) - (1)].value),scope,false);
    if(entry==NULL){
        char message[40]="Variable is not Declared";
        int res=yyerror(message);
        return -1;
    }
    if(strcmp(entry->type,CLASS[0])==0){
        pt='v';
        parD[parDi++]=entry->dimension;
        update(entry,yylinenumber);
    }
    else if(strcmp(entry->type,CLASS[1])==0){
        char message[40]="Variable not declared";
        int res=yyerror(message);
        return -1;
    }
    else if(strcmp(entry->type,CLASS[2])==0){
        pt='a';
        parD[parDi++]=entry->dimension;
        update(entry,yylinenumber);
    }
    (yyval.type)=malloc(strlen(entry->dataType)+1);strcpy((yyval.type),entry->dataType);}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 781 ".\\semanticAnalysis.y"
    {(yyval.type)=malloc(strlen((yyvsp[(1) - (1)].type))+1);strcpy((yyval.type),(yyvsp[(1) - (1)].type));pt='v';parD[parDi++]=0;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 782 ".\\semanticAnalysis.y"
    {(yyval.type)=malloc(strlen((yyvsp[(1) - (1)].type))+1);strcpy((yyval.type),(yyvsp[(1) - (1)].type));pt='v';parD[parDi++]=0;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 783 ".\\semanticAnalysis.y"
    {(yyval.type)=malloc(strlen((yyvsp[(1) - (1)].type))+1);strcpy((yyval.type),(yyvsp[(1) - (1)].type));pt='v';parD[parDi++]=0;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 784 ".\\semanticAnalysis.y"
    {(yyval.type)=malloc(strlen((yyvsp[(1) - (1)].type))+1);strcpy((yyval.type),(yyvsp[(1) - (1)].type));pt='v';parD[parDi++]=0;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 786 ".\\semanticAnalysis.y"
    {
    char Type[10];
    int Index=0;
    int i=0;
    int yl=strlen((yyvsp[(1) - (1)].value));
    for(;i<yl;i++){
        if((yyvsp[(1) - (1)].value)[i]!=' '){
            Type[Index++]=(yyvsp[(1) - (1)].value)[i];
        }
        else{
            Type[Index++]='\0';
            break;
        }
    }
    strcpy(funTypeBuffer,Type);
    while((yyvsp[(1) - (1)].value)[i]==' '){
        i++;
    }
    char iden[30];
    Index=0;
    for(;i<yl;i++){
        if((yyvsp[(1) - (1)].value)[i]!='(' && (yyvsp[(1) - (1)].value)[i]!=' '){
            iden[Index++]=(yyvsp[(1) - (1)].value)[i];
        }
        else{
            iden[Index++]='\0';
            break;
        }
    }
    strcpy(funNameBuffer,iden);
}
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 850 ".\\semanticAnalysis.y"
    {ID_dim++;}
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 852 ".\\semanticAnalysis.y"
    {
        struct SymbolTableEntry * found=lookup((yyvsp[(1) - (1)].value),scope,true);
        if(found != NULL)
        {
            char const errorMessage[100]="Variable Already Declared!!";
            int a=yyerror(errorMessage);
            return -1;
        }

        strcpy(IDBuffer,(yyvsp[(1) - (1)].value));

        }
    break;

  case 144:

/* Line 1455 of yacc.c  */
#line 866 ".\\semanticAnalysis.y"
    {struct SymbolTableEntry* temp = insertArray(IDBuffer,CLASS[2],typeBuffer,dimit,yylinenumber,scope,dimbuffer);dimit = 0;}
    break;

  case 147:

/* Line 1455 of yacc.c  */
#line 869 ".\\semanticAnalysis.y"
    {dimbuffer[dimit++] = intval;}
    break;



/* Line 1455 of yacc.c  */
#line 2905 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 919 ".\\semanticAnalysis.y"


int yyerror(const char *s){
    extern int yylinenumber;
    printf("Error : %s!! \nLine No : %d\n",s,yylinenumber);
}

int main(){
    for (int i=0; i<TABLE_SIZE;i++) {
        Table.symTable[i] = NULL;
    }
    yyin=fopen("input.txt","r");
    yyparse();
    printf("\n\nSYMBOL TABLE\n\n");
    printf("%-15s %-10s %-15s %-15s %-15s %-15s %-15s %-20s\n", "ID", "Type", "Data Type","Dim","Scope","No of Params","Line of Decl","Line of Ref");
    printf("------------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < stIterator; i++) {
        printf("%d ",i);
        struct SymbolTableEntry * entry = Table.symTable[i];
        printf("%-15s %-10s %-15s %-15d %-15d %-15d %-15d [ ", entry->name, entry->type, entry->dataType,entry->dimension,entry->scope,entry->noOfParams,entry->lineOfDeclaration);
        struct lines* h = entry->head->next;
        while(h){
            printf("%d ", h->lineno);
            h = h->next;
        }
        printf("]\n");
    }
    printf("------------------------------------------------------------------------------------------------------------------------------\n");
    printf("\n\n");
    fclose(yyin);
}
