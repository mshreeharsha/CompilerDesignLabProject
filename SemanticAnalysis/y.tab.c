
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
#line 488 "y.tab.c"

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
#line 415 ".\\semanticAnalysis.y"

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
#define YYLAST   992

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  72
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  104
/* YYNRULES -- Number of rules.  */
#define YYNRULES  238
/* YYNRULES -- Number of states.  */
#define YYNSTATES  510

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
      58,    59,    64,    65,    68,    71,    72,    74,    76,    77,
      85,    87,    88,    90,    92,    94,    96,    98,   100,   105,
     109,   113,   116,   119,   122,   125,   127,   130,   133,   136,
     139,   142,   143,   145,   152,   158,   159,   160,   168,   169,
     175,   176,   182,   187,   188,   191,   194,   195,   197,   199,
     201,   205,   209,   213,   217,   221,   225,   229,   233,   237,
     241,   244,   247,   250,   254,   258,   262,   266,   270,   274,
     278,   282,   286,   290,   294,   298,   302,   306,   308,   309,
     313,   315,   317,   319,   325,   329,   332,   338,   342,   344,
     348,   350,   351,   352,   360,   361,   368,   369,   376,   377,
     383,   385,   387,   391,   393,   395,   397,   399,   401,   403,
     405,   417,   427,   439,   449,   451,   460,   467,   473,   478,
     480,   481,   483,   490,   492,   495,   499,   502,   504,   506,
     513,   516,   521,   525,   529,   532,   534,   536,   539,   544,
     548,   550,   552,   557,   562,   566,   568,   570,   579,   587,
     589,   592,   600,   607,   613,   617,   622,   628,   630,   634,
     639,   641,   642,   646,   651,   652,   661,   662,   670,   677,
     679,   681,   684,   686,   689,   691,   693,   706,   718,   728,
     734,   735,   739,   740,   742,   744,   746,   748,   750,   763,
     772,   773,   782,   783,   794,   795,   805,   809,   813,   817,
     820,   823,   826,   828,   832,   833,   835,   838,   842,   849,
     850,   858,   859,   867,   869,   871,   873,   877,   881
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
      -1,    -1,    12,    -1,    12,    -1,    -1,    64,    86,    33,
      85,    97,    87,    98,    -1,   104,    -1,    -1,    89,    -1,
     122,    -1,   126,    -1,   106,    -1,   118,    -1,   116,    -1,
      26,   120,    47,    87,    -1,    22,    47,    87,    -1,    19,
      47,    87,    -1,    27,    87,    -1,    28,    87,    -1,   134,
      87,    -1,   137,    87,    -1,   152,    -1,   144,    87,    -1,
     143,    87,    -1,   156,    87,    -1,   167,    87,    -1,   168,
      87,    -1,    -1,     4,    -1,    88,    96,    95,    94,    47,
      87,    -1,   101,    95,    94,    47,    87,    -1,    -1,    -1,
     101,    90,   135,    95,    47,    91,    87,    -1,    -1,    12,
      92,    37,    47,    87,    -1,    -1,    37,    12,    47,    93,
      87,    -1,    48,    96,    95,    94,    -1,    -1,    29,    99,
      -1,    29,   109,    -1,    -1,    12,    -1,    31,    -1,    34,
      -1,    30,    99,    33,    -1,    99,    38,    99,    -1,    99,
      39,    99,    -1,    99,    41,    99,    -1,    99,    40,    99,
      -1,    99,    42,    99,    -1,    99,    43,    99,    -1,    99,
      36,    99,    -1,    99,    46,    99,    -1,    99,    44,    99,
      -1,    99,    37,    -1,    37,    99,    -1,    20,    99,    -1,
      99,    45,    99,    -1,    99,    49,    99,    -1,    99,    50,
      99,    -1,    99,    51,    99,    -1,    99,    52,    99,    -1,
      99,    53,    99,    -1,    99,    54,    99,    -1,    99,    55,
      99,    -1,    99,    56,    99,    -1,    99,    57,    99,    -1,
      99,    58,    99,    -1,    99,    59,    99,    -1,    99,    60,
      99,    -1,    99,    61,    99,    -1,   101,    -1,    -1,   101,
     100,   135,    -1,     5,    -1,     8,    -1,    12,    -1,   103,
      97,    87,    98,    77,    -1,   115,   104,    33,    -1,   115,
      33,    -1,   104,    48,    88,    12,   105,    -1,   104,    48,
     142,    -1,   142,    -1,    88,    12,   105,    -1,   140,    -1,
      -1,    -1,   112,    30,   113,    33,   107,    47,    87,    -1,
      -1,   112,    30,    33,   108,    47,    87,    -1,    -1,   112,
      30,   113,    33,   110,    87,    -1,    -1,   112,    30,    33,
     111,    87,    -1,    12,    -1,   114,    -1,   113,    48,   114,
      -1,    12,    -1,     5,    -1,     6,    -1,     8,    -1,     7,
      -1,     3,    -1,    13,    -1,   117,    30,   119,   120,    47,
     120,    33,    31,    87,    98,    87,    -1,   117,    30,   119,
     120,    47,   120,    33,    47,    87,    -1,   117,    30,    47,
     120,    47,   120,    33,    97,    87,    98,    87,    -1,   117,
      30,    47,   120,    47,   120,    33,    47,    87,    -1,    21,
      -1,    23,    30,   120,    33,    97,    87,    98,    87,    -1,
      23,    30,   120,    33,    47,    87,    -1,    88,   121,    95,
      94,    47,    -1,   121,    95,    94,    47,    -1,    99,    -1,
      -1,    12,    -1,    62,    30,   123,    33,    47,    87,    -1,
       6,    -1,     6,   124,    -1,    48,   125,   124,    -1,    48,
     125,    -1,    99,    -1,   130,    -1,    63,    30,   127,    33,
      47,    87,    -1,     6,   128,    -1,    48,    44,    12,   128,
      -1,    48,    44,    12,    -1,    48,   129,   128,    -1,    48,
     129,    -1,    12,    -1,   130,    -1,    12,   131,    -1,   132,
      99,    35,   131,    -1,   132,    99,    35,    -1,    32,    -1,
      12,    -1,    88,   133,   135,    47,    -1,   135,   132,   136,
      35,    -1,   132,   136,    35,    -1,     5,    -1,    12,    -1,
      88,   133,   135,    29,    97,   138,    98,    47,    -1,    88,
     133,   135,    29,    97,    98,    47,    -1,   139,    -1,   139,
      48,    -1,   139,    48,    97,   138,    98,    48,   138,    -1,
     139,    48,    97,   138,    98,    48,    -1,   139,    48,    97,
     138,    98,    -1,    97,   138,    98,    -1,    97,   138,    98,
      48,    -1,    97,   138,    98,    48,   138,    -1,     5,    -1,
     139,    48,     5,    -1,    32,   136,    35,   141,    -1,   135,
      -1,    -1,   150,   149,    12,    -1,   150,   149,   147,    47,
      -1,    -1,   150,   149,   147,    29,    44,   148,   145,    47,
      -1,    -1,   150,   149,   147,    29,   148,   146,    47,    -1,
     150,   149,   147,    29,   151,    47,    -1,    12,    -1,    12,
      -1,   149,    41,    -1,    41,    -1,   171,    12,    -1,    88,
      -1,    11,    -1,    30,   150,   149,    33,    67,    30,    68,
      30,   150,   149,    33,    33,    -1,    30,   150,   149,    33,
      67,    30,    68,    30,   150,    33,    33,    -1,    24,    30,
      12,    33,    97,   153,   154,    98,    87,    -1,    25,   155,
      65,    87,   153,    -1,    -1,    66,    65,    87,    -1,    -1,
       8,    -1,     5,    -1,   157,    -1,   158,    -1,   160,    -1,
      18,    30,    99,    33,    97,    87,    98,   159,    17,    97,
      87,    98,    -1,    16,    30,    99,    33,    97,    87,    98,
     159,    -1,    -1,    18,    30,    99,    33,    97,    87,    98,
     159,    -1,    -1,    69,   171,   172,    97,   164,    98,   162,
     165,    47,    77,    -1,    -1,   171,   172,    97,   164,    98,
     163,   165,    47,    77,    -1,   174,    47,   164,    -1,   173,
      47,   164,    -1,   175,    47,   164,    -1,   174,    47,    -1,
     173,    47,    -1,   175,    47,    -1,   166,    -1,   165,    48,
     166,    -1,    -1,    12,    -1,   175,    47,    -1,    12,    12,
      47,    -1,   175,    29,    97,   113,    98,    47,    -1,    -1,
      12,    70,    12,   169,    29,   114,    47,    -1,    -1,    12,
      71,    12,   170,    29,   114,    47,    -1,     9,    -1,    10,
      -1,    12,    -1,   150,   149,    12,    -1,    88,    12,   141,
      -1,   171,    12,    12,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   442,   442,   443,   444,   444,   445,   445,   447,   447,
     447,   447,   447,   448,   448,   448,   448,   450,   451,   452,
     452,   453,   453,   454,   454,   460,   462,   473,   485,   485,
     486,   486,   488,   488,   488,   488,   488,   488,   489,   489,
     489,   490,   490,   490,   490,   491,   491,   491,   491,   492,
     492,   492,   494,   499,   500,   501,   501,   501,   520,   520,
     531,   531,   543,   543,   544,   544,   550,   552,   564,   565,
     567,   568,   569,   570,   571,   572,   573,   574,   575,   576,
     577,   578,   579,   580,   581,   582,   583,   584,   585,   586,
     587,   588,   589,   590,   591,   592,   593,   594,   595,   595,
     596,   596,   598,   611,   612,   623,   634,   667,   674,   682,
     702,   705,   708,   708,   743,   743,   791,   791,   826,   826,
     872,   889,   894,   899,   927,   928,   929,   930,   931,   933,
     966,   967,   968,   969,   971,   973,   974,   976,   977,   979,
     979,   981,   993,   994,   995,   996,   997,   998,   998,  1000,
    1001,  1002,  1003,  1004,  1005,  1006,  1006,  1008,  1009,  1009,
    1011,  1013,  1026,  1036,  1036,  1038,  1038,  1039,  1039,  1040,
    1041,  1042,  1043,  1044,  1045,  1046,  1047,  1048,  1048,  1050,
    1051,  1051,  1053,  1068,  1069,  1069,  1072,  1072,  1076,  1078,
    1092,  1104,  1106,  1107,  1107,  1107,  1108,  1109,  1111,  1112,
    1112,  1113,  1113,  1114,  1114,  1116,  1117,  1117,  1118,  1119,
    1119,  1120,  1122,  1122,  1127,  1126,  1132,  1133,  1134,  1135,
    1136,  1137,  1140,  1140,  1140,  1142,  1155,  1155,  1156,  1157,
    1157,  1179,  1179,  1202,  1207,  1213,  1224,  1239,  1259
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
  "idFor", "print", "printExpr", "printArguments", "printContent", "scanf",
  "scanfExpr", "scanfArguments", "scanfContent", "arrayElement",
  "dimension", "open_sq", "ID2", "arrayDeclr", "BOX", "integer_dim",
  "arrayInitial", "BALANCED_BRACK", "arrayParams_unend",
  "arrayAsAParameter", "higherDimention", "pointerAsAParameter",
  "PTR_DECLR", "PTR_INITIAL", "$@11", "$@12", "idinsert", "idlook",
  "PTR_STAR", "PTR_TYPE", "PTR_EXP", "switch", "switchcase", "default",
  "comp", "ifElseLadder", "S", "matched", "elif", "unmatched",
  "userTypeDefination", "$@13", "$@14", "userTypeParams", "userTypeObj",
  "uIDi", "userTypeDeclaration", "userTypeInitialization", "$@15", "$@16",
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
      79,    80,    80,    81,    81,    81,    82,    83,    85,    84,
      86,    86,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    88,    89,    89,    90,    91,    89,    92,    89,
      93,    89,    94,    94,    95,    95,    95,    96,    97,    98,
      99,    99,    99,    99,    99,    99,    99,    99,    99,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,    99,
      99,    99,    99,    99,    99,    99,    99,    99,   100,    99,
      99,    99,   101,   102,   103,   103,   104,   104,   104,   104,
     105,   105,   107,   106,   108,   106,   110,   109,   111,   109,
     112,   113,   113,   114,   114,   114,   114,   114,   114,   115,
     116,   116,   116,   116,   117,   118,   118,   119,   119,   120,
     120,   121,   122,   123,   123,   124,   124,   125,   125,   126,
     127,   128,   128,   128,   128,   129,   129,   130,   131,   131,
     132,   133,   134,   135,   135,   136,   136,   137,   137,   138,
     138,   138,   138,   138,   138,   138,   138,   139,   139,   140,
     141,   141,   142,   143,   145,   144,   146,   144,   144,   147,
     148,   149,   149,   150,   150,   150,   151,   151,   152,   153,
     153,   154,   154,   155,   155,   156,   157,   157,   158,   159,
     159,   160,   162,   161,   163,   161,   164,   164,   164,   164,
     164,   164,   165,   165,   165,   166,   167,   167,   168,   169,
     168,   170,   168,   171,   171,   172,   173,   174,   175
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     3,     1,     0,     1,     1,     1,     1,
       1,     2,     0,     2,     2,     2,     2,     6,     5,     4,
       0,     4,     0,     2,     2,     0,     1,     1,     0,     7,
       1,     0,     1,     1,     1,     1,     1,     1,     4,     3,
       3,     2,     2,     2,     2,     1,     2,     2,     2,     2,
       2,     0,     1,     6,     5,     0,     0,     7,     0,     5,
       0,     5,     4,     0,     2,     2,     0,     1,     1,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     1,     0,     3,
       1,     1,     1,     5,     3,     2,     5,     3,     1,     3,
       1,     0,     0,     7,     0,     6,     0,     6,     0,     5,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
      11,     9,    11,     9,     1,     8,     6,     5,     4,     1,
       0,     1,     6,     1,     2,     3,     2,     1,     1,     6,
       2,     4,     3,     3,     2,     1,     1,     2,     4,     3,
       1,     1,     4,     4,     3,     1,     1,     8,     7,     1,
       2,     7,     6,     5,     3,     4,     5,     1,     3,     4,
       1,     0,     3,     4,     0,     8,     0,     7,     6,     1,
       1,     2,     1,     2,     1,     1,    12,    11,     9,     5,
       0,     3,     0,     1,     1,     1,     1,     1,    12,     8,
       0,     8,     0,    10,     0,     9,     3,     3,     3,     2,
       2,     2,     1,     3,     0,     1,     2,     3,     6,     0,
       7,     0,     7,     1,     1,     1,     3,     3,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,    12,     6,     7,     5,     1,    52,   233,
     234,   195,    27,   129,     0,     0,     9,    25,   194,     8,
       0,     0,    12,    12,    12,    12,     0,    10,    12,     0,
       0,     4,     3,     0,     0,    31,     2,     0,    22,    26,
      25,     0,    68,    51,   105,   194,     0,   108,     0,     0,
      13,    14,    16,    15,   192,     0,    11,   193,     0,   226,
     227,   235,     0,     0,    30,   100,   101,   102,     0,     0,
       0,    23,    97,    24,     0,     0,     0,    20,   160,     0,
       0,   102,     0,     0,   134,     0,     0,     0,   140,    51,
      51,     0,     0,     0,     0,   194,    32,    66,    35,     0,
      37,     0,    36,    33,    34,    51,    51,    51,    51,    45,
      51,   205,   206,   207,    51,    51,     0,     0,   111,   104,
       0,     0,   193,   189,   191,     0,   238,     0,     0,    28,
     102,    82,     0,    81,     0,    80,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      27,    25,    12,     0,     0,   165,   166,     0,     0,   162,
       0,     0,     0,     0,     0,    51,    51,   140,     0,   139,
       0,    41,    42,     0,     0,     0,    69,    12,    67,    66,
       0,     0,    63,     0,     0,    43,    44,    47,    46,    48,
      49,    50,   193,     0,     0,   109,   110,   194,   107,   182,
       0,   183,   194,     0,     0,     0,     0,     0,     0,     0,
      70,    77,    71,    72,    74,    73,    75,    76,    79,    83,
      78,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    99,   128,   124,   125,   127,   126,
     123,   118,     0,   121,    20,    18,    26,    25,    12,   164,
       0,     0,   229,   231,     0,     0,    40,    39,     0,     0,
      51,    60,   143,     0,     0,     0,   103,    63,    64,    65,
      66,     0,     0,   114,     0,   141,   140,     0,   140,    66,
       0,     0,   111,   190,     0,     0,   186,     0,   181,     0,
     214,   220,   219,   221,   212,    51,    51,   116,     0,    21,
      20,    17,   177,     0,     0,     0,   169,   163,     0,     0,
      51,     0,     0,     0,    38,    51,     0,   144,     0,     0,
     150,     0,     0,     0,    67,    66,    51,     0,   112,     0,
      66,     0,    63,     0,   181,   106,   194,     0,   184,     0,
     188,   180,   237,   236,   224,   217,   216,   218,   224,     0,
     119,    51,   122,    19,     0,   168,     0,   170,     0,     0,
      59,    51,    51,    51,   200,    61,   102,   147,   146,   148,
      51,   155,     0,   154,   156,    51,    51,    56,    63,    54,
      51,     0,   140,    63,   140,     0,     0,   179,     0,     0,
     187,   225,     0,   222,     0,    29,   117,   174,   167,   178,
       0,     0,     0,     0,   136,     0,     0,   202,   157,     0,
     145,   142,   152,   153,   149,    53,    51,    62,   115,    51,
       0,     0,     0,   138,   228,     0,   185,    12,     0,    12,
     175,     0,   230,   232,   210,    51,   204,   203,     0,     0,
       0,     0,   151,    57,   113,     0,   137,     0,     0,   215,
     223,   213,   176,   173,     0,   211,   135,    51,    51,    51,
     159,    51,    51,    51,    51,     0,   172,     0,     0,   200,
     201,   198,   158,   133,     0,     0,   131,     0,   171,     0,
      51,   199,    51,    51,     0,     0,     0,   132,   130,     0,
      51,   208,     0,     0,     0,   197,     0,   210,   196,   209
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    32,     6,    15,    16,   164,    76,    38,
      40,    17,    36,   219,    63,    94,    95,    96,   191,   426,
     173,   325,   282,   192,   189,   313,   187,   179,   158,    97,
      19,    20,    46,   205,    98,   391,   337,    73,   361,   306,
      99,   252,   253,    21,   100,   101,   102,   288,   180,   289,
     103,   273,   327,   378,   104,   275,   330,   383,   379,   418,
      79,    41,   105,   351,   167,   106,   315,   316,   206,   352,
      47,   107,   108,   399,   349,   125,   296,    55,    26,   297,
     109,   417,   450,   448,   110,   111,   112,   465,   113,    27,
     358,   354,   214,   402,   403,   114,   115,   318,   319,   116,
      58,   215,   216,   117
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -360
static const yytype_int16 yypact[] =
{
       9,   182,    11,    42,  -360,  -360,     9,  -360,  -360,  -360,
    -360,  -360,    33,  -360,   225,    57,  -360,    51,    63,  -360,
      71,   391,    42,    42,    42,    42,   105,  -360,    42,   119,
     101,  -360,  -360,   135,   184,   285,  -360,    69,   146,   166,
      51,   170,  -360,   593,  -360,   192,    55,  -360,   105,   196,
    -360,  -360,  -360,  -360,  -360,    -2,  -360,    56,    71,  -360,
    -360,  -360,    71,   205,   195,  -360,  -360,   210,   314,   314,
     314,   908,   209,  -360,   215,   239,   206,   208,  -360,   115,
      87,     1,   224,   226,  -360,   227,   232,   256,   314,   593,
     593,   275,   258,   260,   263,   280,  -360,    68,  -360,   271,
    -360,   281,  -360,  -360,  -360,   593,   593,   593,   593,  -360,
     593,  -360,  -360,  -360,   593,   593,   304,    37,   288,  -360,
     285,    29,  -360,  -360,  -360,    49,  -360,   285,   285,  -360,
    -360,   284,   745,  -360,   314,  -360,   314,   314,   314,   314,
     314,   314,   314,   314,   314,   314,   314,   314,   314,   314,
     314,   314,   314,   314,   314,   314,   314,   314,   170,   157,
    -360,    51,    42,   311,   278,  -360,  -360,   294,    71,  -360,
     115,   318,   320,   306,   314,   593,   593,   314,   329,   908,
     298,  -360,  -360,   299,   341,   344,  -360,    42,   166,   323,
      69,   170,   307,   409,    38,  -360,  -360,  -360,  -360,  -360,
    -360,  -360,   342,    71,   115,  -360,  -360,   345,  -360,  -360,
      46,  -360,   346,   105,   263,   313,   315,   321,   263,    71,
    -360,   530,   296,   296,   284,   284,   284,   587,   693,   667,
     481,   432,   473,   473,   406,   406,   432,   934,   934,   934,
     934,   908,   908,   908,   170,  -360,  -360,  -360,  -360,  -360,
    -360,  -360,   104,  -360,   208,  -360,  -360,    51,    42,  -360,
      25,   331,  -360,  -360,   347,   787,  -360,  -360,   334,   360,
     593,  -360,   348,   364,   355,   371,  -360,   307,   908,  -360,
     121,   396,   363,  -360,   133,  -360,   314,   407,   314,   323,
     273,   383,   288,  -360,   285,   408,  -360,   375,   170,    45,
    -360,   285,   285,   285,  -360,   593,   593,  -360,   273,  -360,
     208,  -360,  -360,    60,   379,   263,   380,  -360,   398,   400,
     593,    71,    36,    71,  -360,   593,   319,  -360,   384,    16,
    -360,   385,   386,   388,  -360,   323,   593,   392,  -360,   393,
     323,   403,   307,    96,   170,  -360,  -360,   105,  -360,   411,
    -360,   170,  -360,  -360,   425,  -360,  -360,  -360,   425,   263,
    -360,   593,  -360,  -360,   263,  -360,   413,    74,   273,   273,
    -360,   593,   593,   593,   430,  -360,   170,   908,   348,  -360,
     593,   170,   426,   355,  -360,   593,   593,  -360,   307,  -360,
     593,   414,   314,   307,   314,   415,   416,  -360,   106,   419,
    -360,  -360,   189,  -360,   201,  -360,  -360,   420,  -360,  -360,
      60,   429,   431,   263,  -360,   263,   198,   421,  -360,   314,
    -360,  -360,   355,  -360,  -360,  -360,   593,  -360,  -360,   593,
     453,   441,   456,  -360,  -360,   423,  -360,    42,   425,    42,
      60,   263,  -360,  -360,   477,   593,  -360,  -360,   434,   437,
     263,   882,  -360,  -360,  -360,    76,  -360,    98,   486,  -360,
    -360,  -360,  -360,   455,   487,   507,  -360,   593,   593,   593,
     170,   593,   593,   593,   593,   458,    60,   314,    71,   430,
    -360,  -360,  -360,  -360,   263,   263,  -360,   498,  -360,   855,
     593,  -360,   593,   593,   285,    71,   263,  -360,  -360,   134,
     593,  -360,   508,   160,   263,  -360,   509,   477,  -360,  -360
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -360,  -360,   534,  -360,  -360,    90,  -360,  -246,  -360,   -26,
     381,   468,  -360,  -360,  -360,   390,    -3,  -360,  -360,  -360,
    -360,  -360,  -260,  -140,   264,   -14,   193,   235,  -360,    73,
    -360,  -360,   511,   255,  -360,  -360,  -360,   359,  -360,  -360,
     -33,  -186,  -307,  -360,  -360,  -360,  -360,  -360,  -150,   266,
    -360,  -360,   173,  -360,  -360,  -360,  -359,  -360,   229,    84,
     -11,  -360,    70,   -36,  -161,   148,  -284,  -360,  -360,   211,
     436,   155,   243,  -360,  -360,  -360,   265,   -45,   -19,  -360,
    -360,    80,  -360,  -360,  -360,  -360,  -360,    66,  -360,  -360,
    -360,  -360,  -116,   204,   125,   290,  -360,  -360,  -360,    12,
     543,  -360,  -360,   236
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -236
static const yytype_int16 yytable[] =
{
      18,   362,    48,   121,    74,    80,    43,   284,   309,   261,
     123,     7,   218,    33,    77,    29,    48,   332,    45,    18,
      18,    18,    18,     1,   423,    18,    34,   268,   381,   364,
     312,  -120,    45,    49,    29,    29,    29,    29,   -58,   124,
      29,   209,     8,   291,   127,    33,     8,    49,   128,   277,
     285,     9,    10,    11,    12,    13,    42,   353,   293,   186,
     382,   411,   412,   452,   363,   312,   203,    42,   126,   170,
     124,   171,   172,    22,    65,    39,   294,    66,   210,   409,
      37,    67,   395,   372,    59,   286,   124,  -235,   119,    68,
     295,    42,    22,    22,    22,    22,   211,   190,    22,    69,
     -55,    48,    42,   120,   343,    42,    70,    42,   213,   213,
      72,    14,    50,    51,    52,    53,   168,   207,    56,    78,
     165,    35,   244,   471,   212,   212,   441,   166,   427,   473,
     186,    57,    49,   431,   169,   254,   339,   307,   341,   435,
     333,    72,    72,    72,   308,   474,    54,   124,    59,   342,
     190,    23,   308,    78,   260,   280,   462,    74,    24,    18,
     245,    72,   246,   247,   248,   249,   338,   502,   299,   250,
      23,    23,    23,    23,    29,    54,    23,    24,    24,    24,
      24,   308,    60,    24,    18,   355,   356,   357,     4,   290,
     251,   287,   488,   506,    75,   388,    61,     5,  -161,    29,
     393,   124,    78,   446,   118,   305,   447,    72,   122,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,   310,    22,   170,     9,    10,   437,   438,   129,    30,
    -120,   -98,   430,   120,   432,   159,    25,    72,   439,   438,
      72,   160,   255,   162,   174,    18,   163,    22,    30,    30,
      30,    30,   177,    72,    30,    25,    25,    25,    25,   170,
      29,    25,    71,   175,   176,   347,   245,   276,   246,   247,
     248,   249,   213,   213,   213,   250,   178,   183,   184,     8,
     185,   346,   188,    28,     9,    10,    11,   186,   212,   212,
     212,   193,   398,   131,   132,   133,    49,   371,   373,   374,
      23,   194,    28,    28,    28,    28,   202,    24,    28,    65,
     204,   135,    66,   256,    65,   258,   130,    66,    22,   259,
     262,   376,   263,   135,    68,    23,   138,   139,   140,    68,
     170,   269,    24,   264,    69,   270,   271,   272,   311,    69,
     274,    70,   190,   410,   126,   281,    70,   292,   298,    72,
     301,    72,   302,   217,   217,   419,   317,   322,   303,   221,
     419,   222,   223,   224,   225,   226,   227,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,   243,   323,   320,     8,   326,   328,    30,    72,
       9,    10,    11,   329,   331,    25,    23,   300,   334,   265,
     336,   304,   245,    24,   246,   247,   248,   249,   344,   285,
     293,   250,   350,    30,    44,   278,   365,   368,   367,   369,
      25,   380,   385,   386,    18,   387,    18,   401,   422,   390,
     392,   472,   283,   135,   136,   137,   138,   139,   140,    29,
     394,    29,    28,   314,   503,   416,   146,   147,   400,   419,
     408,   429,   433,   434,   490,    72,   436,    72,   440,   135,
     136,   137,   138,   139,   140,   499,   442,    28,   443,   181,
     182,   500,   146,   147,   148,   149,   455,   449,   456,   457,
     458,   346,    72,   464,    30,   195,   196,   197,   198,   467,
     199,    25,   468,   476,   200,   201,    49,    22,   366,    22,
     135,   136,   137,   138,   139,   140,   475,   477,   135,   136,
     137,   138,   139,   140,   478,   142,   487,   459,   494,   461,
     145,   146,   147,   148,   149,   150,   396,   217,   217,   217,
      31,   505,   508,   161,   257,   335,    64,   345,    28,   279,
      72,   420,   405,   340,   482,   397,   208,   407,   384,   491,
     348,   377,   404,   460,     0,   266,   267,   135,   136,   137,
     138,   139,   140,   509,   142,   143,   144,    62,     0,   145,
     146,   147,   148,   149,   150,    23,     0,    23,     0,     0,
       0,     0,    24,     0,    24,     0,     0,     8,     0,     0,
       0,     0,     9,    10,    11,    81,   444,     0,   445,     0,
       0,    82,    83,     0,    84,    85,    86,    87,     0,    88,
      89,    90,     0,   134,   135,   136,   137,   138,   139,   140,
      91,   142,   143,   144,   463,     0,   145,   146,   147,   148,
     149,   150,     0,   469,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   451,    92,    93,     0,     0,     0,
     324,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    30,     0,    30,     0,   492,   493,     0,
      25,     0,    25,     0,     0,     0,     0,     0,     0,   501,
       0,     0,     0,     0,     0,   359,   360,   507,     0,     0,
       0,     0,     0,     0,   135,   136,   137,   138,   139,   140,
     370,   142,   489,   144,     0,   375,   145,   146,   147,   148,
     149,   150,     0,     0,     0,     0,   389,    28,     0,    28,
     135,   136,   137,   138,   139,   140,     0,     0,     0,     0,
       0,     0,   145,   146,   147,   148,   149,   150,     0,     0,
       0,   406,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   413,   414,   415,     0,     0,     0,     0,     0,     0,
     421,     0,     0,     0,     0,   424,   425,     0,   220,     0,
     428,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,     0,     0,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   453,     0,     0,   454,
     321,     0,     0,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,     0,   466,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,     0,
       0,     0,     0,     0,     0,     0,     0,   479,   480,   481,
       0,   483,   484,   485,   486,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     496,     0,   497,   498,     0,     0,     0,     0,   495,     0,
     504,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,     0,     0,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   470,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,     0,
       0,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,     0,     0,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,     0,     0,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154
};

static const yytype_int16 yycheck[] =
{
       3,   308,    21,    48,    37,    41,    20,   193,   254,   170,
      12,     0,   128,    12,    40,     3,    35,   277,    21,    22,
      23,    24,    25,    14,   383,    28,    14,   177,    12,   313,
       5,    30,    35,    21,    22,    23,    24,    25,    37,    41,
      28,    12,     4,   204,    58,    12,     4,    35,    62,   189,
      12,     9,    10,    11,    12,    13,    31,    12,    12,    34,
      44,   368,   369,   422,   310,     5,    29,    31,    12,    80,
      41,    70,    71,     3,     5,    12,    30,     8,    29,     5,
      29,    12,   342,    47,    47,    47,    41,    31,    33,    20,
      44,    31,    22,    23,    24,    25,    47,    29,    28,    30,
      32,   120,    31,    48,   290,    31,    37,    31,   127,   128,
      37,    69,    22,    23,    24,    25,    29,   120,    28,    32,
       5,    64,   158,    47,   127,   128,   410,    12,   388,    31,
      34,    12,   120,   393,    47,   161,   286,    33,   288,    33,
     280,    68,    69,    70,    48,    47,    41,    41,    47,   289,
      29,     3,    48,    32,   168,   191,   440,   190,     3,   162,
       3,    88,     5,     6,     7,     8,    33,    33,   213,    12,
      22,    23,    24,    25,   162,    41,    28,    22,    23,    24,
      25,    48,    47,    28,   187,   301,   302,   303,     6,   203,
      33,   194,   476,    33,    48,   335,    12,    15,    32,   187,
     340,    41,    32,     5,    12,   219,     8,   134,    12,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   257,   162,   244,     9,    10,    47,    48,    33,     3,
      30,    32,   392,    48,   394,    30,     3,   174,    47,    48,
     177,    12,   162,    47,    30,   258,    48,   187,    22,    23,
      24,    25,    30,   190,    28,    22,    23,    24,    25,   280,
     258,    28,    37,    47,    47,   294,     3,   187,     5,     6,
       7,     8,   301,   302,   303,    12,    30,    12,    30,     4,
      30,   294,    12,     3,     9,    10,    11,    34,   301,   302,
     303,    30,   347,    68,    69,    70,   294,   321,   322,   323,
     162,    30,    22,    23,    24,    25,    12,   162,    28,     5,
      32,    37,     8,    12,     5,    47,    12,     8,   258,    35,
      12,    12,    12,    37,    20,   187,    40,    41,    42,    20,
     351,    12,   187,    37,    30,    47,    47,     6,   258,    30,
       6,    37,    29,   367,    12,    48,    37,    12,    12,   286,
      47,   288,    47,   127,   128,   376,    35,    33,    47,   134,
     381,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,    33,    47,     4,    48,    33,   162,   326,
       9,    10,    11,    48,    33,   162,   258,   214,    12,   174,
      47,   218,     3,   258,     5,     6,     7,     8,    35,    12,
      12,    12,    47,   187,    33,   190,    47,    29,    48,    29,
     187,    47,    47,    47,   437,    47,   439,    12,    12,    47,
      47,   455,    33,    37,    38,    39,    40,    41,    42,   437,
      47,   439,   162,   260,   499,    25,    50,    51,    47,   470,
      47,    47,    47,    47,   478,   392,    47,   394,    48,    37,
      38,    39,    40,    41,    42,   494,    47,   187,    47,    89,
      90,   495,    50,    51,    52,    53,    33,    66,    47,    33,
      67,   494,   419,    16,   258,   105,   106,   107,   108,    65,
     110,   258,    65,    48,   114,   115,   494,   437,   315,   439,
      37,    38,    39,    40,    41,    42,    30,    30,    37,    38,
      39,    40,    41,    42,    17,    44,    68,   437,    30,   439,
      49,    50,    51,    52,    53,    54,   343,   301,   302,   303,
       6,    33,    33,    75,   163,   281,    35,   292,   258,   190,
     477,   378,   359,   287,   470,   344,   120,   364,   329,   479,
     295,   326,   358,   438,    -1,   175,   176,    37,    38,    39,
      40,    41,    42,   507,    44,    45,    46,    34,    -1,    49,
      50,    51,    52,    53,    54,   437,    -1,   439,    -1,    -1,
      -1,    -1,   437,    -1,   439,    -1,    -1,     4,    -1,    -1,
      -1,    -1,     9,    10,    11,    12,   413,    -1,   415,    -1,
      -1,    18,    19,    -1,    21,    22,    23,    24,    -1,    26,
      27,    28,    -1,    36,    37,    38,    39,    40,    41,    42,
      37,    44,    45,    46,   441,    -1,    49,    50,    51,    52,
      53,    54,    -1,   450,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   419,    62,    63,    -1,    -1,    -1,
     270,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   437,    -1,   439,    -1,   484,   485,    -1,
     437,    -1,   439,    -1,    -1,    -1,    -1,    -1,    -1,   496,
      -1,    -1,    -1,    -1,    -1,   305,   306,   504,    -1,    -1,
      -1,    -1,    -1,    -1,    37,    38,    39,    40,    41,    42,
     320,    44,   477,    46,    -1,   325,    49,    50,    51,    52,
      53,    54,    -1,    -1,    -1,    -1,   336,   437,    -1,   439,
      37,    38,    39,    40,    41,    42,    -1,    -1,    -1,    -1,
      -1,    -1,    49,    50,    51,    52,    53,    54,    -1,    -1,
      -1,   361,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   371,   372,   373,    -1,    -1,    -1,    -1,    -1,    -1,
     380,    -1,    -1,    -1,    -1,   385,   386,    -1,    33,    -1,
     390,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    -1,    -1,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   426,    -1,    -1,   429,
      33,    -1,    -1,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    -1,   445,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   467,   468,   469,
      -1,   471,   472,   473,   474,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     490,    -1,   492,   493,    -1,    -1,    -1,    -1,    33,    -1,
     500,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    -1,    -1,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    -1,
      -1,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    -1,    -1,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    -1,    -1,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58
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
      37,    99,   101,   109,   112,    48,    80,    81,    32,   132,
     135,    12,    18,    19,    21,    22,    23,    24,    26,    27,
      28,    37,    62,    63,    87,    88,    89,   101,   106,   112,
     116,   117,   118,   122,   126,   134,   137,   143,   144,   152,
     156,   157,   158,   160,   167,   168,   171,   175,    12,    33,
      48,   149,    12,    12,    41,   147,    12,    97,    97,    33,
      12,    99,    99,    99,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,   100,    30,
      12,    83,    47,    48,    79,     5,    12,   136,    29,    47,
     132,    70,    71,    92,    30,    47,    47,    30,    30,    99,
     120,    87,    87,    12,    30,    30,    34,    98,    12,    96,
      29,    90,    95,    30,    30,    87,    87,    87,    87,    87,
      87,    87,    12,    29,    32,   105,   140,    88,   142,    12,
      29,    47,    88,   150,   164,   173,   174,   175,   164,    85,
      33,    99,    99,    99,    99,    99,    99,    99,    99,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,    99,
      99,    99,    99,    99,   135,     3,     5,     6,     7,     8,
      12,    33,   113,   114,    81,    77,    12,    82,    47,    35,
      97,   136,    12,    12,    37,    99,    87,    87,   120,    12,
      47,    47,     6,   123,     6,   127,    77,    95,    99,   109,
     135,    48,    94,    33,   113,    12,    47,    88,   119,   121,
      97,   136,    12,    12,    30,    44,   148,   151,    12,   149,
      98,    47,    47,    47,    98,    97,   111,    33,    48,    79,
      81,    77,     5,    97,    98,   138,   139,    35,   169,   170,
      47,    33,    33,    33,    87,    93,    48,   124,    33,    48,
     128,    33,    94,    95,    12,    96,    47,   108,    33,   120,
     121,   120,    95,   113,    35,   105,    88,   150,   148,   146,
      47,   135,   141,    12,   163,   164,   164,   164,   162,    87,
      87,   110,   114,    79,   138,    47,    98,    48,    29,    29,
      87,    97,    47,    97,    97,    87,    12,    99,   125,   130,
      47,    12,    44,   129,   130,    47,    47,    47,    95,    87,
      47,   107,    47,    95,    47,    94,    98,   141,   149,   145,
      47,    12,   165,   166,   165,    98,    87,    98,    47,     5,
      97,   114,   114,    87,    87,    87,    25,   153,   131,   132,
     124,    87,    12,   128,    87,    87,    91,    94,    87,    47,
     120,    94,   120,    47,    47,    33,    47,    47,    48,    47,
      48,   138,    47,    47,    98,    98,     5,     8,   155,    66,
     154,    99,   128,    87,    87,    33,    47,    33,    67,    77,
     166,    77,   138,    98,    16,   159,    87,    65,    65,    98,
      35,    47,    97,    31,    47,    30,    48,    30,    17,    87,
      87,    87,   131,    87,    87,    87,    87,    68,   138,    99,
      97,   153,    98,    98,    30,    33,    87,    87,    87,   150,
      97,    98,    33,   149,    87,    33,    33,    98,    33,   159
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
#line 442 ".\\semanticAnalysis.y"
    {printf("\n\nSyntax is Correct\n");return;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 454 ".\\semanticAnalysis.y"
    {
    if(strcmp(forFunc->dataType,"void")==0){
        char const errorMessage[100]="Void Function Does not return anything";
        int a=yyerror(errorMessage);
        return -1;
    }
}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 462 ".\\semanticAnalysis.y"
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

  case 27:

/* Line 1455 of yacc.c  */
#line 473 ".\\semanticAnalysis.y"
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

  case 28:

/* Line 1455 of yacc.c  */
#line 485 ".\\semanticAnalysis.y"
    {noOfParameters=0;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 494 ".\\semanticAnalysis.y"
    {
            strcpy(typeBuffer,(yyvsp[(1) - (1)].type));
            (yyval.type)=malloc(strlen((yyvsp[(1) - (1)].type))+1);
            strcpy((yyval.type),(yyvsp[(1) - (1)].type));
        }
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 501 ".\\semanticAnalysis.y"
    {dimit = 0;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 501 ".\\semanticAnalysis.y"
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

  case 58:

/* Line 1455 of yacc.c  */
#line 520 ".\\semanticAnalysis.y"
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

  case 60:

/* Line 1455 of yacc.c  */
#line 531 ".\\semanticAnalysis.y"
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

  case 65:

/* Line 1455 of yacc.c  */
#line 544 ".\\semanticAnalysis.y"
    {
    if(strcmp(forFunc->dataType,"void")==0){
        char const errorMessage[100]="Void Function Does not return anything";
        int a=yyerror(errorMessage);
        return -1;
    }
}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 552 ".\\semanticAnalysis.y"
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

  case 68:

/* Line 1455 of yacc.c  */
#line 564 ".\\semanticAnalysis.y"
    {scope++;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 565 ".\\semanticAnalysis.y"
    {deleteDMT(scope);scope--;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 594 ".\\semanticAnalysis.y"
    {dimit = 0;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 595 ".\\semanticAnalysis.y"
    {dimit = 0;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 598 ".\\semanticAnalysis.y"
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

  case 104:

/* Line 1455 of yacc.c  */
#line 612 ".\\semanticAnalysis.y"
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

  case 105:

/* Line 1455 of yacc.c  */
#line 623 ".\\semanticAnalysis.y"
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

  case 106:

/* Line 1455 of yacc.c  */
#line 634 ".\\semanticAnalysis.y"
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

  case 107:

/* Line 1455 of yacc.c  */
#line 667 ".\\semanticAnalysis.y"
    {
                    struct SymbolTableEntry*new_entry = insertIdentifier(ptrBuf,CLASS[3],(yyvsp[(3) - (3)].type),pointerLen,yylinenumber,scope+1);
                    PD[noOfParameters]=pointerLen;
                    strcpy(PL[noOfParameters],(yyvsp[(3) - (3)].type));
                    PTL[noOfParameters]='p';
                    noOfParameters++;
                }
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 674 ".\\semanticAnalysis.y"
    {
                    struct SymbolTableEntry*new_entry = insertIdentifier(ptrBuf,CLASS[3],(yyvsp[(1) - (1)].type),pointerLen,yylinenumber,scope+1);
                    PD[noOfParameters]=pointerLen;
                    strcpy(PL[noOfParameters],(yyvsp[(1) - (1)].type));
                    PTL[noOfParameters]='p';
                    noOfParameters++;
                    pointerLen=1;
                }
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 682 ".\\semanticAnalysis.y"
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

  case 110:

/* Line 1455 of yacc.c  */
#line 702 ".\\semanticAnalysis.y"
    {
    (yyval.type)=malloc(strlen("array")+1);strcpy((yyval.type),"array");

    }
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 705 ".\\semanticAnalysis.y"
    {(yyval.type)=malloc(strlen("variable")+1);strcpy((yyval.type),"variable");}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 708 ".\\semanticAnalysis.y"
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

  case 114:

/* Line 1455 of yacc.c  */
#line 743 ".\\semanticAnalysis.y"
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

  case 116:

/* Line 1455 of yacc.c  */
#line 791 ".\\semanticAnalysis.y"
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
#line 826 ".\\semanticAnalysis.y"
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
#line 872 ".\\semanticAnalysis.y"
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

  case 121:

/* Line 1455 of yacc.c  */
#line 889 ".\\semanticAnalysis.y"
    {
    strcpy(PL[noOfParameters],(yyvsp[(1) - (1)].type));
    PTL[noOfParameters]=pt;
    noOfParameters++;
}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 894 ".\\semanticAnalysis.y"
    {
            strcpy(PL[noOfParameters],(yyvsp[(3) - (3)].type));
            PTL[noOfParameters]=pt;
            noOfParameters++;
        }
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 899 ".\\semanticAnalysis.y"
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

  case 124:

/* Line 1455 of yacc.c  */
#line 927 ".\\semanticAnalysis.y"
    {(yyval.type)=malloc(strlen((yyvsp[(1) - (1)].type))+1);strcpy((yyval.type),(yyvsp[(1) - (1)].type));pt='v';parD[parDi++]=0;}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 928 ".\\semanticAnalysis.y"
    {(yyval.type)=malloc(strlen((yyvsp[(1) - (1)].type))+1);strcpy((yyval.type),(yyvsp[(1) - (1)].type));pt='v';parD[parDi++]=0;}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 929 ".\\semanticAnalysis.y"
    {(yyval.type)=malloc(strlen((yyvsp[(1) - (1)].type))+1);strcpy((yyval.type),(yyvsp[(1) - (1)].type));pt='v';parD[parDi++]=0;}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 930 ".\\semanticAnalysis.y"
    {(yyval.type)=malloc(strlen((yyvsp[(1) - (1)].type))+1);strcpy((yyval.type),(yyvsp[(1) - (1)].type));pt='v';parD[parDi++]=0;}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 933 ".\\semanticAnalysis.y"
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

  case 134:

/* Line 1455 of yacc.c  */
#line 971 ".\\semanticAnalysis.y"
    {scope++;}
    break;

  case 141:

/* Line 1455 of yacc.c  */
#line 981 ".\\semanticAnalysis.y"
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
#line 1011 ".\\semanticAnalysis.y"
    {ID_dim++;}
    break;

  case 161:

/* Line 1455 of yacc.c  */
#line 1013 ".\\semanticAnalysis.y"
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

  case 162:

/* Line 1455 of yacc.c  */
#line 1027 ".\\semanticAnalysis.y"
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

  case 165:

/* Line 1455 of yacc.c  */
#line 1038 ".\\semanticAnalysis.y"
    {dimbuffer[dimit++] = intval;}
    break;

  case 166:

/* Line 1455 of yacc.c  */
#line 1038 ".\\semanticAnalysis.y"
    {dimbuffer[dimit++] = 10000;}
    break;

  case 182:

/* Line 1455 of yacc.c  */
#line 1053 ".\\semanticAnalysis.y"
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

  case 184:

/* Line 1455 of yacc.c  */
#line 1069 ".\\semanticAnalysis.y"
    {if(strcmp((yyvsp[(3) - (6)].type),(yyvsp[(6) - (6)].type))!=0){
    char message[30]="Variable Types dont Match";
        int res=yyerror(message);
        return -1;}}
    break;

  case 186:

/* Line 1455 of yacc.c  */
#line 1072 ".\\semanticAnalysis.y"
    {if(strcmp((yyvsp[(3) - (5)].type),(yyvsp[(5) - (5)].type))!=0){
    char message[30]="Variable Types dont Match";
        int res=yyerror(message);
        return -1;
}}
    break;

  case 189:

/* Line 1455 of yacc.c  */
#line 1078 ".\\semanticAnalysis.y"
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

  case 190:

/* Line 1455 of yacc.c  */
#line 1092 ".\\semanticAnalysis.y"
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

  case 191:

/* Line 1455 of yacc.c  */
#line 1104 ".\\semanticAnalysis.y"
    {  
     pointerLen++;
}
    break;

  case 212:

/* Line 1455 of yacc.c  */
#line 1122 ".\\semanticAnalysis.y"
    {
        struct SymbolTableEntry*new_entry=insertIdentifier(userTypeNameBuffer,CLASS[4],userTypeBuffer,userTypeDim,yylinenumber,scope);
        userTypeDim = 0;
    }
    break;

  case 214:

/* Line 1455 of yacc.c  */
#line 1127 ".\\semanticAnalysis.y"
    {
        struct SymbolTableEntry*new_entry=insertIdentifier(userTypeNameBuffer,CLASS[4],userTypeBuffer,userTypeDim,yylinenumber,scope);
        userTypeDim = 0;
                }
    break;

  case 225:

/* Line 1455 of yacc.c  */
#line 1142 ".\\semanticAnalysis.y"
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

  case 229:

/* Line 1455 of yacc.c  */
#line 1157 ".\\semanticAnalysis.y"
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

  case 231:

/* Line 1455 of yacc.c  */
#line 1179 ".\\semanticAnalysis.y"
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

  case 233:

/* Line 1455 of yacc.c  */
#line 1202 ".\\semanticAnalysis.y"
    {
            strcpy(userTypeBuffer,(yyvsp[(1) - (1)].type));
            (yyval.type)=malloc(strlen((yyvsp[(1) - (1)].type))+1);
            strcpy((yyval.type),(yyvsp[(1) - (1)].type));
        }
    break;

  case 234:

/* Line 1455 of yacc.c  */
#line 1207 ".\\semanticAnalysis.y"
    {
            strcpy(userTypeBuffer,(yyvsp[(1) - (1)].type));
            (yyval.type)=malloc(strlen((yyvsp[(1) - (1)].type))+1);
            strcpy((yyval.type),(yyvsp[(1) - (1)].type));
        }
    break;

  case 235:

/* Line 1455 of yacc.c  */
#line 1213 ".\\semanticAnalysis.y"
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

  case 236:

/* Line 1455 of yacc.c  */
#line 1224 ".\\semanticAnalysis.y"
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

  case 237:

/* Line 1455 of yacc.c  */
#line 1240 ".\\semanticAnalysis.y"
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

  case 238:

/* Line 1455 of yacc.c  */
#line 1260 ".\\semanticAnalysis.y"
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
#line 3510 "y.tab.c"
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
#line 1283 ".\\semanticAnalysis.y"


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
