
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

/* Line 214 of yacc.c  */
#line 413 "semanticAnalysis.y"

    char * value;
    char * type;



/* Line 214 of yacc.c  */
#line 671 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 683 "y.tab.c"

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
#define YYLAST   940

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  72
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  104
/* YYNRULES -- Number of rules.  */
#define YYNRULES  239
/* YYNRULES -- Number of states.  */
#define YYNSTATES  515

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   326

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
      65,    66,    67,    68,    69,    70,    71
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
     139,   142,   145,   146,   148,   155,   161,   162,   163,   171,
     172,   178,   179,   185,   190,   191,   194,   197,   200,   203,
     204,   206,   208,   210,   214,   218,   222,   226,   230,   234,
     238,   242,   246,   250,   253,   256,   259,   263,   267,   271,
     275,   279,   283,   287,   291,   295,   299,   303,   307,   311,
     315,   317,   318,   322,   324,   326,   328,   334,   338,   341,
     347,   351,   353,   357,   359,   360,   361,   369,   370,   377,
     378,   385,   386,   392,   394,   396,   400,   402,   404,   406,
     408,   410,   412,   414,   426,   436,   448,   458,   460,   469,
     476,   482,   487,   489,   490,   492,   499,   504,   506,   509,
     513,   516,   518,   525,   530,   533,   538,   542,   546,   549,
     551,   552,   556,   558,   563,   568,   572,   574,   576,   585,
     593,   595,   598,   606,   613,   619,   623,   628,   634,   636,
     640,   645,   647,   648,   652,   657,   658,   667,   668,   676,
     683,   685,   687,   690,   692,   695,   697,   699,   712,   724,
     734,   740,   741,   745,   746,   748,   750,   752,   754,   756,
     769,   778,   779,   788,   789,   800,   801,   811,   815,   819,
     823,   826,   829,   832,   834,   838,   839,   841,   844,   848,
     855,   856,   864,   865,   873,   875,   877,   879,   883,   887
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      73,     0,    -1,    74,    77,    84,    -1,    14,    76,    75,
      -1,    74,    -1,    -1,     6,    -1,    15,    -1,   102,    -1,
      78,    -1,   161,    -1,   167,    77,    -1,    -1,   134,    77,
      -1,   137,    77,    -1,   144,    77,    -1,   143,    77,    -1,
      88,    82,    81,    79,    47,    77,    -1,    83,    81,    80,
      47,    77,    -1,    48,    82,    81,    79,    -1,    -1,    48,
      83,    81,    79,    -1,    -1,    29,    99,    -1,    29,   109,
      -1,    29,   123,    -1,    -1,    12,    -1,    12,    -1,    -1,
      64,    86,    33,    85,    97,    87,    98,    -1,   104,    -1,
      -1,    89,    -1,   122,    -1,   127,    -1,   106,    -1,   118,
      -1,   116,    -1,    26,   120,    47,    87,    -1,    22,    47,
      87,    -1,    19,    47,    87,    -1,    27,    87,    -1,    28,
      87,    -1,   134,    87,    -1,   137,    87,    -1,   152,    -1,
     144,    87,    -1,   143,    87,    -1,   156,    87,    -1,   167,
      87,    -1,   168,    87,    -1,    -1,     4,    -1,    88,    96,
      95,    94,    47,    87,    -1,   101,    95,    94,    47,    87,
      -1,    -1,    -1,   101,    90,   135,    95,    47,    91,    87,
      -1,    -1,    12,    92,    37,    47,    87,    -1,    -1,    37,
      12,    47,    93,    87,    -1,    48,    96,    95,    94,    -1,
      -1,    29,    99,    -1,    29,   109,    -1,    29,   123,    -1,
      29,   128,    -1,    -1,    12,    -1,    31,    -1,    34,    -1,
      30,    99,    33,    -1,    99,    38,    99,    -1,    99,    39,
      99,    -1,    99,    41,    99,    -1,    99,    40,    99,    -1,
      99,    42,    99,    -1,    99,    43,    99,    -1,    99,    36,
      99,    -1,    99,    46,    99,    -1,    99,    44,    99,    -1,
      99,    37,    -1,    37,    99,    -1,    20,    99,    -1,    99,
      45,    99,    -1,    99,    49,    99,    -1,    99,    50,    99,
      -1,    99,    51,    99,    -1,    99,    52,    99,    -1,    99,
      53,    99,    -1,    99,    54,    99,    -1,    99,    55,    99,
      -1,    99,    56,    99,    -1,    99,    57,    99,    -1,    99,
      58,    99,    -1,    99,    59,    99,    -1,    99,    60,    99,
      -1,    99,    61,    99,    -1,   101,    -1,    -1,   101,   100,
     135,    -1,     5,    -1,     8,    -1,    12,    -1,   103,    97,
      87,    98,    77,    -1,   115,   104,    33,    -1,   115,    33,
      -1,   104,    48,    88,    12,   105,    -1,   104,    48,   142,
      -1,   142,    -1,    88,    12,   105,    -1,   140,    -1,    -1,
      -1,   112,    30,   113,    33,   107,    47,    87,    -1,    -1,
     112,    30,    33,   108,    47,    87,    -1,    -1,   112,    30,
     113,    33,   110,    87,    -1,    -1,   112,    30,    33,   111,
      87,    -1,    12,    -1,   114,    -1,   113,    48,   114,    -1,
      12,    -1,     5,    -1,     6,    -1,     8,    -1,     7,    -1,
       3,    -1,    13,    -1,   117,    30,   119,   120,    47,   120,
      33,    31,    87,    98,    87,    -1,   117,    30,   119,   120,
      47,   120,    33,    47,    87,    -1,   117,    30,    47,   120,
      47,   120,    33,    97,    87,    98,    87,    -1,   117,    30,
      47,   120,    47,   120,    33,    47,    87,    -1,    21,    -1,
      23,    30,   120,    33,    97,    87,    98,    87,    -1,    23,
      30,   120,    33,    47,    87,    -1,    88,   121,    95,    94,
      47,    -1,   121,    95,    94,    47,    -1,    99,    -1,    -1,
      12,    -1,    62,    30,   124,    33,    47,    87,    -1,    62,
      30,   124,    33,    -1,     6,    -1,     6,   125,    -1,    48,
     126,   125,    -1,    48,   126,    -1,    99,    -1,    63,    30,
     129,    33,    47,    87,    -1,    63,    30,   129,    33,    -1,
       6,   130,    -1,    48,    44,   101,   130,    -1,    48,    44,
     101,    -1,    48,   131,   130,    -1,    48,   131,    -1,   101,
      -1,    -1,    12,   132,   135,    -1,    12,    -1,    88,   133,
     135,    47,    -1,   135,    32,   136,    35,    -1,    32,   136,
      35,    -1,     5,    -1,    12,    -1,    88,   133,   135,    29,
      97,   138,    98,    47,    -1,    88,   133,   135,    29,    97,
      98,    47,    -1,   139,    -1,   139,    48,    -1,   139,    48,
      97,   138,    98,    48,   138,    -1,   139,    48,    97,   138,
      98,    48,    -1,   139,    48,    97,   138,    98,    -1,    97,
     138,    98,    -1,    97,   138,    98,    48,    -1,    97,   138,
      98,    48,   138,    -1,     5,    -1,   139,    48,     5,    -1,
      32,   136,    35,   141,    -1,   135,    -1,    -1,   150,   149,
      12,    -1,   150,   149,   147,    47,    -1,    -1,   150,   149,
     147,    29,    44,   148,   145,    47,    -1,    -1,   150,   149,
     147,    29,   148,   146,    47,    -1,   150,   149,   147,    29,
     151,    47,    -1,    12,    -1,    12,    -1,   149,    41,    -1,
      41,    -1,   171,    12,    -1,    88,    -1,    11,    -1,    30,
     150,   149,    33,    67,    30,    68,    30,   150,   149,    33,
      33,    -1,    30,   150,   149,    33,    67,    30,    68,    30,
     150,    33,    33,    -1,    24,    30,    12,    33,    97,   153,
     154,    98,    87,    -1,    25,   155,    65,    87,   153,    -1,
      -1,    66,    65,    87,    -1,    -1,     8,    -1,     5,    -1,
     157,    -1,   158,    -1,   160,    -1,    18,    30,    99,    33,
      97,    87,    98,   159,    17,    97,    87,    98,    -1,    16,
      30,    99,    33,    97,    87,    98,   159,    -1,    -1,    18,
      30,    99,    33,    97,    87,    98,   159,    -1,    -1,    69,
     171,   172,    97,   164,    98,   162,   165,    47,    77,    -1,
      -1,   171,   172,    97,   164,    98,   163,   165,    47,    77,
      -1,   174,    47,   164,    -1,   173,    47,   164,    -1,   175,
      47,   164,    -1,   174,    47,    -1,   173,    47,    -1,   175,
      47,    -1,   166,    -1,   165,    48,   166,    -1,    -1,    12,
      -1,   175,    47,    -1,    12,    12,    47,    -1,   175,    29,
      97,   113,    98,    47,    -1,    -1,    12,    70,    12,   169,
      29,   114,    47,    -1,    -1,    12,    71,    12,   170,    29,
     114,    47,    -1,     9,    -1,    10,    -1,    12,    -1,   150,
     149,    12,    -1,    88,    12,   141,    -1,   171,    12,    12,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   440,   440,   441,   442,   442,   443,   443,   445,   445,
     445,   445,   445,   446,   446,   446,   446,   448,   449,   450,
     450,   451,   451,   452,   452,   458,   458,   460,   471,   483,
     483,   484,   484,   486,   486,   486,   486,   486,   486,   487,
     487,   487,   488,   488,   488,   488,   489,   489,   489,   489,
     490,   490,   490,   492,   497,   498,   499,   499,   499,   518,
     518,   529,   529,   541,   541,   542,   542,   548,   548,   548,
     550,   562,   563,   565,   566,   567,   568,   569,   570,   571,
     572,   573,   574,   575,   576,   577,   578,   579,   580,   581,
     582,   583,   584,   585,   586,   587,   588,   589,   590,   591,
     592,   593,   593,   603,   603,   605,   618,   619,   630,   641,
     674,   681,   689,   709,   712,   715,   715,   750,   750,   798,
     798,   833,   833,   879,   896,   901,   906,   934,   935,   936,
     937,   938,   940,   973,   974,   975,   976,   978,   980,   981,
     983,   984,   986,   986,   988,  1000,  1001,  1002,  1003,  1004,
    1005,  1006,  1008,  1009,  1010,  1011,  1012,  1013,  1014,  1015,
    1015,  1015,  1035,  1048,  1058,  1058,  1060,  1060,  1061,  1070,
    1079,  1080,  1081,  1082,  1083,  1084,  1085,  1086,  1087,  1087,
    1089,  1090,  1090,  1092,  1107,  1108,  1108,  1111,  1111,  1115,
    1117,  1131,  1143,  1145,  1146,  1146,  1146,  1147,  1148,  1150,
    1151,  1151,  1152,  1152,  1153,  1153,  1155,  1156,  1156,  1157,
    1158,  1158,  1159,  1161,  1161,  1166,  1165,  1171,  1172,  1173,
    1174,  1175,  1176,  1179,  1179,  1179,  1181,  1194,  1194,  1195,
    1196,  1196,  1218,  1218,  1241,  1246,  1252,  1263,  1278,  1298
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NULLT", "TYPE", "INTEGER", "STRING",
  "FLOATING_NUM", "CHAR_CONST", "STRUCT", "UNION", "VOID", "ID",
  "FUN_START", "INCLUDE", "PREDEF_HEADER", "ELIF", "ELSE", "IF", "BREAK",
  "NOT", "FOR", "CONTINUE", "WHILE", "SWITCH", "CASE", "RETURN",
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
     325,   326
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    72,    73,    74,    75,    75,    76,    76,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    78,    78,    79,
      79,    80,    80,    81,    81,    81,    81,    82,    83,    85,
      84,    86,    86,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    88,    89,    89,    90,    91,    89,    92,
      89,    93,    89,    94,    94,    95,    95,    95,    95,    95,
      96,    97,    98,    99,    99,    99,    99,    99,    99,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,    99,
      99,   100,    99,    99,    99,   101,   102,   103,   103,   104,
     104,   104,   104,   105,   105,   107,   106,   108,   106,   110,
     109,   111,   109,   112,   113,   113,   114,   114,   114,   114,
     114,   114,   115,   116,   116,   116,   116,   117,   118,   118,
     119,   119,   120,   120,   121,   122,   123,   124,   124,   125,
     125,   126,   127,   128,   129,   130,   130,   130,   130,   131,
     132,   131,   133,   134,   135,   135,   136,   136,   137,   137,
     138,   138,   138,   138,   138,   138,   138,   138,   139,   139,
     140,   141,   141,   142,   143,   145,   144,   146,   144,   144,
     147,   148,   149,   149,   150,   150,   150,   151,   151,   152,
     153,   153,   154,   154,   155,   155,   156,   157,   157,   158,
     159,   159,   160,   162,   161,   163,   161,   164,   164,   164,
     164,   164,   164,   165,   165,   165,   166,   167,   167,   168,
     169,   168,   170,   168,   171,   171,   172,   173,   174,   175
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     3,     1,     0,     1,     1,     1,     1,
       1,     2,     0,     2,     2,     2,     2,     6,     5,     4,
       0,     4,     0,     2,     2,     2,     0,     1,     1,     0,
       7,     1,     0,     1,     1,     1,     1,     1,     1,     4,
       3,     3,     2,     2,     2,     2,     1,     2,     2,     2,
       2,     2,     0,     1,     6,     5,     0,     0,     7,     0,
       5,     0,     5,     4,     0,     2,     2,     2,     2,     0,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       1,     0,     3,     1,     1,     1,     5,     3,     2,     5,
       3,     1,     3,     1,     0,     0,     7,     0,     6,     0,
       6,     0,     5,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,    11,     9,    11,     9,     1,     8,     6,
       5,     4,     1,     0,     1,     6,     4,     1,     2,     3,
       2,     1,     6,     4,     2,     4,     3,     3,     2,     1,
       0,     3,     1,     4,     4,     3,     1,     1,     8,     7,
       1,     2,     7,     6,     5,     3,     4,     5,     1,     3,
       4,     1,     0,     3,     4,     0,     8,     0,     7,     6,
       1,     1,     2,     1,     2,     1,     1,    12,    11,     9,
       5,     0,     3,     0,     1,     1,     1,     1,     1,    12,
       8,     0,     8,     0,    10,     0,     9,     3,     3,     3,
       2,     2,     2,     1,     3,     0,     1,     2,     3,     6,
       0,     7,     0,     7,     1,     1,     1,     3,     3,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,    12,     6,     7,     5,     1,    53,   234,
     235,   196,    28,   132,     0,     0,     9,    26,   195,     8,
       0,     0,    12,    12,    12,    12,     0,    10,    12,     0,
       0,     4,     3,     0,     0,    32,     2,     0,    22,    27,
      26,     0,    71,    52,   108,   195,     0,   111,     0,     0,
      13,    14,    16,    15,   193,     0,    11,   194,     0,   227,
     228,   236,     0,     0,    31,   103,   104,   105,     0,     0,
       0,     0,    23,   100,    24,     0,    25,     0,     0,    20,
       0,     0,   105,     0,     0,   137,     0,     0,     0,   143,
      52,    52,     0,     0,     0,     0,   195,    33,    69,    36,
       0,    38,     0,    37,    34,    35,    52,    52,    52,    52,
      46,    52,   206,   207,   208,    52,    52,     0,     0,   114,
     107,     0,     0,   194,   190,   192,     0,   239,     0,     0,
      29,   105,    85,     0,    84,     0,     0,    83,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    28,    26,    12,     0,     0,   166,   167,     0,
       0,     0,   163,     0,     0,     0,     0,    52,    52,   143,
       0,   142,     0,    42,    43,     0,     0,     0,    72,    12,
      70,    69,     0,     0,    64,     0,     0,    44,    45,    48,
      47,    49,    50,    51,   194,     0,     0,   112,   113,   195,
     110,   183,     0,   184,   195,     0,     0,     0,     0,     0,
       0,     0,    73,   147,     0,    80,    74,    75,    77,    76,
      78,    79,    82,    86,    81,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   102,   131,
     127,   128,   130,   129,   126,   121,     0,   124,    20,    18,
      27,    26,    12,   165,     0,     0,   230,   232,     0,     0,
      41,    40,     0,     0,    52,    61,     0,     0,     0,   106,
      64,     0,    65,    66,    67,    68,    69,     0,     0,   117,
       0,   144,   143,     0,   143,    69,     0,     0,   114,   191,
       0,     0,   187,     0,   182,     0,   215,   221,   220,   222,
     213,    52,     0,   148,   146,    52,   119,     0,    21,    20,
      17,   178,     0,     0,     0,   170,   164,     0,     0,    52,
       0,     0,     0,    39,    52,     0,     0,   154,     0,     0,
       0,     0,    70,    69,    52,     0,   115,     0,    69,     0,
      64,     0,   182,   109,   195,     0,   185,     0,   189,   181,
     238,   237,   225,   218,   217,   219,   225,     0,   151,   150,
     122,    52,   125,    19,     0,   169,     0,   171,     0,     0,
      60,    52,    52,    52,   201,    62,    52,   105,     0,   159,
     158,    52,    52,     0,    57,    64,    55,    52,     0,   143,
      64,   143,     0,     0,   180,     0,     0,   188,   226,     0,
     223,     0,    30,   149,   120,   175,   168,   179,     0,     0,
       0,     0,   139,     0,     0,   203,   145,     0,   156,   157,
     152,    54,   153,    52,    63,   118,    52,     0,     0,     0,
     141,   229,     0,   186,    12,     0,    12,   176,     0,   231,
     233,   211,    52,   205,   204,     0,     0,     0,   161,   155,
      58,   116,     0,   140,     0,     0,   216,   224,   214,   177,
     174,     0,   212,   138,    52,    52,    52,    52,    52,    52,
      52,     0,   173,     0,     0,   201,   202,   199,   136,     0,
       0,   134,     0,   172,     0,    52,   200,    52,    52,     0,
       0,     0,   135,   133,     0,    52,   209,     0,     0,     0,
     198,     0,   211,   197,   210
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    32,     6,    15,    16,   166,    78,    38,
      40,    17,    36,   221,    63,    95,    96,    97,   193,   433,
     175,   334,   288,   194,   191,   322,   189,   181,   160,    98,
      19,    20,    46,   207,    99,   398,   345,    74,   371,   315,
     100,   256,   257,    21,   101,   102,   103,   294,   182,   295,
     104,    76,   224,   313,   369,   105,   285,   278,   337,   390,
     427,    41,   106,   359,   169,   107,   324,   325,   208,   360,
      47,   108,   109,   406,   357,   126,   302,    55,    26,   303,
     110,   425,   457,   455,   111,   112,   113,   472,   114,    27,
     366,   362,   216,   409,   410,   115,   116,   327,   328,   117,
      58,   217,   218,   118
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -364
static const yytype_int16 yypact[] =
{
      25,   240,    73,    44,  -364,  -364,    25,  -364,  -364,  -364,
    -364,  -364,    83,  -364,   111,    21,  -364,    86,    85,  -364,
     101,   170,    44,    44,    44,    44,   141,  -364,    44,   163,
     159,  -364,  -364,   184,   231,   267,  -364,    74,   208,   230,
      86,   253,  -364,   513,  -364,   275,   150,  -364,   141,   281,
    -364,  -364,  -364,  -364,  -364,    62,  -364,    18,   101,  -364,
    -364,  -364,   101,   261,   255,  -364,  -364,   272,    38,    38,
      38,   277,   820,   278,  -364,   288,  -364,   299,   280,   276,
     270,    52,    30,   295,   282,  -364,   286,   298,   327,    38,
     513,   513,   347,   331,   340,   337,   366,  -364,   176,  -364,
     344,  -364,   349,  -364,  -364,  -364,   513,   513,   513,   513,
    -364,   513,  -364,  -364,  -364,   513,   513,   368,    60,   352,
    -364,   267,    75,  -364,  -364,  -364,    77,  -364,   267,   267,
    -364,  -364,   348,   686,  -364,   375,    38,  -364,    38,    38,
      38,    38,    38,    38,    38,    38,    38,    38,    38,    38,
      38,    38,    38,    38,    38,    38,    38,    38,    38,    38,
     253,   246,  -364,    86,    44,   374,   343,  -364,  -364,   356,
     101,   270,  -364,   380,   381,   350,    38,   513,   513,    38,
     383,   820,   358,  -364,  -364,   363,   375,   391,  -364,    44,
     230,   382,   441,   253,   360,   361,    19,  -364,  -364,  -364,
    -364,  -364,  -364,  -364,   410,   101,   270,  -364,  -364,   411,
    -364,  -364,    32,  -364,   412,   141,   337,   378,   389,   390,
     337,   101,  -364,   394,   405,   632,   259,   259,   348,   348,
     348,   507,   886,   566,   868,   447,   379,   379,   362,   362,
     447,   846,   846,   846,   846,   820,   820,   820,   395,  -364,
    -364,  -364,  -364,  -364,  -364,  -364,   151,  -364,   276,  -364,
    -364,    86,    44,  -364,    46,   409,  -364,  -364,   400,   728,
    -364,  -364,   415,   417,   513,  -364,   418,   404,   421,  -364,
     360,   425,   820,  -364,  -364,  -364,   254,   448,   416,  -364,
     152,  -364,    38,   450,    38,   382,   314,   429,   352,  -364,
     267,   453,  -364,   422,   253,    76,  -364,   267,   267,   267,
    -364,   513,    38,  -364,  -364,   513,  -364,   314,  -364,   276,
    -364,  -364,    33,   426,   337,   420,  -364,   445,   446,   513,
     101,    81,   101,  -364,   513,   430,    17,  -364,   432,   434,
     391,   435,  -364,   382,   513,   443,  -364,   444,   382,   458,
     360,   129,   253,  -364,  -364,   141,  -364,   459,  -364,   395,
    -364,  -364,   464,  -364,  -364,  -364,   464,   337,   820,   394,
    -364,   513,  -364,  -364,   337,  -364,   463,    67,   314,   314,
    -364,   513,   513,   513,   467,  -364,   513,   462,   483,  -364,
     404,   513,   513,   480,  -364,   360,  -364,   513,   468,    38,
     360,    38,   471,   472,  -364,   132,   473,  -364,  -364,   194,
    -364,   213,  -364,  -364,  -364,   478,  -364,  -364,    33,   474,
     481,   337,  -364,   337,   287,   461,  -364,   253,   404,  -364,
    -364,  -364,  -364,   513,  -364,  -364,   513,   496,   486,   497,
    -364,  -364,   475,  -364,    44,   464,    44,    33,   337,  -364,
    -364,   522,   513,  -364,  -364,   490,   502,   337,   395,  -364,
    -364,  -364,    88,  -364,   107,   532,  -364,  -364,  -364,  -364,
     520,   539,   553,  -364,   513,   513,   513,   513,   513,   513,
     513,   504,    33,    38,   101,   467,  -364,  -364,  -364,   337,
     337,  -364,   544,  -364,   794,   513,  -364,   513,   513,   267,
     101,   337,  -364,  -364,   161,   513,  -364,   546,   239,   337,
    -364,   548,   522,  -364,  -364
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -364,  -364,   571,  -364,  -364,   -18,  -364,  -241,  -364,   -16,
     419,   505,  -364,  -364,  -364,   324,    -3,  -364,  -364,  -364,
    -364,  -364,  -228,  -108,   296,   -17,   142,   196,  -364,    71,
    -364,  -364,   550,   289,  -364,  -364,  -364,   396,  -364,  -364,
     -26,  -182,  -309,  -364,  -364,  -364,  -364,  -364,  -165,   293,
    -364,   397,   406,   222,  -364,  -364,  -364,   256,  -363,  -364,
    -364,  -364,   120,   -29,  -143,   127,  -313,  -364,  -364,   241,
     476,   134,   167,  -364,  -364,  -364,   294,   -47,   -19,  -364,
    -364,   109,  -364,  -364,  -364,  -364,  -364,    89,  -364,  -364,
    -364,  -364,   -70,   234,   157,   245,  -364,  -364,  -364,    12,
     575,  -364,  -364,    68
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -237
static const yytype_int16 yytable[] =
{
      18,   122,    48,    43,    50,    51,    52,    53,   372,   374,
      56,    75,    81,   290,   272,    29,    48,   318,    45,    18,
      18,    18,    18,     8,    79,    18,    34,   429,   265,   387,
     127,   291,    45,    49,    29,    29,    29,    29,   321,     1,
      29,   128,    33,    65,   299,   129,    66,    49,     8,  -236,
     131,   321,   339,     9,    10,    11,    12,    13,    68,   220,
    -123,   388,   300,   297,    42,   459,   292,   -59,    69,   419,
     420,    30,   417,     7,   124,    70,   301,    42,   373,    65,
     188,   170,    66,   280,   171,    35,    67,   211,   361,   205,
      30,    30,    30,    30,    68,    33,    30,    39,    42,   172,
     173,   174,    48,   125,    69,   448,   212,    59,    73,   215,
     215,    70,    42,    14,   351,    37,   125,   125,   209,    42,
       9,    10,   402,    22,   213,   214,   214,   347,   382,   349,
      23,   248,    42,    49,   469,   477,    71,    24,   479,    73,
      73,    73,    22,    22,    22,    22,   259,   258,    22,    23,
      23,    23,    23,   264,   480,    23,    24,    24,    24,    24,
      73,    18,    24,   188,   286,   442,    75,   434,   305,   493,
      25,   279,   438,   125,     8,    57,    29,   317,   341,     9,
      10,    11,    54,   120,   316,   346,    18,   350,   296,    25,
      25,    25,    25,   293,   507,    25,   219,   219,   121,   317,
     317,    29,    54,    44,   311,   192,    59,    73,   -56,    73,
      73,    73,    73,    73,    73,    73,    73,    73,    73,    73,
      73,    73,    73,    73,    73,    73,    73,    73,    73,    73,
      73,    60,    30,    72,   437,   395,   439,   363,   364,   365,
     400,   444,   445,    61,   320,   319,     4,    73,    28,   249,
      73,   250,   251,   252,   253,     5,    77,    30,   254,    18,
     446,   445,  -162,    73,   132,   133,   134,    28,    28,    28,
      28,     8,   511,    28,    29,   167,     9,    10,    11,   255,
     125,   355,   168,   192,    22,    80,   171,   119,   215,   215,
     215,    23,   453,   123,   130,   454,   137,   354,    24,   140,
     141,   142,  -123,   121,   214,   214,   214,   135,   405,    22,
    -101,   162,    49,   381,   383,   384,    23,   249,   161,   250,
     251,   252,   253,    24,   165,   176,   254,   164,   179,   177,
      30,    25,   225,   178,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,    25,   180,   306,   185,
     418,   186,   310,    73,   249,    73,   250,   251,   252,   253,
     187,   188,   269,   254,   195,   219,   219,   219,   190,   196,
     204,   223,    22,    73,   206,   137,   260,   268,   282,    23,
     262,   263,   266,   267,   289,   273,    24,   277,   458,   137,
     138,   139,   140,   141,   142,   274,   323,   389,   287,    28,
     275,   192,   148,   149,   183,   184,   137,   138,   139,   140,
     141,   142,   127,   298,   304,   307,   466,   171,   468,    25,
     197,   198,   199,   200,    28,   201,   308,   309,   314,   202,
     203,    18,   312,    18,   326,   478,    65,   329,   331,    66,
     332,   335,   336,    67,   338,   340,    29,   508,    29,   428,
     342,    68,   291,   344,   352,   299,   376,   495,   377,   358,
      73,    69,    73,   375,   378,   379,   408,   386,    70,   391,
     504,   392,   394,   505,   137,   138,   139,   140,   141,   142,
     397,   399,   424,   403,  -160,   131,   354,   148,   149,   150,
     151,   270,   271,    71,   281,   401,   407,    28,   368,   412,
     416,    49,    30,   432,    30,   436,   415,     8,   440,   441,
     443,   449,     9,    10,    11,    82,   447,   456,   450,   462,
     464,    83,    84,   463,    85,    86,    87,    88,   471,    89,
      90,    91,   465,   136,   137,   138,   139,   140,   141,   142,
      92,   144,   145,   146,    73,   474,   147,   148,   149,   150,
     151,   152,   481,   451,    22,   452,    22,   475,   482,   483,
     484,    23,   492,    23,   499,    93,    94,    31,    24,   510,
      24,   513,   163,   343,   261,    64,   348,   353,   283,   284,
     470,   413,   276,   404,   496,   356,   393,   210,   333,   476,
     411,   514,   467,   137,   138,   139,   140,   141,   142,    62,
     144,    25,   146,    25,     0,   147,   148,   149,   150,   151,
     152,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   497,   498,     0,     0,   367,     0,     0,     0,   370,
       0,     0,     0,   506,     0,     0,     0,     0,     0,     0,
       0,   512,     0,   380,     0,     0,     0,     0,   385,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   396,   137,
     138,   139,   140,   141,   142,     0,   144,   145,   146,   494,
       0,   147,   148,   149,   150,   151,   152,     0,     0,    28,
       0,    28,     0,     0,     0,   414,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   421,   422,   423,     0,     0,
     426,     0,     0,     0,     0,   430,   431,     0,     0,   222,
       0,   435,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,     0,     0,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   460,     0,     0,
     461,   330,     0,     0,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,     0,   473,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
       0,     0,     0,     0,     0,     0,     0,     0,   485,   486,
     487,   488,   489,   490,   491,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   501,
       0,   502,   503,     0,     0,     0,     0,   500,     0,   509,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,     0,     0,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,     0,     0,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,     0,     0,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   137,   138,   139,   140,   141,
     142,     0,   144,     0,     0,     0,     0,   147,   148,   149,
     150,   151,   152,   137,   138,   139,   140,   141,   142,     0,
       0,     0,     0,     0,     0,   147,   148,   149,   150,   151,
     152
};

static const yytype_int16 yycheck[] =
{
       3,    48,    21,    20,    22,    23,    24,    25,   317,   322,
      28,    37,    41,   195,   179,     3,    35,   258,    21,    22,
      23,    24,    25,     4,    40,    28,    14,   390,   171,    12,
      12,    12,    35,    21,    22,    23,    24,    25,     5,    14,
      28,    58,    12,     5,    12,    62,     8,    35,     4,    31,
      12,     5,   280,     9,    10,    11,    12,    13,    20,   129,
      30,    44,    30,   206,    31,   428,    47,    37,    30,   378,
     379,     3,     5,     0,    12,    37,    44,    31,   319,     5,
      34,    29,     8,   191,    32,    64,    12,    12,    12,    29,
      22,    23,    24,    25,    20,    12,    28,    12,    31,    47,
      70,    71,   121,    41,    30,   418,    29,    47,    37,   128,
     129,    37,    31,    69,   296,    29,    41,    41,   121,    31,
       9,    10,   350,     3,    47,   128,   129,   292,    47,   294,
       3,   160,    31,   121,   447,    47,    62,     3,    31,    68,
      69,    70,    22,    23,    24,    25,   164,   163,    28,    22,
      23,    24,    25,   170,    47,    28,    22,    23,    24,    25,
      89,   164,    28,    34,   193,    33,   192,   395,   215,   482,
       3,   189,   400,    41,     4,    12,   164,    48,   286,     9,
      10,    11,    41,    33,    33,    33,   189,   295,   205,    22,
      23,    24,    25,   196,    33,    28,   128,   129,    48,    48,
      48,   189,    41,    33,   221,    29,    47,   136,    32,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,    47,   164,    37,   399,   343,   401,   307,   308,   309,
     348,    47,    48,    12,   262,   261,     6,   176,     3,     3,
     179,     5,     6,     7,     8,    15,    48,   189,    12,   262,
      47,    48,    32,   192,    68,    69,    70,    22,    23,    24,
      25,     4,    33,    28,   262,     5,     9,    10,    11,    33,
      41,   300,    12,    29,   164,    32,    32,    12,   307,   308,
     309,   164,     5,    12,    33,     8,    37,   300,   164,    40,
      41,    42,    30,    48,   307,   308,   309,    30,   355,   189,
      32,    12,   300,   330,   331,   332,   189,     3,    30,     5,
       6,     7,     8,   189,    48,    30,    12,    47,    30,    47,
     262,   164,   136,    47,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   189,    30,   216,    12,
     377,    30,   220,   292,     3,   294,     5,     6,     7,     8,
      30,    34,   176,    12,    30,   307,   308,   309,    12,    30,
      12,     6,   262,   312,    32,    37,    12,    37,   192,   262,
      47,    35,    12,    12,    33,    12,   262,     6,   427,    37,
      38,    39,    40,    41,    42,    47,   264,   336,    48,   164,
      47,    29,    50,    51,    90,    91,    37,    38,    39,    40,
      41,    42,    12,    12,    12,    47,   444,    32,   446,   262,
     106,   107,   108,   109,   189,   111,    47,    47,    33,   115,
     116,   444,    48,   446,    35,   462,     5,    47,    33,     8,
      33,    33,    48,    12,    33,    30,   444,   504,   446,   388,
      12,    20,    12,    47,    35,    12,   324,   484,    48,    47,
     399,    30,   401,    47,    29,    29,    12,    47,    37,    47,
     499,    47,    47,   500,    37,    38,    39,    40,    41,    42,
      47,    47,    25,   351,    32,    12,   499,    50,    51,    52,
      53,   177,   178,    62,    63,    47,    47,   262,   312,   367,
      47,   499,   444,    33,   446,    47,   374,     4,    47,    47,
      47,    47,     9,    10,    11,    12,    48,    66,    47,    33,
      33,    18,    19,    47,    21,    22,    23,    24,    16,    26,
      27,    28,    67,    36,    37,    38,    39,    40,    41,    42,
      37,    44,    45,    46,   483,    65,    49,    50,    51,    52,
      53,    54,    30,   421,   444,   423,   446,    65,    48,    30,
      17,   444,    68,   446,    30,    62,    63,     6,   444,    33,
     446,    33,    77,   287,   165,    35,   293,   298,   192,   192,
     448,   369,   186,   352,   485,   301,   340,   121,   274,   457,
     366,   512,   445,    37,    38,    39,    40,    41,    42,    34,
      44,   444,    46,   446,    -1,    49,    50,    51,    52,    53,
      54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   489,   490,    -1,    -1,   311,    -1,    -1,    -1,   315,
      -1,    -1,    -1,   501,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   509,    -1,   329,    -1,    -1,    -1,    -1,   334,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   344,    37,
      38,    39,    40,    41,    42,    -1,    44,    45,    46,   483,
      -1,    49,    50,    51,    52,    53,    54,    -1,    -1,   444,
      -1,   446,    -1,    -1,    -1,   371,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   381,   382,   383,    -1,    -1,
     386,    -1,    -1,    -1,    -1,   391,   392,    -1,    -1,    33,
      -1,   397,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    -1,    -1,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   433,    -1,    -1,
     436,    33,    -1,    -1,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    -1,   452,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   474,   475,
     476,   477,   478,   479,   480,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   495,
      -1,   497,   498,    -1,    -1,    -1,    -1,    33,    -1,   505,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    -1,    -1,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    -1,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    -1,    -1,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    37,    38,    39,    40,    41,
      42,    -1,    44,    -1,    -1,    -1,    -1,    49,    50,    51,
      52,    53,    54,    37,    38,    39,    40,    41,    42,    -1,
      -1,    -1,    -1,    -1,    -1,    49,    50,    51,    52,    53,
      54
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    14,    73,    74,     6,    15,    76,     0,     4,     9,
      10,    11,    12,    13,    69,    77,    78,    83,    88,   102,
     103,   115,   134,   137,   143,   144,   150,   161,   167,   171,
     175,    74,    75,    12,   171,    64,    84,    29,    81,    12,
      82,   133,    31,    97,    33,    88,   104,   142,   150,   171,
      77,    77,    77,    77,    41,   149,    77,    12,   172,    47,
      47,    12,   172,    86,   104,     5,     8,    12,    20,    30,
      37,    62,    99,   101,   109,   112,   123,    48,    80,    81,
      32,   135,    12,    18,    19,    21,    22,    23,    24,    26,
      27,    28,    37,    62,    63,    87,    88,    89,   101,   106,
     112,   116,   117,   118,   122,   127,   134,   137,   143,   144,
     152,   156,   157,   158,   160,   167,   168,   171,   175,    12,
      33,    48,   149,    12,    12,    41,   147,    12,    97,    97,
      33,    12,    99,    99,    99,    30,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
     100,    30,    12,    83,    47,    48,    79,     5,    12,   136,
      29,    32,    47,    70,    71,    92,    30,    47,    47,    30,
      30,    99,   120,    87,    87,    12,    30,    30,    34,    98,
      12,    96,    29,    90,    95,    30,    30,    87,    87,    87,
      87,    87,    87,    87,    12,    29,    32,   105,   140,    88,
     142,    12,    29,    47,    88,   150,   164,   173,   174,   175,
     164,    85,    33,     6,   124,    99,    99,    99,    99,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,    99,
      99,    99,    99,    99,    99,    99,    99,    99,   135,     3,
       5,     6,     7,     8,    12,    33,   113,   114,    81,    77,
      12,    82,    47,    35,    97,   136,    12,    12,    37,    99,
      87,    87,   120,    12,    47,    47,   124,     6,   129,    77,
      95,    63,    99,   109,   123,   128,   135,    48,    94,    33,
     113,    12,    47,    88,   119,   121,    97,   136,    12,    12,
      30,    44,   148,   151,    12,   149,    98,    47,    47,    47,
      98,    97,    48,   125,    33,   111,    33,    48,    79,    81,
      77,     5,    97,    98,   138,   139,    35,   169,   170,    47,
      33,    33,    33,    87,    93,    33,    48,   130,    33,    94,
      30,    95,    12,    96,    47,   108,    33,   120,   121,   120,
      95,   113,    35,   105,    88,   150,   148,   146,    47,   135,
     141,    12,   163,   164,   164,   164,   162,    87,    99,   126,
      87,   110,   114,    79,   138,    47,    98,    48,    29,    29,
      87,    97,    47,    97,    97,    87,    47,    12,    44,   101,
     131,    47,    47,   129,    47,    95,    87,    47,   107,    47,
      95,    47,    94,    98,   141,   149,   145,    47,    12,   165,
     166,   165,    98,   125,    87,    98,    47,     5,    97,   114,
     114,    87,    87,    87,    25,   153,    87,   132,   101,   130,
      87,    87,    33,    91,    94,    87,    47,   120,    94,   120,
      47,    47,    33,    47,    47,    48,    47,    48,   138,    47,
      47,    98,    98,     5,     8,   155,    66,   154,   135,   130,
      87,    87,    33,    47,    33,    67,    77,   166,    77,   138,
      98,    16,   159,    87,    65,    65,    98,    47,    97,    31,
      47,    30,    48,    30,    17,    87,    87,    87,    87,    87,
      87,    87,    68,   138,    99,    97,   153,    98,    98,    30,
      33,    87,    87,    87,   150,    97,    98,    33,   149,    87,
      33,    33,    98,    33,   159
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

  case 56:

/* Line 1455 of yacc.c  */
#line 499 "semanticAnalysis.y"
    {dimit = 0;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 499 "semanticAnalysis.y"
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

  case 59:

/* Line 1455 of yacc.c  */
#line 518 "semanticAnalysis.y"
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

  case 61:

/* Line 1455 of yacc.c  */
#line 529 "semanticAnalysis.y"
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

  case 66:

/* Line 1455 of yacc.c  */
#line 542 "semanticAnalysis.y"
    {
    if(strcmp(forFunc->dataType,"void")==0){
        char const errorMessage[100]="Void Function Does not return anything";
        int a=yyerror(errorMessage);
        return -1;
    }
}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 550 "semanticAnalysis.y"
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

  case 71:

/* Line 1455 of yacc.c  */
#line 562 "semanticAnalysis.y"
    {scope++;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 563 "semanticAnalysis.y"
    {deleteDMT(scope);scope--;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 592 "semanticAnalysis.y"
    {dimit = 0;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 593 "semanticAnalysis.y"
    {dimit = 0;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 593 "semanticAnalysis.y"
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

  case 105:

/* Line 1455 of yacc.c  */
#line 605 "semanticAnalysis.y"
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

  case 107:

/* Line 1455 of yacc.c  */
#line 619 "semanticAnalysis.y"
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

  case 108:

/* Line 1455 of yacc.c  */
#line 630 "semanticAnalysis.y"
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
#line 641 "semanticAnalysis.y"
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

  case 110:

/* Line 1455 of yacc.c  */
#line 674 "semanticAnalysis.y"
    {
                    struct SymbolTableEntry*new_entry = insertIdentifier(ptrBuf,CLASS[3],(yyvsp[(3) - (3)].type),pointerLen,yylinenumber,scope+1);
                    PD[noOfParameters]=pointerLen;
                    strcpy(PL[noOfParameters],(yyvsp[(3) - (3)].type));
                    PTL[noOfParameters]='p';
                    noOfParameters++;
                }
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 681 "semanticAnalysis.y"
    {
                    struct SymbolTableEntry*new_entry = insertIdentifier(ptrBuf,CLASS[3],(yyvsp[(1) - (1)].type),pointerLen,yylinenumber,scope+1);
                    PD[noOfParameters]=pointerLen;
                    strcpy(PL[noOfParameters],(yyvsp[(1) - (1)].type));
                    PTL[noOfParameters]='p';
                    noOfParameters++;
                    pointerLen=1;
                }
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 689 "semanticAnalysis.y"
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

  case 113:

/* Line 1455 of yacc.c  */
#line 709 "semanticAnalysis.y"
    {
    (yyval.type)=malloc(strlen("array")+1);strcpy((yyval.type),"array");

    }
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 712 "semanticAnalysis.y"
    {(yyval.type)=malloc(strlen("variable")+1);strcpy((yyval.type),"variable");}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 715 "semanticAnalysis.y"
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

  case 117:

/* Line 1455 of yacc.c  */
#line 750 "semanticAnalysis.y"
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

  case 119:

/* Line 1455 of yacc.c  */
#line 798 "semanticAnalysis.y"
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

  case 121:

/* Line 1455 of yacc.c  */
#line 833 "semanticAnalysis.y"
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

  case 123:

/* Line 1455 of yacc.c  */
#line 879 "semanticAnalysis.y"
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

  case 124:

/* Line 1455 of yacc.c  */
#line 896 "semanticAnalysis.y"
    {
    strcpy(PL[noOfParameters],(yyvsp[(1) - (1)].type));
    PTL[noOfParameters]=pt;
    noOfParameters++;
}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 901 "semanticAnalysis.y"
    {
            strcpy(PL[noOfParameters],(yyvsp[(3) - (3)].type));
            PTL[noOfParameters]=pt;
            noOfParameters++;
        }
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 906 "semanticAnalysis.y"
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

  case 127:

/* Line 1455 of yacc.c  */
#line 934 "semanticAnalysis.y"
    {(yyval.type)=malloc(strlen((yyvsp[(1) - (1)].type))+1);strcpy((yyval.type),(yyvsp[(1) - (1)].type));pt='v';parD[parDi++]=0;}
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

  case 132:

/* Line 1455 of yacc.c  */
#line 940 "semanticAnalysis.y"
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

  case 137:

/* Line 1455 of yacc.c  */
#line 978 "semanticAnalysis.y"
    {scope++;}
    break;

  case 144:

/* Line 1455 of yacc.c  */
#line 988 "semanticAnalysis.y"
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

  case 160:

/* Line 1455 of yacc.c  */
#line 1015 "semanticAnalysis.y"
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

  case 161:

/* Line 1455 of yacc.c  */
#line 1024 "semanticAnalysis.y"
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

  case 162:

/* Line 1455 of yacc.c  */
#line 1035 "semanticAnalysis.y"
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

  case 163:

/* Line 1455 of yacc.c  */
#line 1049 "semanticAnalysis.y"
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

  case 166:

/* Line 1455 of yacc.c  */
#line 1060 "semanticAnalysis.y"
    {dimbuffer[dimit++] = intval;}
    break;

  case 167:

/* Line 1455 of yacc.c  */
#line 1060 "semanticAnalysis.y"
    {dimbuffer[dimit++] = 10000;}
    break;

  case 168:

/* Line 1455 of yacc.c  */
#line 1061 "semanticAnalysis.y"
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

  case 169:

/* Line 1455 of yacc.c  */
#line 1070 "semanticAnalysis.y"
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

  case 183:

/* Line 1455 of yacc.c  */
#line 1092 "semanticAnalysis.y"
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

  case 185:

/* Line 1455 of yacc.c  */
#line 1108 "semanticAnalysis.y"
    {if(strcmp((yyvsp[(3) - (6)].type),(yyvsp[(6) - (6)].type))!=0){
    char message[30]="Variable Types dont Match";
        int res=yyerror(message);
        return -1;}}
    break;

  case 187:

/* Line 1455 of yacc.c  */
#line 1111 "semanticAnalysis.y"
    {if(strcmp((yyvsp[(3) - (5)].type),(yyvsp[(5) - (5)].type))!=0){
    char message[30]="Variable Types dont Match";
        int res=yyerror(message);
        return -1;
}}
    break;

  case 190:

/* Line 1455 of yacc.c  */
#line 1117 "semanticAnalysis.y"
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

  case 191:

/* Line 1455 of yacc.c  */
#line 1131 "semanticAnalysis.y"
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

  case 192:

/* Line 1455 of yacc.c  */
#line 1143 "semanticAnalysis.y"
    {  
     pointerLen++;
}
    break;

  case 213:

/* Line 1455 of yacc.c  */
#line 1161 "semanticAnalysis.y"
    {
        struct SymbolTableEntry*new_entry=insertIdentifier(userTypeNameBuffer,CLASS[4],userTypeBuffer,userTypeDim,yylinenumber,scope);
        userTypeDim = 0;
    }
    break;

  case 215:

/* Line 1455 of yacc.c  */
#line 1166 "semanticAnalysis.y"
    {
        struct SymbolTableEntry*new_entry=insertIdentifier(userTypeNameBuffer,CLASS[4],userTypeBuffer,userTypeDim,yylinenumber,scope);
        userTypeDim = 0;
                }
    break;

  case 226:

/* Line 1455 of yacc.c  */
#line 1181 "semanticAnalysis.y"
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

  case 230:

/* Line 1455 of yacc.c  */
#line 1196 "semanticAnalysis.y"
    {
                            struct SymbolTableEntry * search=lookup((yyvsp[(1) - (3)].value),1,true);
                            
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

  case 232:

/* Line 1455 of yacc.c  */
#line 1218 "semanticAnalysis.y"
    {
                            struct SymbolTableEntry * search=lookup((yyvsp[(1) - (3)].value),1,true);
                            
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

  case 234:

/* Line 1455 of yacc.c  */
#line 1241 "semanticAnalysis.y"
    {
            strcpy(userTypeBuffer,(yyvsp[(1) - (1)].type));
            (yyval.type)=malloc(strlen((yyvsp[(1) - (1)].type))+1);
            strcpy((yyval.type),(yyvsp[(1) - (1)].type));
        }
    break;

  case 235:

/* Line 1455 of yacc.c  */
#line 1246 "semanticAnalysis.y"
    {
            strcpy(userTypeBuffer,(yyvsp[(1) - (1)].type));
            (yyval.type)=malloc(strlen((yyvsp[(1) - (1)].type))+1);
            strcpy((yyval.type),(yyvsp[(1) - (1)].type));
        }
    break;

  case 236:

/* Line 1455 of yacc.c  */
#line 1252 "semanticAnalysis.y"
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

  case 237:

/* Line 1455 of yacc.c  */
#line 1263 "semanticAnalysis.y"
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

  case 238:

/* Line 1455 of yacc.c  */
#line 1279 "semanticAnalysis.y"
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

  case 239:

/* Line 1455 of yacc.c  */
#line 1299 "semanticAnalysis.y"
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
#line 3573 "y.tab.c"
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
#line 1322 "semanticAnalysis.y"


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
