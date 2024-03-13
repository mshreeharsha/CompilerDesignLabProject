
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
#line 1 "semanticAnalysis.y"

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
    int dimbuffer[30];
    int dimit = 0;

    int pointerLen = 1;
    char ptrBuf[100];
    int ptrBI=0;

    int PD[20];
    int pdi=0;

    //Datatypes
    char datatypesArray[][20]={"int","char","float","string"};
    char CLASS[][20]={"variable","function","array","pointer","userDefType"};
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
    char userTypeBuffer[10];
    char userTypeNameBuffer[10];
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
    int userTypeDim = 0;


/* Line 189 of yacc.c  */
#line 486 "y.tab.c"

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

/* Line 214 of yacc.c  */
#line 413 "semanticAnalysis.y"

    char * value;
    char * type;



/* Line 214 of yacc.c  */
#line 673 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 685 "y.tab.c"

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
#define YYLAST   933

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  73
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  104
/* YYNRULES -- Number of rules.  */
#define YYNRULES  240
/* YYNRULES -- Number of states.  */
#define YYNSTATES  522

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   327

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
      65,    66,    67,    68,    69,    70,    71,    72
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     7,    11,    13,    14,    16,    18,    20,
      22,    24,    27,    28,    31,    34,    37,    40,    47,    53,
      58,    59,    64,    65,    68,    71,    74,    75,    77,    79,
      80,    88,    90,    91,    93,    95,    97,    99,   101,   103,
     108,   112,   116,   119,   122,   125,   128,   130,   133,   136,
     139,   142,   145,   146,   148,   156,   163,   169,   170,   171,
     179,   180,   186,   187,   193,   198,   199,   202,   205,   208,
     211,   212,   214,   216,   218,   222,   226,   230,   234,   238,
     242,   246,   250,   254,   258,   261,   264,   267,   271,   275,
     279,   283,   287,   291,   295,   299,   303,   307,   311,   315,
     319,   323,   325,   326,   330,   332,   334,   336,   342,   346,
     349,   355,   359,   361,   365,   367,   368,   369,   377,   378,
     385,   386,   393,   394,   400,   402,   404,   408,   410,   412,
     414,   416,   418,   420,   422,   434,   444,   456,   466,   468,
     477,   484,   490,   495,   497,   498,   500,   507,   512,   514,
     517,   521,   524,   526,   533,   538,   541,   546,   550,   554,
     557,   559,   560,   564,   566,   571,   576,   580,   582,   584,
     593,   601,   603,   606,   614,   621,   627,   631,   636,   642,
     644,   648,   653,   655,   656,   660,   665,   666,   675,   676,
     684,   691,   693,   695,   698,   700,   703,   705,   707,   720,
     732,   742,   748,   749,   753,   754,   756,   758,   760,   762,
     764,   777,   786,   787,   796,   797,   808,   809,   819,   823,
     827,   831,   834,   837,   840,   842,   846,   847,   849,   852,
     856,   863,   864,   872,   873,   881,   883,   885,   887,   891,
     895
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      74,     0,    -1,    75,    78,    85,    -1,    14,    77,    76,
      -1,    75,    -1,    -1,     6,    -1,    16,    -1,   103,    -1,
      79,    -1,   162,    -1,   168,    78,    -1,    -1,   135,    78,
      -1,   138,    78,    -1,   145,    78,    -1,   144,    78,    -1,
      89,    83,    82,    80,    48,    78,    -1,    84,    82,    81,
      48,    78,    -1,    49,    83,    82,    80,    -1,    -1,    49,
      84,    82,    80,    -1,    -1,    30,   100,    -1,    30,   110,
      -1,    30,   124,    -1,    -1,    12,    -1,    12,    -1,    -1,
      65,    87,    34,    86,    98,    88,    99,    -1,   105,    -1,
      -1,    90,    -1,   123,    -1,   128,    -1,   107,    -1,   119,
      -1,   117,    -1,    27,   121,    48,    88,    -1,    23,    48,
      88,    -1,    20,    48,    88,    -1,    28,    88,    -1,    29,
      88,    -1,   135,    88,    -1,   138,    88,    -1,   153,    -1,
     145,    88,    -1,   144,    88,    -1,   157,    88,    -1,   168,
      88,    -1,   169,    88,    -1,    -1,     4,    -1,    15,    89,
      97,    96,    95,    48,    88,    -1,    89,    97,    96,    95,
      48,    88,    -1,   102,    96,    95,    48,    88,    -1,    -1,
      -1,   102,    91,   136,    96,    48,    92,    88,    -1,    -1,
      12,    93,    38,    48,    88,    -1,    -1,    38,    12,    48,
      94,    88,    -1,    49,    97,    96,    95,    -1,    -1,    30,
     100,    -1,    30,   110,    -1,    30,   124,    -1,    30,   129,
      -1,    -1,    12,    -1,    32,    -1,    35,    -1,    31,   100,
      34,    -1,   100,    39,   100,    -1,   100,    40,   100,    -1,
     100,    42,   100,    -1,   100,    41,   100,    -1,   100,    43,
     100,    -1,   100,    44,   100,    -1,   100,    37,   100,    -1,
     100,    47,   100,    -1,   100,    45,   100,    -1,   100,    38,
      -1,    38,   100,    -1,    21,   100,    -1,   100,    46,   100,
      -1,   100,    50,   100,    -1,   100,    51,   100,    -1,   100,
      52,   100,    -1,   100,    53,   100,    -1,   100,    54,   100,
      -1,   100,    55,   100,    -1,   100,    56,   100,    -1,   100,
      57,   100,    -1,   100,    58,   100,    -1,   100,    59,   100,
      -1,   100,    60,   100,    -1,   100,    61,   100,    -1,   100,
      62,   100,    -1,   102,    -1,    -1,   102,   101,   136,    -1,
       5,    -1,     8,    -1,    12,    -1,   104,    98,    88,    99,
      78,    -1,   116,   105,    34,    -1,   116,    34,    -1,   105,
      49,    89,    12,   106,    -1,   105,    49,   143,    -1,   143,
      -1,    89,    12,   106,    -1,   141,    -1,    -1,    -1,   113,
      31,   114,    34,   108,    48,    88,    -1,    -1,   113,    31,
      34,   109,    48,    88,    -1,    -1,   113,    31,   114,    34,
     111,    88,    -1,    -1,   113,    31,    34,   112,    88,    -1,
      12,    -1,   115,    -1,   114,    49,   115,    -1,    12,    -1,
       5,    -1,     6,    -1,     8,    -1,     7,    -1,     3,    -1,
      13,    -1,   118,    31,   120,   121,    48,   121,    34,    32,
      88,    99,    88,    -1,   118,    31,   120,   121,    48,   121,
      34,    48,    88,    -1,   118,    31,    48,   121,    48,   121,
      34,    98,    88,    99,    88,    -1,   118,    31,    48,   121,
      48,   121,    34,    48,    88,    -1,    22,    -1,    24,    31,
     121,    34,    98,    88,    99,    88,    -1,    24,    31,   121,
      34,    48,    88,    -1,    89,   122,    96,    95,    48,    -1,
     122,    96,    95,    48,    -1,   100,    -1,    -1,    12,    -1,
      63,    31,   125,    34,    48,    88,    -1,    63,    31,   125,
      34,    -1,     6,    -1,     6,   126,    -1,    49,   127,   126,
      -1,    49,   127,    -1,   100,    -1,    64,    31,   130,    34,
      48,    88,    -1,    64,    31,   130,    34,    -1,     6,   131,
      -1,    49,    45,   102,   131,    -1,    49,    45,   102,    -1,
      49,   132,   131,    -1,    49,   132,    -1,   102,    -1,    -1,
      12,   133,   136,    -1,    12,    -1,    89,   134,   136,    48,
      -1,   136,    33,   137,    36,    -1,    33,   137,    36,    -1,
       5,    -1,    12,    -1,    89,   134,   136,    30,    98,   139,
      99,    48,    -1,    89,   134,   136,    30,    98,    99,    48,
      -1,   140,    -1,   140,    49,    -1,   140,    49,    98,   139,
      99,    49,   139,    -1,   140,    49,    98,   139,    99,    49,
      -1,   140,    49,    98,   139,    99,    -1,    98,   139,    99,
      -1,    98,   139,    99,    49,    -1,    98,   139,    99,    49,
     139,    -1,     5,    -1,   140,    49,     5,    -1,    33,   137,
      36,   142,    -1,   136,    -1,    -1,   151,   150,    12,    -1,
     151,   150,   148,    48,    -1,    -1,   151,   150,   148,    30,
      45,   149,   146,    48,    -1,    -1,   151,   150,   148,    30,
     149,   147,    48,    -1,   151,   150,   148,    30,   152,    48,
      -1,    12,    -1,    12,    -1,   150,    42,    -1,    42,    -1,
     172,    12,    -1,    89,    -1,    11,    -1,    31,   151,   150,
      34,    68,    31,    69,    31,   151,   150,    34,    34,    -1,
      31,   151,   150,    34,    68,    31,    69,    31,   151,    34,
      34,    -1,    25,    31,    12,    34,    98,   154,   155,    99,
      88,    -1,    26,   156,    66,    88,   154,    -1,    -1,    67,
      66,    88,    -1,    -1,     8,    -1,     5,    -1,   158,    -1,
     159,    -1,   161,    -1,    19,    31,   100,    34,    98,    88,
      99,   160,    18,    98,    88,    99,    -1,    17,    31,   100,
      34,    98,    88,    99,   160,    -1,    -1,    19,    31,   100,
      34,    98,    88,    99,   160,    -1,    -1,    70,   172,   173,
      98,   165,    99,   163,   166,    48,    78,    -1,    -1,   172,
     173,    98,   165,    99,   164,   166,    48,    78,    -1,   175,
      48,   165,    -1,   174,    48,   165,    -1,   176,    48,   165,
      -1,   175,    48,    -1,   174,    48,    -1,   176,    48,    -1,
     167,    -1,   166,    49,   167,    -1,    -1,    12,    -1,   176,
      48,    -1,    12,    12,    48,    -1,   176,    30,    98,   114,
      99,    48,    -1,    -1,    12,    71,    12,   170,    30,   115,
      48,    -1,    -1,    12,    72,    12,   171,    30,   115,    48,
      -1,     9,    -1,    10,    -1,    12,    -1,   151,   150,    12,
      -1,    89,    12,   142,    -1,   172,    12,    12,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   440,   440,   441,   442,   442,   443,   443,   445,   445,
     445,   445,   445,   446,   446,   446,   446,   448,   449,   450,
     450,   451,   451,   452,   452,   458,   458,   460,   471,   483,
     483,   484,   484,   486,   486,   486,   486,   486,   486,   487,
     487,   487,   488,   488,   488,   488,   489,   489,   489,   489,
     490,   490,   490,   492,   497,   498,   499,   500,   500,   500,
     519,   519,   530,   530,   542,   542,   543,   543,   549,   549,
     549,   551,   563,   564,   566,   567,   568,   569,   570,   571,
     572,   573,   574,   575,   576,   577,   578,   579,   580,   581,
     582,   583,   584,   585,   586,   587,   588,   589,   590,   591,
     592,   593,   594,   594,   604,   604,   606,   619,   620,   631,
     642,   675,   682,   690,   710,   713,   716,   716,   751,   751,
     799,   799,   834,   834,   880,   897,   902,   907,   935,   936,
     937,   938,   939,   941,   974,   975,   976,   977,   979,   981,
     982,   984,   985,   987,   987,   989,  1001,  1002,  1003,  1004,
    1005,  1006,  1007,  1009,  1010,  1011,  1012,  1013,  1014,  1015,
    1016,  1016,  1016,  1036,  1049,  1059,  1059,  1061,  1061,  1062,
    1071,  1080,  1081,  1082,  1083,  1084,  1085,  1086,  1087,  1088,
    1088,  1090,  1091,  1091,  1093,  1108,  1109,  1109,  1112,  1112,
    1116,  1118,  1132,  1144,  1146,  1147,  1147,  1147,  1148,  1149,
    1151,  1152,  1152,  1153,  1153,  1154,  1154,  1156,  1157,  1157,
    1158,  1159,  1159,  1160,  1162,  1162,  1167,  1166,  1172,  1173,
    1174,  1175,  1176,  1177,  1180,  1180,  1180,  1182,  1195,  1195,
    1196,  1197,  1197,  1219,  1219,  1242,  1247,  1253,  1264,  1279,
    1299
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NULLT", "TYPE", "INTEGER", "STRING",
  "FLOATING_NUM", "CHAR_CONST", "STRUCT", "UNION", "VOID", "ID",
  "FUN_START", "INCLUDE", "CONST", "PREDEF_HEADER", "ELIF", "ELSE", "IF",
  "BREAK", "NOT", "FOR", "CONTINUE", "WHILE", "SWITCH", "CASE", "RETURN",
  "SL_COMMENT", "ML_COMMENT", "EQUALTO", "OPEN_BRACK", "OPEN_FLOWER",
  "OPEN_SQ", "CLOSE_BRACK", "CLOSE_FLOWER", "CLOSE_SQ", "AND", "UNARY_OP",
  "PLUS", "MINUS", "DIV", "MUL", "MOD", "OR", "AMPERSAND", "BIT_OR",
  "BIT_XOR", "SEMICOLON", "COMMA", "ISEQUALTO", "LT", "LTE", "GT", "GTE",
  "NE", "PLUS_ET", "MINUS_ET", "MUL_ET", "DIV_ET", "OR_ET", "AND_ET",
  "XOR_ET", "PRINTF", "SCANF", "MAIN", "COLON", "DEFAULT", "MALLOC",
  "SIZEOF", "TYPEDEF", "DOT", "ARROW", "$accept", "start", "header",
  "newHeader", "file", "startGlobal", "globalVarDec", "DGd", "DGl",
  "optionsG", "idgi", "idgl", "main", "$@1", "mainParameters", "start1",
  "type", "varDec", "$@2", "$@3", "$@4", "$@5", "D", "options", "id",
  "open_flower", "close_flower", "Exp", "$@6", "id3", "function_defn",
  "function_declaration", "parameter_list", "choice", "function_call",
  "$@7", "$@8", "function_call1", "$@9", "$@10", "funName", "params",
  "item", "fun_start", "for", "forScope", "while", "varDecF", "ExpF",
  "idFor", "print", "printVar", "printExpr", "printArguments",
  "printContent", "scanf", "scanfVar", "scanfExpr", "scanfArguments",
  "scanfContent", "$@11", "ID2", "arrayDeclr", "BOX", "integer_dim",
  "arrayInitial", "BALANCED_BRACK", "arrayParams_unend",
  "arrayAsAParameter", "higherDimention", "pointerAsAParameter",
  "PTR_DECLR", "PTR_INITIAL", "$@12", "$@13", "idinsert", "idlook",
  "PTR_STAR", "PTR_TYPE", "PTR_EXP", "switch", "switchcase", "default",
  "comp", "ifElseLadder", "S", "matched", "elif", "unmatched",
  "userTypeDefination", "$@14", "$@15", "userTypeParams", "userTypeObj",
  "uIDi", "userTypeDeclaration", "userTypeInitialization", "$@16", "$@17",
  "userDefDataType", "sidi", "pointerInStruct", "varInStruct",
  "structInStruct", 0
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
     325,   326,   327
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    73,    74,    75,    76,    76,    77,    77,    78,    78,
      78,    78,    78,    78,    78,    78,    78,    79,    79,    80,
      80,    81,    81,    82,    82,    82,    82,    83,    84,    86,
      85,    87,    87,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    89,    90,    90,    90,    91,    92,    90,
      93,    90,    94,    90,    95,    95,    96,    96,    96,    96,
      96,    97,    98,    99,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   101,   100,   100,   100,   102,   103,   104,   104,
     105,   105,   105,   105,   106,   106,   108,   107,   109,   107,
     111,   110,   112,   110,   113,   114,   114,   115,   115,   115,
     115,   115,   115,   116,   117,   117,   117,   117,   118,   119,
     119,   120,   120,   121,   121,   122,   123,   124,   125,   125,
     126,   126,   127,   128,   129,   130,   131,   131,   131,   131,
     132,   133,   132,   134,   135,   136,   136,   137,   137,   138,
     138,   139,   139,   139,   139,   139,   139,   139,   139,   140,
     140,   141,   142,   142,   143,   144,   146,   145,   147,   145,
     145,   148,   149,   150,   150,   151,   151,   151,   152,   152,
     153,   154,   154,   155,   155,   156,   156,   157,   158,   158,
     159,   160,   160,   161,   163,   162,   164,   162,   165,   165,
     165,   165,   165,   165,   166,   166,   166,   167,   168,   168,
     169,   170,   169,   171,   169,   172,   172,   173,   174,   175,
     176
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     3,     1,     0,     1,     1,     1,     1,
       1,     2,     0,     2,     2,     2,     2,     6,     5,     4,
       0,     4,     0,     2,     2,     2,     0,     1,     1,     0,
       7,     1,     0,     1,     1,     1,     1,     1,     1,     4,
       3,     3,     2,     2,     2,     2,     1,     2,     2,     2,
       2,     2,     0,     1,     7,     6,     5,     0,     0,     7,
       0,     5,     0,     5,     4,     0,     2,     2,     2,     2,
       0,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     0,     3,     1,     1,     1,     5,     3,     2,
       5,     3,     1,     3,     1,     0,     0,     7,     0,     6,
       0,     6,     0,     5,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,    11,     9,    11,     9,     1,     8,
       6,     5,     4,     1,     0,     1,     6,     4,     1,     2,
       3,     2,     1,     6,     4,     2,     4,     3,     3,     2,
       1,     0,     3,     1,     4,     4,     3,     1,     1,     8,
       7,     1,     2,     7,     6,     5,     3,     4,     5,     1,
       3,     4,     1,     0,     3,     4,     0,     8,     0,     7,
       6,     1,     1,     2,     1,     2,     1,     1,    12,    11,
       9,     5,     0,     3,     0,     1,     1,     1,     1,     1,
      12,     8,     0,     8,     0,    10,     0,     9,     3,     3,
       3,     2,     2,     2,     1,     3,     0,     1,     2,     3,
       6,     0,     7,     0,     7,     1,     1,     1,     3,     3,
       3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,    12,     6,     7,     5,     1,    53,   235,
     236,   197,    28,   133,     0,     0,     9,    26,   196,     8,
       0,     0,    12,    12,    12,    12,     0,    10,    12,     0,
       0,     4,     3,     0,     0,    32,     2,     0,    22,    27,
      26,     0,    72,    52,   109,   196,     0,   112,     0,     0,
      13,    14,    16,    15,   194,     0,    11,   195,     0,   228,
     229,   237,     0,     0,    31,   104,   105,   106,     0,     0,
       0,     0,    23,   101,    24,     0,    25,     0,     0,    20,
       0,     0,   106,     0,     0,     0,   138,     0,     0,     0,
     144,    52,    52,     0,     0,     0,     0,   196,    33,    70,
      36,     0,    38,     0,    37,    34,    35,    52,    52,    52,
      52,    46,    52,   207,   208,   209,    52,    52,     0,     0,
     115,   108,     0,     0,   195,   191,   193,     0,   240,     0,
       0,    29,   106,    86,     0,    85,     0,     0,    84,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    28,    26,    12,     0,     0,   167,   168,
       0,     0,     0,   164,     0,     0,     0,     0,     0,    52,
      52,   144,     0,   143,     0,    42,    43,     0,     0,     0,
      73,    12,    71,    70,     0,     0,    65,     0,     0,    44,
      45,    48,    47,    49,    50,    51,   195,     0,     0,   113,
     114,   196,   111,   184,     0,   185,   196,     0,     0,     0,
       0,     0,     0,     0,    74,   148,     0,    81,    75,    76,
      78,    77,    79,    80,    83,    87,    82,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     103,   132,   128,   129,   131,   130,   127,   122,     0,   125,
      20,    18,    27,    26,    12,   166,     0,     0,   231,   233,
       0,    71,    70,     0,    41,    40,     0,     0,    52,    62,
       0,     0,     0,   107,    65,     0,    66,    67,    68,    69,
      70,     0,     0,   118,     0,   145,   144,     0,   144,    70,
       0,     0,   115,   192,     0,     0,   188,     0,   183,     0,
     216,   222,   221,   223,   214,    52,     0,   149,   147,    52,
     120,     0,    21,    20,    17,   179,     0,     0,     0,   171,
     165,     0,     0,    52,    65,     0,     0,     0,    39,    52,
       0,     0,   155,     0,     0,     0,     0,    70,    52,     0,
     116,     0,    70,     0,    65,     0,   183,   110,   196,     0,
     186,     0,   190,   182,   239,   238,   226,   219,   218,   220,
     226,     0,   152,   151,   123,    52,   126,    19,     0,   170,
       0,   172,     0,     0,    61,     0,    52,    52,    52,   202,
      63,    52,   106,     0,   160,   159,    52,    52,     0,    58,
      65,    56,    52,     0,   144,    65,   144,     0,     0,   181,
       0,     0,   189,   227,     0,   224,     0,    30,   150,   121,
     176,   169,   180,     0,     0,     0,    52,     0,   140,     0,
       0,   204,   146,     0,   157,   158,   153,    55,   154,    52,
      64,   119,    52,     0,     0,     0,   142,   230,     0,   187,
      12,     0,    12,   177,     0,   232,   234,    54,   212,    52,
     206,   205,     0,     0,     0,   162,   156,    59,   117,     0,
     141,     0,     0,   217,   225,   215,   178,   175,     0,   213,
     139,    52,    52,    52,    52,    52,    52,    52,     0,   174,
       0,     0,   202,   203,   200,   137,     0,     0,   135,     0,
     173,     0,    52,   201,    52,    52,     0,     0,     0,   136,
     134,     0,    52,   210,     0,     0,     0,   199,     0,   212,
     198,   211
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    32,     6,    15,    16,   167,    78,    38,
      40,    17,    36,   223,    63,    96,    97,    98,   195,   439,
     176,   339,   292,   196,   193,   326,   191,   183,   161,    99,
      19,    20,    46,   209,   100,   403,   349,    74,   375,   319,
     101,   258,   259,    21,   102,   103,   104,   298,   184,   299,
     105,    76,   226,   317,   373,   106,   289,   282,   342,   395,
     433,    41,   107,   363,   170,   108,   328,   329,   210,   364,
      47,   109,   110,   411,   361,   127,   306,    55,    26,   307,
     111,   431,   464,   462,   112,   113,   114,   479,   115,    27,
     370,   366,   218,   414,   415,   116,   117,   331,   332,   118,
      58,   219,   220,   119
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -366
static const yytype_int16 yypact[] =
{
      -2,   173,    38,    44,  -366,  -366,    -2,  -366,  -366,  -366,
    -366,  -366,    32,  -366,   199,    -5,  -366,    19,    69,  -366,
      51,   280,    44,    44,    44,    44,    45,  -366,    44,    88,
      61,  -366,  -366,    81,   111,   404,  -366,   380,   110,   133,
      19,   178,  -366,   615,  -366,   225,   118,  -366,    45,   232,
    -366,  -366,  -366,  -366,  -366,    40,  -366,    73,    51,  -366,
    -366,  -366,    51,   214,   202,  -366,  -366,   221,   391,   391,
     391,   237,   775,   244,  -366,   265,  -366,   290,   255,   264,
     186,    74,    30,   313,   297,   273,  -366,   281,   299,   302,
     391,   615,   615,   322,   305,   307,   304,   329,  -366,   127,
    -366,   343,  -366,   344,  -366,  -366,  -366,   615,   615,   615,
     615,  -366,   615,  -366,  -366,  -366,   615,   615,   365,    68,
     346,  -366,   404,    50,  -366,  -366,  -366,   116,  -366,   404,
     404,  -366,  -366,   342,   691,  -366,   381,   391,  -366,   391,
     391,   391,   391,   391,   391,   391,   391,   391,   391,   391,
     391,   391,   391,   391,   391,   391,   391,   391,   391,   391,
     391,   178,   292,  -366,    19,    44,   374,   341,  -366,  -366,
     354,    51,   186,  -366,   386,   390,   366,   393,   391,   615,
     615,   391,   394,   775,   361,  -366,  -366,   369,   381,   413,
    -366,    44,   133,   395,   120,   178,   372,   451,    27,  -366,
    -366,  -366,  -366,  -366,  -366,  -366,   411,    51,   186,  -366,
    -366,   412,  -366,  -366,    46,  -366,   416,    45,   304,   388,
     392,   396,   304,    51,  -366,   385,   405,   842,   389,   389,
     342,   342,   342,   824,   878,   860,   517,   498,   327,   327,
     535,   535,   498,   801,   801,   801,   801,   775,   775,   775,
     408,  -366,  -366,  -366,  -366,  -366,  -366,  -366,   148,  -366,
     264,  -366,  -366,    19,    44,  -366,    83,   402,  -366,  -366,
     397,  -366,   395,   720,  -366,  -366,   414,   417,   615,  -366,
     419,   401,   421,  -366,   372,   415,   775,  -366,  -366,  -366,
     177,   393,   418,  -366,   153,  -366,   391,   430,   391,   395,
     275,   424,   346,  -366,   404,   449,  -366,   422,   178,    55,
    -366,   404,   404,   404,  -366,   615,   391,  -366,  -366,   615,
    -366,   275,  -366,   264,  -366,  -366,   108,   423,   304,   420,
    -366,   435,   442,   615,   372,    51,    11,    51,  -366,   615,
     425,    34,  -366,   427,   428,   413,   429,   395,   615,   432,
    -366,   436,   395,   438,   372,   150,   178,  -366,  -366,    45,
    -366,   440,  -366,   408,  -366,  -366,   466,  -366,  -366,  -366,
     466,   304,   775,   385,  -366,   615,  -366,  -366,   304,  -366,
     441,   115,   275,   275,  -366,   443,   615,   615,   615,   457,
    -366,   615,   459,   482,  -366,   401,   615,   615,   461,  -366,
     372,  -366,   615,   448,   391,   372,   391,   453,   454,  -366,
     119,   456,  -366,  -366,   206,  -366,   226,  -366,  -366,  -366,
     458,  -366,  -366,   108,   460,   462,   615,   304,  -366,   304,
     238,   444,  -366,   178,   401,  -366,  -366,  -366,  -366,   615,
    -366,  -366,   615,   463,   464,   471,  -366,  -366,   445,  -366,
      44,   466,    44,   108,   304,  -366,  -366,  -366,   497,   615,
    -366,  -366,   450,   465,   304,   408,  -366,  -366,  -366,    18,
    -366,   124,   484,  -366,  -366,  -366,  -366,   468,   489,   504,
    -366,   615,   615,   615,   615,   615,   615,   615,   455,   108,
     391,    51,   457,  -366,  -366,  -366,   304,   304,  -366,   495,
    -366,   749,   615,  -366,   615,   615,   404,    51,   304,  -366,
    -366,   162,   615,  -366,   493,   208,   304,  -366,   494,   497,
    -366,  -366
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -366,  -366,   523,  -366,  -366,   -15,  -366,  -237,  -366,   -16,
     367,   467,  -366,  -366,  -366,   215,    -3,  -366,  -366,  -366,
    -366,  -366,  -270,  -166,  -160,   -17,   154,   203,  -366,    75,
    -366,  -366,   500,   240,  -366,  -366,  -366,   349,  -366,  -366,
     -31,  -192,  -293,  -366,  -366,  -366,  -366,  -366,  -118,   248,
    -366,   352,   359,   180,  -366,  -366,  -366,   216,  -365,  -366,
    -366,  -366,    48,   -40,  -143,   114,  -248,  -366,  -366,   223,
     469,   146,   235,  -366,  -366,  -366,   277,   -44,   -19,  -366,
    -366,    92,  -366,  -366,  -366,  -366,  -366,    66,  -366,  -366,
    -366,  -366,  -119,   210,   137,   242,  -366,  -366,  -366,    12,
     555,  -366,  -366,    71
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -238
static const yytype_int16 yytable[] =
{
      18,    81,    48,    43,   123,   294,    75,    50,    51,    52,
      53,   222,     1,    56,   344,    29,    48,   272,    45,    18,
      18,    18,    18,   322,    79,    18,    34,   284,   376,   267,
     435,     8,    45,    49,    29,    29,    29,    29,     7,   295,
      29,   129,    33,    42,    33,   130,   392,    49,     8,    37,
      42,    22,   125,     9,    10,    11,    12,    13,   303,   387,
      35,  -124,   213,   276,   385,   301,   484,   365,   -60,   466,
      22,    22,    22,    22,    30,   296,    22,   304,   378,   393,
     177,    39,   126,    42,   407,   128,   377,    54,   325,   424,
     425,   305,   126,    30,    30,    30,    30,   126,   207,    30,
      57,   174,   175,    48,   171,  -237,   334,   172,   355,    59,
     217,   217,    73,   325,    14,    42,    59,    23,   190,   211,
     422,   250,   173,    61,   346,    65,   216,   216,    66,    60,
     440,   347,    67,   354,    49,   444,    23,    23,    23,    23,
      42,    68,    23,    73,    73,    73,   214,    42,   260,    24,
     261,    69,   121,   448,   266,   290,   486,   194,    70,    77,
     -57,   126,    18,    75,   215,    73,  -163,   122,    24,    24,
      24,    24,   487,   309,    24,   454,   283,    29,   351,     4,
     353,   400,   320,    71,   285,   190,   405,   350,    18,     5,
     300,   168,   367,   368,   369,   297,   514,   321,   169,   321,
     221,   221,   321,    29,    54,   476,   315,   194,     9,    10,
     172,    80,    73,    22,    73,    73,    73,    73,    73,    73,
      73,    73,    73,    73,    73,    73,    73,    73,    73,    73,
      73,    73,    73,    73,    73,    73,    30,   120,    25,    22,
      72,   500,   518,   460,   124,    28,   461,   323,   131,   324,
     126,   122,  -124,    73,   450,   451,    73,    25,    25,    25,
      25,    18,    30,    25,    28,    28,    28,    28,   136,    73,
      28,   133,   134,   135,   452,   451,    29,  -102,   251,    23,
     252,   253,   254,   255,     8,   359,   443,   256,   445,     9,
      10,    11,   217,   217,   217,   251,   162,   252,   253,   254,
     255,   358,   163,   165,   256,    23,   185,   186,   216,   216,
     216,    24,    22,   166,    44,   410,    49,     8,   386,   388,
     389,   179,   199,   200,   201,   202,   257,   203,   178,   180,
     181,   204,   205,   182,   187,    30,   188,    24,   189,   190,
     227,   192,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   423,   138,   139,   140,   141,   142,
     143,    73,   310,    73,   197,   198,   314,   206,    23,   208,
     138,   273,   221,   221,   221,    65,   262,   225,    66,   264,
     265,    73,    67,   465,   274,   275,    65,   286,   268,    66,
      25,    68,   269,   132,   270,   271,   277,    28,     8,   278,
      24,    69,    68,     9,    10,    11,   394,   279,    70,   281,
     327,   291,    69,   128,   302,   194,    25,   138,   308,    70,
     141,   142,   143,    28,   316,   473,   311,   475,   330,   318,
     312,   172,   295,    71,   313,   333,   345,    18,   336,    18,
     341,   337,   485,   340,   251,   343,   252,   253,   254,   255,
     356,   303,    29,   256,    29,   382,   348,   515,   434,   381,
     362,   379,   383,   391,   502,   396,   397,   399,   413,    73,
     402,    73,   380,   430,   404,   293,   406,   511,   412,   421,
     512,   426,  -161,   338,   132,   438,   442,   469,    22,    25,
      22,   446,   447,   358,   449,   471,    28,   453,   455,   408,
     456,   463,   470,   472,   478,   488,   481,   489,    49,   372,
     490,    30,   491,    30,   499,   417,   506,   517,   520,    31,
     371,   482,   420,   263,   374,    64,   138,   139,   140,   141,
     142,   143,   357,   287,   164,   352,   288,   280,   384,   149,
     150,   151,   152,   418,   390,   138,   139,   140,   141,   142,
     143,   398,   145,   401,    23,    73,    23,   148,   149,   150,
     151,   152,   153,   138,   139,   140,   141,   142,   143,   409,
     416,   458,   360,   459,   503,   521,   149,   150,   474,    62,
     419,   212,     0,     0,     0,     0,    24,     0,    24,     0,
       0,   427,   428,   429,     0,     0,   432,     0,   477,     0,
       0,   436,   437,     0,     0,     0,     0,   441,   483,     8,
       0,     0,     0,     0,     9,    10,    11,    82,     0,     0,
      83,     0,     0,     0,    84,    85,     0,    86,    87,    88,
      89,   457,    90,    91,    92,     0,     0,     0,     0,     0,
     504,   505,     0,    93,   467,     0,     0,   468,     0,     0,
       0,     0,   513,     0,     0,     0,     0,     0,     0,     0,
     519,     0,     0,     0,   480,     0,     0,     0,    94,    95,
       0,     0,     0,     0,     0,    25,     0,    25,     0,     0,
       0,     0,    28,   501,    28,     0,   492,   493,   494,   495,
     496,   497,   498,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   508,     0,   509,
     510,     0,     0,     0,     0,   224,     0,   516,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,     0,
       0,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   335,     0,     0,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,     0,     0,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   507,     0,     0,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,     0,     0,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,     0,     0,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,     0,
       0,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   137,   138,   139,   140,   141,   142,   143,     0,   145,
     146,   147,     0,     0,   148,   149,   150,   151,   152,   153,
     138,   139,   140,   141,   142,   143,     0,   145,   146,   147,
       0,     0,   148,   149,   150,   151,   152,   153,   138,   139,
     140,   141,   142,   143,     0,   145,     0,   147,     0,     0,
     148,   149,   150,   151,   152,   153,   138,   139,   140,   141,
     142,   143,     0,     0,     0,     0,     0,     0,   148,   149,
     150,   151,   152,   153
};

static const yytype_int16 yycheck[] =
{
       3,    41,    21,    20,    48,   197,    37,    22,    23,    24,
      25,   130,    14,    28,   284,     3,    35,   177,    21,    22,
      23,    24,    25,   260,    40,    28,    14,   193,   321,   172,
     395,     4,    35,    21,    22,    23,    24,    25,     0,    12,
      28,    58,    12,    32,    12,    62,    12,    35,     4,    30,
      32,     3,    12,     9,    10,    11,    12,    13,    12,    48,
      65,    31,    12,   181,   334,   208,    48,    12,    38,   434,
      22,    23,    24,    25,     3,    48,    28,    31,   326,    45,
      83,    12,    42,    32,   354,    12,   323,    42,     5,   382,
     383,    45,    42,    22,    23,    24,    25,    42,    30,    28,
      12,    71,    72,   122,    30,    32,   272,    33,   300,    48,
     129,   130,    37,     5,    70,    32,    48,     3,    35,   122,
       5,   161,    48,    12,   290,     5,   129,   130,     8,    48,
     400,   291,    12,   299,   122,   405,    22,    23,    24,    25,
      32,    21,    28,    68,    69,    70,    30,    32,   164,     3,
     165,    31,    34,    34,   171,   195,    32,    30,    38,    49,
      33,    42,   165,   194,    48,    90,    33,    49,    22,    23,
      24,    25,    48,   217,    28,   423,   191,   165,   296,     6,
     298,   347,    34,    63,    64,    35,   352,    34,   191,    16,
     207,     5,   311,   312,   313,   198,    34,    49,    12,    49,
     129,   130,    49,   191,    42,   453,   223,    30,     9,    10,
      33,    33,   137,   165,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   165,    12,     3,   191,
      37,   489,    34,     5,    12,     3,     8,   263,    34,   264,
      42,    49,    31,   178,    48,    49,   181,    22,    23,    24,
      25,   264,   191,    28,    22,    23,    24,    25,    31,   194,
      28,    68,    69,    70,    48,    49,   264,    33,     3,   165,
       5,     6,     7,     8,     4,   304,   404,    12,   406,     9,
      10,    11,   311,   312,   313,     3,    31,     5,     6,     7,
       8,   304,    12,    48,    12,   191,    91,    92,   311,   312,
     313,   165,   264,    49,    34,   359,   304,     4,   335,   336,
     337,    48,   107,   108,   109,   110,    34,   112,    31,    48,
      31,   116,   117,    31,    12,   264,    31,   191,    31,    35,
     137,    12,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   381,    38,    39,    40,    41,    42,
      43,   296,   218,   298,    31,    31,   222,    12,   264,    33,
      38,   178,   311,   312,   313,     5,    12,     6,     8,    48,
      36,   316,    12,   433,   179,   180,     5,   194,    12,     8,
     165,    21,    12,    12,    38,    12,    12,   165,     4,    48,
     264,    31,    21,     9,    10,    11,   341,    48,    38,     6,
     266,    49,    31,    12,    12,    30,   191,    38,    12,    38,
      41,    42,    43,   191,    49,   450,    48,   452,    36,    34,
      48,    33,    12,    63,    48,    48,    31,   450,    34,   452,
      49,    34,   469,    34,     3,    34,     5,     6,     7,     8,
      36,    12,   450,    12,   452,    30,    48,   511,   393,    49,
      48,    48,    30,    48,   491,    48,    48,    48,    12,   404,
      48,   406,   328,    26,    48,    34,    48,   506,    48,    48,
     507,    48,    33,   278,    12,    34,    48,    34,   450,   264,
     452,    48,    48,   506,    48,    34,   264,    49,    48,   355,
      48,    67,    48,    68,    17,    31,    66,    49,   506,   316,
      31,   450,    18,   452,    69,   371,    31,    34,    34,     6,
     315,    66,   378,   166,   319,    35,    38,    39,    40,    41,
      42,    43,   302,   194,    77,   297,   194,   188,   333,    51,
      52,    53,    54,   373,   339,    38,    39,    40,    41,    42,
      43,   345,    45,   348,   450,   490,   452,    50,    51,    52,
      53,    54,    55,    38,    39,    40,    41,    42,    43,   356,
     370,   427,   305,   429,   492,   519,    51,    52,   451,    34,
     375,   122,    -1,    -1,    -1,    -1,   450,    -1,   452,    -1,
      -1,   386,   387,   388,    -1,    -1,   391,    -1,   454,    -1,
      -1,   396,   397,    -1,    -1,    -1,    -1,   402,   464,     4,
      -1,    -1,    -1,    -1,     9,    10,    11,    12,    -1,    -1,
      15,    -1,    -1,    -1,    19,    20,    -1,    22,    23,    24,
      25,   426,    27,    28,    29,    -1,    -1,    -1,    -1,    -1,
     496,   497,    -1,    38,   439,    -1,    -1,   442,    -1,    -1,
      -1,    -1,   508,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     516,    -1,    -1,    -1,   459,    -1,    -1,    -1,    63,    64,
      -1,    -1,    -1,    -1,    -1,   450,    -1,   452,    -1,    -1,
      -1,    -1,   450,   490,   452,    -1,   481,   482,   483,   484,
     485,   486,   487,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   502,    -1,   504,
     505,    -1,    -1,    -1,    -1,    34,    -1,   512,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    -1,
      -1,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    34,    -1,    -1,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    -1,    -1,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    34,    -1,    -1,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    -1,    -1,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    -1,    -1,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    -1,
      -1,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    37,    38,    39,    40,    41,    42,    43,    -1,    45,
      46,    47,    -1,    -1,    50,    51,    52,    53,    54,    55,
      38,    39,    40,    41,    42,    43,    -1,    45,    46,    47,
      -1,    -1,    50,    51,    52,    53,    54,    55,    38,    39,
      40,    41,    42,    43,    -1,    45,    -1,    47,    -1,    -1,
      50,    51,    52,    53,    54,    55,    38,    39,    40,    41,
      42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    50,    51,
      52,    53,    54,    55
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    14,    74,    75,     6,    16,    77,     0,     4,     9,
      10,    11,    12,    13,    70,    78,    79,    84,    89,   103,
     104,   116,   135,   138,   144,   145,   151,   162,   168,   172,
     176,    75,    76,    12,   172,    65,    85,    30,    82,    12,
      83,   134,    32,    98,    34,    89,   105,   143,   151,   172,
      78,    78,    78,    78,    42,   150,    78,    12,   173,    48,
      48,    12,   173,    87,   105,     5,     8,    12,    21,    31,
      38,    63,   100,   102,   110,   113,   124,    49,    81,    82,
      33,   136,    12,    15,    19,    20,    22,    23,    24,    25,
      27,    28,    29,    38,    63,    64,    88,    89,    90,   102,
     107,   113,   117,   118,   119,   123,   128,   135,   138,   144,
     145,   153,   157,   158,   159,   161,   168,   169,   172,   176,
      12,    34,    49,   150,    12,    12,    42,   148,    12,    98,
      98,    34,    12,   100,   100,   100,    31,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,   101,    31,    12,    84,    48,    49,    80,     5,    12,
     137,    30,    33,    48,    71,    72,    93,    89,    31,    48,
      48,    31,    31,   100,   121,    88,    88,    12,    31,    31,
      35,    99,    12,    97,    30,    91,    96,    31,    31,    88,
      88,    88,    88,    88,    88,    88,    12,    30,    33,   106,
     141,    89,   143,    12,    30,    48,    89,   151,   165,   174,
     175,   176,   165,    86,    34,     6,   125,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     136,     3,     5,     6,     7,     8,    12,    34,   114,   115,
      82,    78,    12,    83,    48,    36,    98,   137,    12,    12,
      38,    12,    97,   100,    88,    88,   121,    12,    48,    48,
     125,     6,   130,    78,    96,    64,   100,   110,   124,   129,
     136,    49,    95,    34,   114,    12,    48,    89,   120,   122,
      98,   137,    12,    12,    31,    45,   149,   152,    12,   150,
      99,    48,    48,    48,    99,    98,    49,   126,    34,   112,
      34,    49,    80,    82,    78,     5,    98,    99,   139,   140,
      36,   170,   171,    48,    96,    34,    34,    34,    88,    94,
      34,    49,   131,    34,    95,    31,    96,    97,    48,   109,
      34,   121,   122,   121,    96,   114,    36,   106,    89,   151,
     149,   147,    48,   136,   142,    12,   164,   165,   165,   165,
     163,    88,   100,   127,    88,   111,   115,    80,   139,    48,
      99,    49,    30,    30,    88,    95,    98,    48,    98,    98,
      88,    48,    12,    45,   102,   132,    48,    48,   130,    48,
      96,    88,    48,   108,    48,    96,    48,    95,    99,   142,
     150,   146,    48,    12,   166,   167,   166,    99,   126,    88,
      99,    48,     5,    98,   115,   115,    48,    88,    88,    88,
      26,   154,    88,   133,   102,   131,    88,    88,    34,    92,
      95,    88,    48,   121,    95,   121,    48,    48,    34,    48,
      48,    49,    48,    49,   139,    48,    48,    88,    99,    99,
       5,     8,   156,    67,   155,   136,   131,    88,    88,    34,
      48,    34,    68,    78,   167,    78,   139,    99,    17,   160,
      88,    66,    66,    99,    48,    98,    32,    48,    31,    49,
      31,    18,    88,    88,    88,    88,    88,    88,    88,    69,
     139,   100,    98,   154,    99,    99,    31,    34,    88,    88,
      88,   151,    98,    99,    34,   150,    88,    34,    34,    99,
      34,   160
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
#line 440 "semanticAnalysis.y"
    {printf("\n\nSyntax is Correct\n");return;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 452 "semanticAnalysis.y"
    {
    if(strcmp(forFunc->dataType,"void")==0){
        char const errorMessage[100]="Void Function Does not return anything";
        int a=yyerror(errorMessage);
        return -1;
    }
}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 460 "semanticAnalysis.y"
    {
    struct SymbolTableEntry * search=lookup((yyvsp[(1) - (1)].value),1,true);
    if(search!=NULL){
        char message[30]="Variable Already Declared";
        int res=yyerror(message);
        return -1;
    }
    else{
        struct SymbolTableEntry*new_entry=insertIdentifier((yyvsp[(1) - (1)].value),CLASS[0],typeBuffer,0,yylinenumber,1);
    }
}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 471 "semanticAnalysis.y"
    {
            struct SymbolTableEntry * search=lookup((yyvsp[(1) - (1)].value),scope,false);
            if(search==NULL){
                char message[30]="Variable Not Declared";
                int res=yyerror(message);
                return -1;
            }
            else{
                update(search,yylinenumber);
            }
         }
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 483 "semanticAnalysis.y"
    {noOfParameters=0;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 492 "semanticAnalysis.y"
    {
            strcpy(typeBuffer,(yyvsp[(1) - (1)].type));
            (yyval.type)=malloc(strlen((yyvsp[(1) - (1)].type))+1);
            strcpy((yyval.type),(yyvsp[(1) - (1)].type));
        }
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 500 "semanticAnalysis.y"
    {dimit = 0;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 500 "semanticAnalysis.y"
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
                if(dimbuffer[i] != 10000 && entry->dimSize[i] <= dimbuffer[i] || dimbuffer[i] < 0)
                {
                    char const errorMessage[100]="Invalid Access";
                    int a=yyerror(errorMessage);
                    return -1;
                }
            }
            dimit = 0;
        }
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 519 "semanticAnalysis.y"
    {
            struct SymbolTableEntry * search=lookup((yyvsp[(1) - (1)].value),scope,false);
            if(search==NULL){
                char message[30]="Variable Not Declared";
                int res=yyerror(message);
                return -1;
            }
            else{
                update(search,yylinenumber);
            }
        }
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 530 "semanticAnalysis.y"
    {
            struct SymbolTableEntry * search=lookup((yyvsp[(2) - (3)].value),scope,false);
            if(search==NULL){
                char message[30]="Variable Not Declared";
                int res=yyerror(message);
                return -1;
            }
            else{
                update(search,yylinenumber);
            }
        }
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 543 "semanticAnalysis.y"
    {
    if(strcmp(forFunc->dataType,"void")==0){
        char const errorMessage[100]="Void Function Does not return anything";
        int a=yyerror(errorMessage);
        return -1;
    }
}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 551 "semanticAnalysis.y"
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

  case 72:

/* Line 1455 of yacc.c  */
#line 563 "semanticAnalysis.y"
    {scope++;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 564 "semanticAnalysis.y"
    {deleteDMT(scope);scope--;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 593 "semanticAnalysis.y"
    {dimit = 0;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 594 "semanticAnalysis.y"
    {dimit = 0;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 594 "semanticAnalysis.y"
    {
    struct SymbolTableEntry * found=lookup(IDBuffer,scope,false);
    if(dimit!=found->dimension){
        char const errorMessage[100]="Dimension does Not match!!";
            int a=yyerror(errorMessage);
            return -1;
    }
    update(found,yylinenumber);
    dimit=0;
}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 606 "semanticAnalysis.y"
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

  case 108:

/* Line 1455 of yacc.c  */
#line 620 "semanticAnalysis.y"
    {
    struct SymbolTableEntry * entry = lookup(funNameBuffer,1,true);
    if(entry!=NULL){
        char message[40]="Function name is Already Declared";
        int res=yyerror(message);
        return -1;
    }
    struct SymbolTableEntry* new_entry = insertFunction(funNameBuffer,CLASS[1],funTypeBuffer,0,yylinenumber,scope,noOfParameters,PL,PTL);
    noOfParameters=0;
    pointerLen=1;
}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 631 "semanticAnalysis.y"
    {
                        struct SymbolTableEntry * entry = lookup(funNameBuffer,1,true);
                        if(entry!=NULL){
                            char message[40]="Function name is Already Declared";
                            int res=yyerror(message);
                            return -1;
                        }
                        struct SymbolTableEntry* new_entry = insertFunction(funNameBuffer,CLASS[1],funTypeBuffer,0,yylinenumber,scope,noOfParameters,PL,PTL);
                        noOfParameters=0;
                        pointerLen=1;
                      }
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 642 "semanticAnalysis.y"
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

  case 111:

/* Line 1455 of yacc.c  */
#line 675 "semanticAnalysis.y"
    {
                    struct SymbolTableEntry*new_entry = insertIdentifier(ptrBuf,CLASS[3],(yyvsp[(3) - (3)].type),pointerLen,yylinenumber,scope+1);
                    PD[noOfParameters]=pointerLen;
                    strcpy(PL[noOfParameters],(yyvsp[(3) - (3)].type));
                    PTL[noOfParameters]='p';
                    noOfParameters++;
                }
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 682 "semanticAnalysis.y"
    {
                    struct SymbolTableEntry*new_entry = insertIdentifier(ptrBuf,CLASS[3],(yyvsp[(1) - (1)].type),pointerLen,yylinenumber,scope+1);
                    PD[noOfParameters]=pointerLen;
                    strcpy(PL[noOfParameters],(yyvsp[(1) - (1)].type));
                    PTL[noOfParameters]='p';
                    noOfParameters++;
                    pointerLen=1;
                }
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 690 "semanticAnalysis.y"
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

  case 114:

/* Line 1455 of yacc.c  */
#line 710 "semanticAnalysis.y"
    {
    (yyval.type)=malloc(strlen("array")+1);strcpy((yyval.type),"array");

    }
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 713 "semanticAnalysis.y"
    {(yyval.type)=malloc(strlen("variable")+1);strcpy((yyval.type),"variable");}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 716 "semanticAnalysis.y"
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
        if((PTL[i]=='a' && forFunc->paraTypes[i]=='p') || (PTL[i]=='p' && forFunc->paraTypes[i]=='a'))continue;
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

  case 118:

/* Line 1455 of yacc.c  */
#line 751 "semanticAnalysis.y"
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
                        if((PTL[i]=='a' && forFunc->paraTypes[i]=='p') || (PTL[i]=='p' && forFunc->paraTypes[i]=='a'))continue;
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

  case 120:

/* Line 1455 of yacc.c  */
#line 799 "semanticAnalysis.y"
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
        if((PTL[i]=='a' && forFunc->paraTypes[i]=='p') || (PTL[i]=='p' && forFunc->paraTypes[i]=='a'))continue;
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

  case 122:

/* Line 1455 of yacc.c  */
#line 834 "semanticAnalysis.y"
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
                        if((PTL[i]=='a' && forFunc->paraTypes[i]=='p') || (PTL[i]=='p' && forFunc->paraTypes[i]=='a'))continue;
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

  case 124:

/* Line 1455 of yacc.c  */
#line 880 "semanticAnalysis.y"
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

  case 125:

/* Line 1455 of yacc.c  */
#line 897 "semanticAnalysis.y"
    {
    strcpy(PL[noOfParameters],(yyvsp[(1) - (1)].type));
    PTL[noOfParameters]=pt;
    noOfParameters++;
}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 902 "semanticAnalysis.y"
    {
            strcpy(PL[noOfParameters],(yyvsp[(3) - (3)].type));
            PTL[noOfParameters]=pt;
            noOfParameters++;
        }
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 907 "semanticAnalysis.y"
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
    else if(strcmp(entry->type,CLASS[3])==0){
        pt='p';
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

  case 128:

/* Line 1455 of yacc.c  */
#line 935 "semanticAnalysis.y"
    {(yyval.type)=malloc(strlen((yyvsp[(1) - (1)].type))+1);strcpy((yyval.type),(yyvsp[(1) - (1)].type));pt='v';parD[parDi++]=0;}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 936 "semanticAnalysis.y"
    {(yyval.type)=malloc(strlen((yyvsp[(1) - (1)].type))+1);strcpy((yyval.type),(yyvsp[(1) - (1)].type));pt='v';parD[parDi++]=0;}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 937 "semanticAnalysis.y"
    {(yyval.type)=malloc(strlen((yyvsp[(1) - (1)].type))+1);strcpy((yyval.type),(yyvsp[(1) - (1)].type));pt='v';parD[parDi++]=0;}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 938 "semanticAnalysis.y"
    {(yyval.type)=malloc(strlen((yyvsp[(1) - (1)].type))+1);strcpy((yyval.type),(yyvsp[(1) - (1)].type));pt='v';parD[parDi++]=0;}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 941 "semanticAnalysis.y"
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

  case 138:

/* Line 1455 of yacc.c  */
#line 979 "semanticAnalysis.y"
    {scope++;}
    break;

  case 145:

/* Line 1455 of yacc.c  */
#line 989 "semanticAnalysis.y"
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

  case 161:

/* Line 1455 of yacc.c  */
#line 1016 "semanticAnalysis.y"
    {
    dimit = 0;
    struct SymbolTableEntry * found=lookup((yyvsp[(1) - (1)].value),scope,false);
        strcpy(IDBuffer,(yyvsp[(1) - (1)].value));
        if(found==NULL){
            char const errorMessage[100]="Variable Not Declared!!";
            int a=yyerror(errorMessage);
            return -1;
        }
    }
    break;

  case 162:

/* Line 1455 of yacc.c  */
#line 1025 "semanticAnalysis.y"
    {
    struct SymbolTableEntry * found=lookup(IDBuffer,scope,false);
    if(dimit!=found->dimension){
        char const errorMessage[100]="Dimension does Not match!!";
            int a=yyerror(errorMessage);
            return -1;
    }
    update(found,yylinenumber);
    dimit=0;
}
    break;

  case 163:

/* Line 1455 of yacc.c  */
#line 1036 "semanticAnalysis.y"
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

  case 164:

/* Line 1455 of yacc.c  */
#line 1050 "semanticAnalysis.y"
    {
        for(int i=0;i<dimit;i++){
            if(dimbuffer[i]<=0){
                char message[25]="Access Denied";
                int res=yyerror(message);
                return -1;
            }
        }
    struct SymbolTableEntry* temp = insertArray(IDBuffer,CLASS[2],typeBuffer,dimit,yylinenumber,scope,dimbuffer);dimit = 0;}
    break;

  case 167:

/* Line 1455 of yacc.c  */
#line 1061 "semanticAnalysis.y"
    {dimbuffer[dimit++] = intval;}
    break;

  case 168:

/* Line 1455 of yacc.c  */
#line 1061 "semanticAnalysis.y"
    {dimbuffer[dimit++] = 10000;}
    break;

  case 169:

/* Line 1455 of yacc.c  */
#line 1062 "semanticAnalysis.y"
    {
        for(int i=0;i<dimit;i++){
            if(dimbuffer[i]<=0){
                char message[25]="Access Denied";
                int res=yyerror(message);
                return -1;
            }
        }
    struct SymbolTableEntry* temp = insertArray(IDBuffer,CLASS[2],typeBuffer,dimit,yylinenumber,scope,dimbuffer);dimit = 0;}
    break;

  case 170:

/* Line 1455 of yacc.c  */
#line 1071 "semanticAnalysis.y"
    {
        for(int i=0;i<dimit;i++){
            if(dimbuffer[i]<=0){
                char message[25]="Access Denied";
                int res=yyerror(message);
                return -1;
            }
        }
    struct SymbolTableEntry* temp = insertArray(IDBuffer,CLASS[2],typeBuffer,dimit,yylinenumber,scope,dimbuffer);dimit = 0;}
    break;

  case 184:

/* Line 1455 of yacc.c  */
#line 1093 "semanticAnalysis.y"
    {
    struct SymbolTableEntry * found=lookup((yyvsp[(3) - (3)].value),scope+1,true);
    if(found != NULL)
    {
        char const errorMessage[100]="Variable Already Declared!!";
        int a=yyerror(errorMessage);
        return -1;
    }
    else{
        strcpy(ptrBuf,(yyvsp[(3) - (3)].value));
        (yyval.type)=malloc(strlen((yyvsp[(1) - (3)].type))+1);
        strcpy((yyval.type),(yyvsp[(1) - (3)].type));
    }
}
    break;

  case 186:

/* Line 1455 of yacc.c  */
#line 1109 "semanticAnalysis.y"
    {if(strcmp((yyvsp[(3) - (6)].type),(yyvsp[(6) - (6)].type))!=0){
    char message[30]="Variable Types dont Match";
        int res=yyerror(message);
        return -1;}}
    break;

  case 188:

/* Line 1455 of yacc.c  */
#line 1112 "semanticAnalysis.y"
    {if(strcmp((yyvsp[(3) - (5)].type),(yyvsp[(5) - (5)].type))!=0){
    char message[30]="Variable Types dont Match";
        int res=yyerror(message);
        return -1;
}}
    break;

  case 191:

/* Line 1455 of yacc.c  */
#line 1118 "semanticAnalysis.y"
    {
    
    struct SymbolTableEntry * search=lookup((yyvsp[(1) - (1)].value),scope,true);
    if(search!=NULL){
        char message[30]="Variable Already Declared";
        int res=yyerror(message);
        return -1;
    }
    else{
        (yyval.type)=typeBuffer;
        struct SymbolTableEntry*new_entry=insertIdentifier((yyvsp[(1) - (1)].value),CLASS[3],typeBuffer,pointerLen,yylinenumber,scope);
        pointerLen = 1;
    }
}
    break;

  case 192:

/* Line 1455 of yacc.c  */
#line 1132 "semanticAnalysis.y"
    {
        struct SymbolTableEntry * found=lookup((yyvsp[(1) - (1)].value),scope,false);
        if(found==NULL){
            char const errorMessage[100]="Variable Not Declared!!";
            int a=yyerror(errorMessage);
            return -1;
        }
        else{
            (yyval.type) = found->dataType;
            update(found,yylinenumber);
        }
     }
    break;

  case 193:

/* Line 1455 of yacc.c  */
#line 1144 "semanticAnalysis.y"
    {  
     pointerLen++;
}
    break;

  case 214:

/* Line 1455 of yacc.c  */
#line 1162 "semanticAnalysis.y"
    {
        struct SymbolTableEntry*new_entry=insertIdentifier(userTypeNameBuffer,CLASS[4],userTypeBuffer,userTypeDim,yylinenumber,scope);
        userTypeDim = 0;
    }
    break;

  case 216:

/* Line 1455 of yacc.c  */
#line 1167 "semanticAnalysis.y"
    {
        struct SymbolTableEntry*new_entry=insertIdentifier(userTypeNameBuffer,CLASS[4],userTypeBuffer,userTypeDim,yylinenumber,scope);
        userTypeDim = 0;
                }
    break;

  case 227:

/* Line 1455 of yacc.c  */
#line 1182 "semanticAnalysis.y"
    {
    struct SymbolTableEntry * search=lookup((yyvsp[(1) - (1)].value),1,true);
    if(search!=NULL){
        char message[30]="Variable Already Declared";
        int res=yyerror(message);
        return -1;
    }
    else{
        struct SymbolTableEntry*new_entry=insertIdentifier((yyvsp[(1) - (1)].value),userTypeBuffer,userTypeNameBuffer,0,yylinenumber,1);
    }
}
    break;

  case 231:

/* Line 1455 of yacc.c  */
#line 1197 "semanticAnalysis.y"
    {
                            struct SymbolTableEntry * search=lookup((yyvsp[(1) - (3)].value),scope,false);
                            
                            if(search==NULL){
                                char message[30]="Variable Not Declared";
                                int res=yyerror(message);
                                return -1;
                            }else {
                                struct SymbolTableEntry * search1=lookup((yyvsp[(3) - (3)].value),1,true);
                                if(search1 == NULL){
                                    char message[50]="Variable Not Part of the User definied Data Type";
                                    int res=yyerror(message);
                                return -1;
                                }
                                if(strcmp(search->dataType,search1->dataType)!=0){
                                        char message[30]="Varible Type Mismatch!!";
                                        int res=yyerror(message);
                                        return -1;
                                }
                                update(search,yylinenumber);
                            }
                        }
    break;

  case 233:

/* Line 1455 of yacc.c  */
#line 1219 "semanticAnalysis.y"
    {
                            struct SymbolTableEntry * search=lookup((yyvsp[(1) - (3)].value),scope,false);
                            
                            if(search==NULL){
                                char message[30]="Variable Not Declared";
                                int res=yyerror(message);
                                return -1;
                            }else {
                                struct SymbolTableEntry * search1=lookup((yyvsp[(3) - (3)].value),1,true);
                                if(search1 == NULL){
                                    char message[50]="Variable Not Part of the User definied Data Type";
                                    int res=yyerror(message);
                                return -1;
                                }
                                if(strcmp(search->dataType,search1->dataType)!=0){
                                        char message[30]="Varible Type Mismatch!!";
                                        int res=yyerror(message);
                                        return -1;
                                }
                            }
                            update(search,yylinenumber);
                        }
    break;

  case 235:

/* Line 1455 of yacc.c  */
#line 1242 "semanticAnalysis.y"
    {
            strcpy(userTypeBuffer,(yyvsp[(1) - (1)].type));
            (yyval.type)=malloc(strlen((yyvsp[(1) - (1)].type))+1);
            strcpy((yyval.type),(yyvsp[(1) - (1)].type));
        }
    break;

  case 236:

/* Line 1455 of yacc.c  */
#line 1247 "semanticAnalysis.y"
    {
            strcpy(userTypeBuffer,(yyvsp[(1) - (1)].type));
            (yyval.type)=malloc(strlen((yyvsp[(1) - (1)].type))+1);
            strcpy((yyval.type),(yyvsp[(1) - (1)].type));
        }
    break;

  case 237:

/* Line 1455 of yacc.c  */
#line 1253 "semanticAnalysis.y"
    {
    struct SymbolTableEntry * search=lookup((yyvsp[(1) - (1)].value),1,true);
    if(search!=NULL){
        char message[30]="Variable Already Declared";
        int res=yyerror(message);
        return -1;
    }
    else{
        strcpy(userTypeNameBuffer, (yyvsp[(1) - (1)].value));
    }
}
    break;

  case 238:

/* Line 1455 of yacc.c  */
#line 1264 "semanticAnalysis.y"
    {
    struct SymbolTableEntry * found=lookup((yyvsp[(3) - (3)].value),1,true);
    if(found != NULL)
    {
        char const errorMessage[100]="Variable Already Declared!!";
        int a=yyerror(errorMessage);
        return -1;
    }
    else{
        struct SymbolTableEntry*new_entry=insertIdentifier((yyvsp[(3) - (3)].value),CLASS[3],userTypeNameBuffer,pointerLen,yylinenumber,1);
        pointerLen = 1;
    }
    userTypeDim++;
}
    break;

  case 239:

/* Line 1455 of yacc.c  */
#line 1280 "semanticAnalysis.y"
    {
    struct SymbolTableEntry * search=lookup((yyvsp[(2) - (3)].value),1,true);
    if(search!=NULL){
        char message[30]="Variable Already Declared";
        int res=yyerror(message);
        return -1;
    }
    else{
        if(dimit==0){
            struct SymbolTableEntry*new_entry=insertIdentifier((yyvsp[(2) - (3)].value),CLASS[0],userTypeNameBuffer,dimit,yylinenumber,1);
        }else{
            struct SymbolTableEntry*new_entry=insertIdentifier((yyvsp[(2) - (3)].value),CLASS[2],userTypeNameBuffer,dimit,yylinenumber,1);
        }
        
        userTypeDim++;
        dimit = 0;
    }
}
    break;

  case 240:

/* Line 1455 of yacc.c  */
#line 1300 "semanticAnalysis.y"
    {
                    struct SymbolTableEntry * search=lookup((yyvsp[(2) - (3)].value),1,true);
                    if(search==NULL){
                        char message[30]="Variable Not Declared";
                        int res=yyerror(message);
                        return -1;
                    }else if(strcmp(search->dataType,(yyvsp[(1) - (3)].type))!=0){
                            char message[30]="Varible Type Mismatch!!";
                            int res=yyerror(message);
                            return -1;
                    }
                    else{struct SymbolTableEntry * search1=lookup((yyvsp[(3) - (3)].value),1,true);
                        if(search1!=NULL){
                        char message[30]="Variable Already Declared";
                        int res=yyerror(message);
                        return -1;
                        }else{
                            struct SymbolTableEntry*new_entry=insertIdentifier((yyvsp[(3) - (3)].value),search->dataType,(yyvsp[(2) - (3)].value),0,yylinenumber,1);
                        }
                    }
                    userTypeDim++;       
                }
    break;



/* Line 1455 of yacc.c  */
#line 3580 "y.tab.c"
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
#line 1323 "semanticAnalysis.y"


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
    printf("%-3s %-15s %-15s %-20s %-10s %-10s %-15s %-15s %-20s\n","No.","ID", "Type", "Data Type","Dim","Scope","No of Params","Line of Decl","Line of Ref");
    printf("------------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < stIterator; i++) {
        printf("%d ",i);
        struct SymbolTableEntry * entry = Table.symTable[i];
        printf("%-15s %-15s %-20s %-10d %-10d %-15d %-15d [ ", entry->name, entry->type, entry->dataType,entry->dimension,entry->scope,entry->noOfParams,entry->lineOfDeclaration);
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
