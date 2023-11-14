
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
#define YYLAST   914

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  72
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  103
/* YYNRULES -- Number of rules.  */
#define YYNRULES  237
/* YYNRULES -- Number of states.  */
#define YYNSTATES  509

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
      58,    59,    64,    65,    68,    71,    72,    74,    76,    83,
      85,    86,    88,    90,    92,    94,    96,    98,   103,   107,
     111,   114,   117,   120,   123,   125,   128,   131,   134,   137,
     140,   141,   143,   150,   156,   157,   158,   166,   167,   173,
     174,   180,   185,   186,   189,   192,   193,   195,   197,   199,
     203,   207,   211,   215,   219,   223,   227,   231,   235,   239,
     242,   245,   248,   252,   256,   260,   264,   268,   272,   276,
     280,   284,   288,   292,   296,   300,   304,   306,   307,   311,
     313,   315,   317,   323,   327,   330,   336,   340,   342,   346,
     348,   349,   350,   358,   359,   366,   367,   374,   375,   381,
     383,   385,   389,   391,   393,   395,   397,   399,   401,   403,
     415,   425,   437,   447,   449,   458,   465,   471,   476,   478,
     479,   481,   488,   490,   493,   497,   500,   502,   504,   511,
     514,   519,   523,   527,   530,   532,   534,   537,   542,   546,
     548,   550,   555,   560,   564,   566,   568,   577,   585,   587,
     590,   598,   605,   611,   615,   620,   626,   628,   632,   637,
     639,   640,   644,   649,   650,   659,   660,   668,   675,   677,
     679,   682,   684,   687,   689,   691,   704,   716,   726,   732,
     733,   737,   738,   740,   742,   744,   746,   748,   761,   770,
     771,   780,   781,   792,   793,   803,   807,   811,   815,   818,
     821,   824,   826,   830,   831,   833,   836,   840,   847,   848,
     856,   857,   865,   867,   869,   871,   875,   879
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      73,     0,    -1,    74,    77,    84,    -1,    14,    76,    75,
      -1,    74,    -1,    -1,     6,    -1,    15,    -1,   101,    -1,
      78,    -1,   160,    -1,   166,    77,    -1,    -1,   133,    77,
      -1,   136,    77,    -1,   143,    77,    -1,   142,    77,    -1,
      87,    82,    81,    79,    47,    77,    -1,    83,    81,    80,
      47,    77,    -1,    48,    82,    81,    79,    -1,    -1,    48,
      83,    81,    79,    -1,    -1,    29,    98,    -1,    29,   108,
      -1,    -1,    12,    -1,    12,    -1,    64,    85,    33,    96,
      86,    97,    -1,   103,    -1,    -1,    88,    -1,   121,    -1,
     125,    -1,   105,    -1,   117,    -1,   115,    -1,    26,   119,
      47,    86,    -1,    22,    47,    86,    -1,    19,    47,    86,
      -1,    27,    86,    -1,    28,    86,    -1,   133,    86,    -1,
     136,    86,    -1,   151,    -1,   143,    86,    -1,   142,    86,
      -1,   155,    86,    -1,   166,    86,    -1,   167,    86,    -1,
      -1,     4,    -1,    87,    95,    94,    93,    47,    86,    -1,
     100,    94,    93,    47,    86,    -1,    -1,    -1,   100,    89,
     134,    94,    47,    90,    86,    -1,    -1,    12,    91,    37,
      47,    86,    -1,    -1,    37,    12,    47,    92,    86,    -1,
      48,    95,    94,    93,    -1,    -1,    29,    98,    -1,    29,
     108,    -1,    -1,    12,    -1,    31,    -1,    34,    -1,    30,
      98,    33,    -1,    98,    38,    98,    -1,    98,    39,    98,
      -1,    98,    41,    98,    -1,    98,    40,    98,    -1,    98,
      42,    98,    -1,    98,    43,    98,    -1,    98,    36,    98,
      -1,    98,    46,    98,    -1,    98,    44,    98,    -1,    98,
      37,    -1,    37,    98,    -1,    20,    98,    -1,    98,    45,
      98,    -1,    98,    49,    98,    -1,    98,    50,    98,    -1,
      98,    51,    98,    -1,    98,    52,    98,    -1,    98,    53,
      98,    -1,    98,    54,    98,    -1,    98,    55,    98,    -1,
      98,    56,    98,    -1,    98,    57,    98,    -1,    98,    58,
      98,    -1,    98,    59,    98,    -1,    98,    60,    98,    -1,
      98,    61,    98,    -1,   100,    -1,    -1,   100,    99,   134,
      -1,     5,    -1,     8,    -1,    12,    -1,   102,    96,    86,
      97,    77,    -1,   114,   103,    33,    -1,   114,    33,    -1,
     103,    48,    87,    12,   104,    -1,   103,    48,   141,    -1,
     141,    -1,    87,    12,   104,    -1,   139,    -1,    -1,    -1,
     111,    30,   112,    33,   106,    47,    86,    -1,    -1,   111,
      30,    33,   107,    47,    86,    -1,    -1,   111,    30,   112,
      33,   109,    86,    -1,    -1,   111,    30,    33,   110,    86,
      -1,    12,    -1,   113,    -1,   112,    48,   113,    -1,    12,
      -1,     5,    -1,     6,    -1,     8,    -1,     7,    -1,     3,
      -1,    13,    -1,   116,    30,   118,   119,    47,   119,    33,
      31,    86,    97,    86,    -1,   116,    30,   118,   119,    47,
     119,    33,    47,    86,    -1,   116,    30,    47,   119,    47,
     119,    33,    96,    86,    97,    86,    -1,   116,    30,    47,
     119,    47,   119,    33,    47,    86,    -1,    21,    -1,    23,
      30,   119,    33,    96,    86,    97,    86,    -1,    23,    30,
     119,    33,    47,    86,    -1,    87,   120,    94,    93,    47,
      -1,   120,    94,    93,    47,    -1,    98,    -1,    -1,    12,
      -1,    62,    30,   122,    33,    47,    86,    -1,     6,    -1,
       6,   123,    -1,    48,   124,   123,    -1,    48,   124,    -1,
      98,    -1,   129,    -1,    63,    30,   126,    33,    47,    86,
      -1,     6,   127,    -1,    48,    44,    12,   127,    -1,    48,
      44,    12,    -1,    48,   128,   127,    -1,    48,   128,    -1,
      12,    -1,   129,    -1,    12,   130,    -1,   131,    98,    35,
     130,    -1,   131,    98,    35,    -1,    32,    -1,    12,    -1,
      87,   132,   134,    47,    -1,   134,   131,   135,    35,    -1,
     131,   135,    35,    -1,     5,    -1,    12,    -1,    87,   132,
     134,    29,    96,   137,    97,    47,    -1,    87,   132,   134,
      29,    96,    97,    47,    -1,   138,    -1,   138,    48,    -1,
     138,    48,    96,   137,    97,    48,   137,    -1,   138,    48,
      96,   137,    97,    48,    -1,   138,    48,    96,   137,    97,
      -1,    96,   137,    97,    -1,    96,   137,    97,    48,    -1,
      96,   137,    97,    48,   137,    -1,     5,    -1,   138,    48,
       5,    -1,    32,   135,    35,   140,    -1,   134,    -1,    -1,
     149,   148,    12,    -1,   149,   148,   146,    47,    -1,    -1,
     149,   148,   146,    29,    44,   147,   144,    47,    -1,    -1,
     149,   148,   146,    29,   147,   145,    47,    -1,   149,   148,
     146,    29,   150,    47,    -1,    12,    -1,    12,    -1,   148,
      41,    -1,    41,    -1,   170,    12,    -1,    87,    -1,    11,
      -1,    30,   149,   148,    33,    67,    30,    68,    30,   149,
     148,    33,    33,    -1,    30,   149,   148,    33,    67,    30,
      68,    30,   149,    33,    33,    -1,    24,    30,    12,    33,
      96,   152,   153,    97,    86,    -1,    25,   154,    65,    86,
     152,    -1,    -1,    66,    65,    86,    -1,    -1,     8,    -1,
       5,    -1,   156,    -1,   157,    -1,   159,    -1,    18,    30,
      98,    33,    96,    86,    97,   158,    17,    96,    86,    97,
      -1,    16,    30,    98,    33,    96,    86,    97,   158,    -1,
      -1,    18,    30,    98,    33,    96,    86,    97,   158,    -1,
      -1,    69,   170,   171,    96,   163,    97,   161,   164,    47,
      77,    -1,    -1,   170,   171,    96,   163,    97,   162,   164,
      47,    77,    -1,   173,    47,   163,    -1,   172,    47,   163,
      -1,   174,    47,   163,    -1,   173,    47,    -1,   172,    47,
      -1,   174,    47,    -1,   165,    -1,   164,    48,   165,    -1,
      -1,    12,    -1,   174,    47,    -1,    12,    12,    47,    -1,
     174,    29,    96,   112,    97,    47,    -1,    -1,    12,    70,
      12,   168,    29,   113,    47,    -1,    -1,    12,    71,    12,
     169,    29,   113,    47,    -1,     9,    -1,    10,    -1,    12,
      -1,   149,   148,    12,    -1,    87,    12,   140,    -1,   170,
      12,    12,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   442,   442,   443,   444,   444,   445,   445,   447,   447,
     447,   447,   447,   448,   448,   448,   448,   450,   451,   452,
     452,   453,   453,   454,   454,   460,   462,   473,   485,   486,
     486,   488,   488,   488,   488,   488,   488,   489,   489,   489,
     490,   490,   490,   490,   491,   491,   491,   491,   492,   492,
     492,   494,   499,   500,   501,   501,   501,   520,   520,   531,
     531,   543,   543,   544,   544,   550,   552,   564,   565,   567,
     568,   569,   570,   571,   572,   573,   574,   575,   576,   577,
     578,   579,   580,   581,   582,   583,   584,   585,   586,   587,
     588,   589,   590,   591,   592,   593,   594,   595,   595,   596,
     596,   598,   611,   612,   623,   634,   667,   674,   681,   701,
     704,   707,   707,   742,   742,   790,   790,   825,   825,   871,
     888,   893,   898,   926,   927,   928,   929,   930,   932,   965,
     966,   967,   968,   970,   972,   973,   975,   976,   978,   978,
     980,   992,   993,   994,   995,   996,   997,   997,   999,  1000,
    1001,  1002,  1003,  1004,  1005,  1005,  1007,  1008,  1008,  1010,
    1012,  1025,  1035,  1035,  1037,  1037,  1038,  1038,  1039,  1040,
    1041,  1042,  1043,  1044,  1045,  1046,  1047,  1047,  1049,  1050,
    1050,  1052,  1067,  1068,  1068,  1071,  1071,  1075,  1077,  1091,
    1103,  1105,  1106,  1106,  1106,  1107,  1108,  1110,  1111,  1111,
    1112,  1112,  1113,  1113,  1115,  1116,  1116,  1117,  1118,  1118,
    1119,  1121,  1121,  1126,  1125,  1131,  1132,  1133,  1134,  1135,
    1136,  1139,  1139,  1139,  1141,  1154,  1154,  1155,  1156,  1156,
    1177,  1177,  1199,  1204,  1210,  1221,  1236,  1256
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
  "optionsG", "idgi", "idgl", "main", "mainParameters", "start1", "type",
  "varDec", "$@1", "$@2", "$@3", "$@4", "D", "options", "id",
  "open_flower", "close_flower", "Exp", "$@5", "id3", "function_defn",
  "function_declaration", "parameter_list", "choice", "function_call",
  "$@6", "$@7", "function_call1", "$@8", "$@9", "funName", "params",
  "item", "fun_start", "for", "forScope", "while", "varDecF", "ExpF",
  "idFor", "print", "printExpr", "printArguments", "printContent", "scanf",
  "scanfExpr", "scanfArguments", "scanfContent", "arrayElement",
  "dimension", "open_sq", "ID2", "arrayDeclr", "BOX", "integer_dim",
  "arrayInitial", "BALANCED_BRACK", "arrayParams_unend",
  "arrayAsAParameter", "higherDimention", "pointerAsAParameter",
  "PTR_DECLR", "PTR_INITIAL", "$@10", "$@11", "idinsert", "idlook",
  "PTR_STAR", "PTR_TYPE", "PTR_EXP", "switch", "switchcase", "default",
  "comp", "ifElseLadder", "S", "matched", "elif", "unmatched",
  "userTypeDefination", "$@12", "$@13", "userTypeParams", "userTypeObj",
  "uIDi", "userTypeDeclaration", "userTypeInitialization", "$@14", "$@15",
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
      79,    80,    80,    81,    81,    81,    82,    83,    84,    85,
      85,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    87,    88,    88,    89,    90,    88,    91,    88,    92,
      88,    93,    93,    94,    94,    94,    95,    96,    97,    98,
      98,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    98,    98,    98,    98,    98,    98,    99,    98,    98,
      98,   100,   101,   102,   102,   103,   103,   103,   103,   104,
     104,   106,   105,   107,   105,   109,   108,   110,   108,   111,
     112,   112,   113,   113,   113,   113,   113,   113,   114,   115,
     115,   115,   115,   116,   117,   117,   118,   118,   119,   119,
     120,   121,   122,   122,   123,   123,   124,   124,   125,   126,
     127,   127,   127,   127,   128,   128,   129,   130,   130,   131,
     132,   133,   134,   134,   135,   135,   136,   136,   137,   137,
     137,   137,   137,   137,   137,   137,   138,   138,   139,   140,
     140,   141,   142,   144,   143,   145,   143,   143,   146,   147,
     148,   148,   149,   149,   149,   150,   150,   151,   152,   152,
     153,   153,   154,   154,   155,   156,   156,   157,   158,   158,
     159,   161,   160,   162,   160,   163,   163,   163,   163,   163,
     163,   164,   164,   164,   165,   166,   166,   167,   168,   167,
     169,   167,   170,   170,   171,   172,   173,   174
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     3,     1,     0,     1,     1,     1,     1,
       1,     2,     0,     2,     2,     2,     2,     6,     5,     4,
       0,     4,     0,     2,     2,     0,     1,     1,     6,     1,
       0,     1,     1,     1,     1,     1,     1,     4,     3,     3,
       2,     2,     2,     2,     1,     2,     2,     2,     2,     2,
       0,     1,     6,     5,     0,     0,     7,     0,     5,     0,
       5,     4,     0,     2,     2,     0,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     1,     0,     3,     1,
       1,     1,     5,     3,     2,     5,     3,     1,     3,     1,
       0,     0,     7,     0,     6,     0,     6,     0,     5,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,    11,
       9,    11,     9,     1,     8,     6,     5,     4,     1,     0,
       1,     6,     1,     2,     3,     2,     1,     1,     6,     2,
       4,     3,     3,     2,     1,     1,     2,     4,     3,     1,
       1,     4,     4,     3,     1,     1,     8,     7,     1,     2,
       7,     6,     5,     3,     4,     5,     1,     3,     4,     1,
       0,     3,     4,     0,     8,     0,     7,     6,     1,     1,
       2,     1,     2,     1,     1,    12,    11,     9,     5,     0,
       3,     0,     1,     1,     1,     1,     1,    12,     8,     0,
       8,     0,    10,     0,     9,     3,     3,     3,     2,     2,
       2,     1,     3,     0,     1,     2,     3,     6,     0,     7,
       0,     7,     1,     1,     1,     3,     3,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,    12,     6,     7,     5,     1,    51,   232,
     233,   194,    27,   128,     0,     0,     9,    25,   193,     8,
       0,     0,    12,    12,    12,    12,     0,    10,    12,     0,
       0,     4,     3,     0,     0,    30,     2,     0,    22,    26,
      25,     0,    67,    50,   104,   193,     0,   107,     0,     0,
      13,    14,    16,    15,   191,     0,    11,   192,     0,   225,
     226,   234,     0,     0,    29,    99,   100,   101,     0,     0,
       0,    23,    96,    24,     0,     0,     0,    20,   159,     0,
       0,   101,     0,     0,   133,     0,     0,     0,   139,    50,
      50,     0,     0,     0,     0,   193,    31,    65,    34,     0,
      36,     0,    35,    32,    33,    50,    50,    50,    50,    44,
      50,   204,   205,   206,    50,    50,     0,     0,   110,   103,
       0,     0,   192,   188,   190,     0,   237,     0,     0,     0,
     101,    81,     0,    80,     0,    79,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      27,    25,    12,     0,     0,   164,   165,     0,     0,   161,
       0,     0,     0,     0,     0,    50,    50,   139,     0,   138,
       0,    40,    41,     0,     0,     0,    68,    12,    66,    65,
       0,     0,    62,     0,     0,    42,    43,    46,    45,    47,
      48,    49,   192,     0,     0,   108,   109,   193,   106,   181,
       0,   182,   193,     0,     0,     0,     0,     0,     0,    50,
      69,    76,    70,    71,    73,    72,    74,    75,    78,    82,
      77,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    98,   127,   123,   124,   126,   125,
     122,   117,     0,   120,    20,    18,    26,    25,    12,   163,
       0,     0,   228,   230,     0,     0,    39,    38,     0,     0,
      50,    59,   142,     0,     0,     0,   102,    62,    63,    64,
      65,     0,     0,   113,     0,   140,   139,     0,   139,    65,
       0,     0,   110,   189,     0,     0,   185,     0,   180,     0,
     213,   219,   218,   220,   211,     0,    50,   115,     0,    21,
      20,    17,   176,     0,     0,     0,   168,   162,     0,     0,
      50,     0,     0,     0,    37,    50,     0,   143,     0,     0,
     149,     0,     0,     0,    66,    65,    50,     0,   111,     0,
      65,     0,    62,     0,   180,   105,   193,     0,   183,     0,
     187,   179,   236,   235,   223,   216,   215,   217,   223,    28,
     118,    50,   121,    19,     0,   167,     0,   169,     0,     0,
      58,    50,    50,    50,   199,    60,   101,   146,   145,   147,
      50,   154,     0,   153,   155,    50,    50,    55,    62,    53,
      50,     0,   139,    62,   139,     0,     0,   178,     0,     0,
     186,   224,     0,   221,     0,   116,   173,   166,   177,     0,
       0,     0,     0,   135,     0,     0,   201,   156,     0,   144,
     141,   151,   152,   148,    52,    50,    61,   114,    50,     0,
       0,     0,   137,   227,     0,   184,    12,     0,    12,   174,
       0,   229,   231,   209,    50,   203,   202,     0,     0,     0,
       0,   150,    56,   112,     0,   136,     0,     0,   214,   222,
     212,   175,   172,     0,   210,   134,    50,    50,    50,   158,
      50,    50,    50,    50,     0,   171,     0,     0,   199,   200,
     197,   157,   132,     0,     0,   130,     0,   170,     0,    50,
     198,    50,    50,     0,     0,     0,   131,   129,     0,    50,
     207,     0,     0,     0,   196,     0,   209,   195,   208
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    32,     6,    15,    16,   164,    76,    38,
      40,    17,    36,    63,    94,    95,    96,   191,   425,   173,
     325,   282,   192,   189,   313,   187,   179,   158,    97,    19,
      20,    46,   205,    98,   391,   337,    73,   361,   306,    99,
     252,   253,    21,   100,   101,   102,   288,   180,   289,   103,
     273,   327,   378,   104,   275,   330,   383,   379,   417,    79,
      41,   105,   351,   167,   106,   315,   316,   206,   352,    47,
     107,   108,   399,   349,   125,   296,    55,    26,   297,   109,
     416,   449,   447,   110,   111,   112,   464,   113,    27,   358,
     354,   214,   402,   403,   114,   115,   318,   319,   116,    58,
     215,   216,   117
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -373
static const yytype_int16 yypact[] =
{
      -2,    71,    14,    41,  -373,  -373,    -2,  -373,  -373,  -373,
    -373,  -373,    17,  -373,   237,   -33,  -373,    45,    85,  -373,
      52,   161,    41,    41,    41,    41,    61,  -373,    41,   174,
     119,  -373,  -373,   149,   186,   285,  -373,   273,   155,   199,
      45,   204,  -373,   503,  -373,   241,    83,  -373,    61,   259,
    -373,  -373,  -373,  -373,  -373,    16,  -373,    -4,    52,  -373,
    -373,  -373,    52,   239,   228,  -373,  -373,   244,   366,   366,
     366,   807,   248,  -373,   257,   276,   243,   264,  -373,   107,
      44,    29,   262,   258,  -373,   267,   292,   294,   366,   503,
     503,   337,   320,   322,   317,   343,  -373,   151,  -373,   327,
    -373,   329,  -373,  -373,  -373,   503,   503,   503,   503,  -373,
     503,  -373,  -373,  -373,   503,   503,   352,    82,   340,  -373,
     285,    43,  -373,  -373,  -373,   106,  -373,   285,   285,    52,
    -373,   332,   574,  -373,   366,  -373,   366,   366,   366,   366,
     366,   366,   366,   366,   366,   366,   366,   366,   366,   366,
     366,   366,   366,   366,   366,   366,   366,   366,   204,   431,
    -373,    45,    41,   361,   330,  -373,  -373,   345,    52,  -373,
     107,   373,   375,   353,   366,   503,   503,   366,   377,   807,
     346,  -373,  -373,   348,   386,   393,  -373,    41,   199,   378,
     273,   204,   356,   439,    34,  -373,  -373,  -373,  -373,  -373,
    -373,  -373,   388,    52,   107,  -373,  -373,   398,  -373,  -373,
      48,  -373,   399,    61,   317,   365,   368,   369,   317,   503,
    -373,   605,   321,   321,   332,   332,   332,   543,   855,   760,
     631,   861,   279,   279,   696,   696,   861,   833,   833,   833,
     833,   807,   807,   807,   204,  -373,  -373,  -373,  -373,  -373,
    -373,  -373,   140,  -373,   264,  -373,  -373,    45,    41,  -373,
      51,   382,  -373,  -373,   381,   671,  -373,  -373,   385,   387,
     503,  -373,   384,   392,   401,   396,  -373,   356,   807,  -373,
     153,   429,   405,  -373,   142,  -373,   366,   442,   366,   378,
     232,   420,   340,  -373,   285,   444,  -373,   410,   204,    53,
    -373,   285,   285,   285,  -373,   317,   503,  -373,   232,  -373,
     264,  -373,  -373,    64,   411,   317,   413,  -373,   430,   436,
     503,    52,    49,    52,  -373,   503,   371,  -373,   419,    31,
    -373,   421,   423,   424,  -373,   378,   503,   426,  -373,   432,
     378,   434,   356,   109,   204,  -373,  -373,    61,  -373,   435,
    -373,   204,  -373,  -373,   464,  -373,  -373,  -373,   464,  -373,
    -373,   503,  -373,  -373,   317,  -373,   438,    67,   232,   232,
    -373,   503,   503,   503,   453,  -373,   204,   807,   384,  -373,
     503,   204,   471,   401,  -373,   503,   503,  -373,   356,  -373,
     503,   440,   366,   356,   366,   441,   446,  -373,    81,   447,
    -373,  -373,   209,  -373,   219,  -373,   448,  -373,  -373,    64,
     450,   452,   317,  -373,   317,   192,   443,  -373,   366,  -373,
    -373,   401,  -373,  -373,  -373,   503,  -373,  -373,   503,   456,
     459,   467,  -373,  -373,   449,  -373,    41,   464,    41,    64,
     317,  -373,  -373,   492,   503,  -373,  -373,   445,   454,   317,
     781,  -373,  -373,  -373,    76,  -373,   113,   481,  -373,  -373,
    -373,  -373,   470,   490,   506,  -373,   503,   503,   503,   204,
     503,   503,   503,   503,   460,    64,   366,    52,   453,  -373,
    -373,  -373,  -373,   317,   317,  -373,   502,  -373,   712,   503,
    -373,   503,   503,   285,    52,   317,  -373,  -373,   154,   503,
    -373,   500,   200,   317,  -373,   501,   492,  -373,  -373
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -373,  -373,   530,  -373,  -373,   139,  -373,  -231,  -373,   -27,
     374,   466,  -373,  -373,   316,    -3,  -373,  -373,  -373,  -373,
    -373,  -238,  -159,   261,   -14,    55,   191,  -373,    68,  -373,
    -373,   508,   253,  -373,  -373,  -373,   357,  -373,  -373,   -32,
    -184,  -298,  -373,  -373,  -373,  -373,  -373,  -160,   265,  -373,
    -373,   168,  -373,  -373,  -373,  -372,  -373,   220,    79,    33,
    -373,    39,   -40,  -146,   117,  -306,  -373,  -373,   207,   437,
     124,   226,  -373,  -373,  -373,   266,   -45,   -19,  -373,  -373,
      78,  -373,  -373,  -373,  -373,  -373,    57,  -373,  -373,  -373,
    -373,  -124,   196,   122,   240,  -373,  -373,  -373,    12,   533,
    -373,  -373,    65
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -235
static const yytype_int16 yytable[] =
{
      18,    80,    48,   121,   218,    74,    43,   364,   126,   284,
     362,   422,     1,    77,     7,    29,    48,   268,    45,    18,
      18,    18,    18,   309,   261,    18,    34,  -234,   123,    33,
     277,    35,    45,    49,    29,    29,    29,    29,     8,   332,
      29,    33,    22,   381,   127,     8,   285,    49,   128,   451,
       9,    10,    11,    12,    13,   209,   312,   124,   291,  -119,
     293,    22,    22,    22,    22,   353,   -57,    22,    30,   312,
     410,   411,   408,   168,    37,   382,    78,     4,   294,   363,
      42,   286,    42,    42,   124,   186,     5,    30,    30,    30,
      30,   169,   295,    30,   124,    42,   372,    39,    42,   171,
     172,    48,    54,   440,   395,    72,   343,    42,   213,   213,
      14,   203,   165,   170,   434,   219,   119,   207,   244,   166,
      23,   333,   124,   470,   212,   212,   339,    24,   341,    59,
     342,   120,    49,   461,   254,   210,    72,    72,    72,    23,
      23,    23,    23,   186,   472,    23,    24,    24,    24,    24,
     426,   280,    24,   211,   260,   430,    72,   308,    74,    18,
     473,    50,    51,    52,    53,     8,    59,    56,   299,   487,
       9,    10,    11,   307,    29,   338,   388,   355,   356,   357,
     190,   393,   190,   -54,    18,    78,    57,   501,   308,   290,
     308,   287,   217,   217,    44,    54,    60,   445,    61,    29,
     446,    22,    72,    75,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    22,    30,    71,    25,
     310,  -160,   429,   505,   431,   245,    78,   246,   247,   248,
     249,   124,    72,    28,   250,    72,     9,    10,    25,    25,
      25,    25,    30,   118,    25,    18,   436,   437,    72,   131,
     132,   133,    28,    28,    28,    28,   438,   437,    28,   300,
      29,   122,   129,   304,  -119,   347,   120,   170,    65,    23,
     -97,    66,   213,   213,   213,    67,    24,   159,   160,     8,
     162,   346,   174,    68,     9,    10,    11,    22,   212,   212,
     212,   255,   398,    69,    23,   175,    49,   371,   373,   374,
      70,    24,   163,   170,   176,   314,   135,   136,   137,   138,
     139,   140,   177,    30,   178,   221,   276,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   183,
     184,   186,   185,   409,    72,   188,    72,   193,   135,   194,
     359,   138,   139,   140,   202,   265,   217,   217,   217,   135,
     366,    65,   204,   256,    66,    23,    65,   258,   130,    66,
     259,   278,    24,   376,   170,   262,    68,   263,    25,   269,
     264,    68,   272,   270,    72,   271,    69,   311,   396,   274,
     126,    69,    28,    70,   281,   181,   182,   190,    70,   418,
     292,   298,   301,    25,   418,   302,   303,   317,   322,   406,
     323,   195,   196,   197,   198,   328,   199,    28,   320,   331,
     200,   201,   326,    18,   245,    18,   246,   247,   248,   249,
     471,   334,   245,   250,   246,   247,   248,   249,    29,   329,
      29,   250,   336,   502,   285,   344,   293,   350,   365,   368,
      72,   367,    72,   489,   251,   369,   380,   443,   385,   444,
     386,   387,   283,   390,   498,    22,   401,    22,   415,   392,
     499,   394,   400,   421,    25,   407,    72,   428,   432,   454,
     346,   266,   267,   433,   435,   462,   439,   441,    28,   442,
     456,    30,   418,    30,   468,    49,   455,     8,   463,   448,
     466,   474,     9,    10,    11,    81,   457,   377,   475,   467,
     476,    82,    83,   477,    84,    85,    86,    87,   486,    88,
      89,    90,   493,   504,   507,   305,    31,   257,   491,   492,
      91,   161,   335,    64,    72,   345,   419,   279,   481,   384,
     500,   397,   340,    23,   404,    23,   490,   208,   506,   459,
      24,   348,    24,   508,     0,    92,    93,    62,     0,     0,
       0,     0,     0,     0,     0,   458,     0,   460,     0,   134,
     135,   136,   137,   138,   139,   140,   324,   142,   143,   144,
       0,     0,   145,   146,   147,   148,   149,   150,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   220,     0,   450,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,     0,   360,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   370,     0,     0,     0,
       0,   375,   135,   136,   137,   138,   139,   140,     0,   142,
     143,   144,   389,     0,   145,   146,   147,   148,   149,   150,
       0,     0,    25,     0,    25,     0,     0,   488,   135,   136,
     137,   138,   139,   140,     0,   142,    28,   405,    28,     0,
     145,   146,   147,   148,   149,   150,     0,   412,   413,   414,
       0,     0,     0,     0,     0,     0,   420,     0,     0,     0,
       0,   423,   424,     0,   321,     0,   427,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,     0,     0,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   135,   136,   137,   138,   139,   140,     0,
       0,   452,     0,     0,   453,   494,   146,   147,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,     0,
     465,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,     0,     0,     0,     0,     0,     0,
       0,     0,   478,   479,   480,     0,   482,   483,   484,   485,
       0,     0,     0,     0,     0,     0,     0,   135,   136,   137,
     138,   139,   140,     0,   142,   495,   144,   496,   497,   145,
     146,   147,   148,   149,   150,   503,   469,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,     0,     0,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,     0,     0,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
       0,     0,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   135,   136,   137,   138,   139,   140,   135,   136,
     137,   138,   139,   140,   145,   146,   147,   148,   149,   150,
       0,   146,   147,   148,   149
};

static const yytype_int16 yycheck[] =
{
       3,    41,    21,    48,   128,    37,    20,   313,    12,   193,
     308,   383,    14,    40,     0,     3,    35,   177,    21,    22,
      23,    24,    25,   254,   170,    28,    14,    31,    12,    12,
     189,    64,    35,    21,    22,    23,    24,    25,     4,   277,
      28,    12,     3,    12,    58,     4,    12,    35,    62,   421,
       9,    10,    11,    12,    13,    12,     5,    41,   204,    30,
      12,    22,    23,    24,    25,    12,    37,    28,     3,     5,
     368,   369,     5,    29,    29,    44,    32,     6,    30,   310,
      31,    47,    31,    31,    41,    34,    15,    22,    23,    24,
      25,    47,    44,    28,    41,    31,    47,    12,    31,    70,
      71,   120,    41,   409,   342,    37,   290,    31,   127,   128,
      69,    29,     5,    80,    33,   129,    33,   120,   158,    12,
       3,   280,    41,    47,   127,   128,   286,     3,   288,    47,
     289,    48,   120,   439,   161,    29,    68,    69,    70,    22,
      23,    24,    25,    34,    31,    28,    22,    23,    24,    25,
     388,   191,    28,    47,   168,   393,    88,    48,   190,   162,
      47,    22,    23,    24,    25,     4,    47,    28,   213,   475,
       9,    10,    11,    33,   162,    33,   335,   301,   302,   303,
      29,   340,    29,    32,   187,    32,    12,    33,    48,   203,
      48,   194,   127,   128,    33,    41,    47,     5,    12,   187,
       8,   162,   134,    48,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   187,   162,    37,     3,
     257,    32,   392,    33,   394,     3,    32,     5,     6,     7,
       8,    41,   174,     3,    12,   177,     9,    10,    22,    23,
      24,    25,   187,    12,    28,   258,    47,    48,   190,    68,
      69,    70,    22,    23,    24,    25,    47,    48,    28,   214,
     258,    12,    33,   218,    30,   294,    48,   244,     5,   162,
      32,     8,   301,   302,   303,    12,   162,    30,    12,     4,
      47,   294,    30,    20,     9,    10,    11,   258,   301,   302,
     303,   162,   347,    30,   187,    47,   294,   321,   322,   323,
      37,   187,    48,   280,    47,   260,    37,    38,    39,    40,
      41,    42,    30,   258,    30,   134,   187,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,    12,
      30,    34,    30,   367,   286,    12,   288,    30,    37,    30,
     305,    40,    41,    42,    12,   174,   301,   302,   303,    37,
     315,     5,    32,    12,     8,   258,     5,    47,    12,     8,
      35,   190,   258,    12,   351,    12,    20,    12,   162,    12,
      37,    20,     6,    47,   326,    47,    30,   258,   343,     6,
      12,    30,   162,    37,    48,    89,    90,    29,    37,   376,
      12,    12,    47,   187,   381,    47,    47,    35,    33,   364,
      33,   105,   106,   107,   108,    33,   110,   187,    47,    33,
     114,   115,    48,   436,     3,   438,     5,     6,     7,     8,
     454,    12,     3,    12,     5,     6,     7,     8,   436,    48,
     438,    12,    47,   498,    12,    35,    12,    47,    47,    29,
     392,    48,   394,   477,    33,    29,    47,   412,    47,   414,
      47,    47,    33,    47,   493,   436,    12,   438,    25,    47,
     494,    47,    47,    12,   258,    47,   418,    47,    47,    33,
     493,   175,   176,    47,    47,   440,    48,    47,   258,    47,
      33,   436,   469,   438,   449,   493,    47,     4,    16,    66,
      65,    30,     9,    10,    11,    12,    67,   326,    48,    65,
      30,    18,    19,    17,    21,    22,    23,    24,    68,    26,
      27,    28,    30,    33,    33,   219,     6,   163,   483,   484,
      37,    75,   281,    35,   476,   292,   378,   190,   469,   329,
     495,   344,   287,   436,   358,   438,   478,   120,   503,   437,
     436,   295,   438,   506,    -1,    62,    63,    34,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   436,    -1,   438,    -1,    36,
      37,    38,    39,    40,    41,    42,   270,    44,    45,    46,
      -1,    -1,    49,    50,    51,    52,    53,    54,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    -1,   418,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    -1,   306,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,   320,    -1,    -1,    -1,
      -1,   325,    37,    38,    39,    40,    41,    42,    -1,    44,
      45,    46,   336,    -1,    49,    50,    51,    52,    53,    54,
      -1,    -1,   436,    -1,   438,    -1,    -1,   476,    37,    38,
      39,    40,    41,    42,    -1,    44,   436,   361,   438,    -1,
      49,    50,    51,    52,    53,    54,    -1,   371,   372,   373,
      -1,    -1,    -1,    -1,    -1,    -1,   380,    -1,    -1,    -1,
      -1,   385,   386,    -1,    33,    -1,   390,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    -1,    -1,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    37,    38,    39,    40,    41,    42,    -1,
      -1,   425,    -1,    -1,   428,    33,    50,    51,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    -1,
     444,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   466,   467,   468,    -1,   470,   471,   472,   473,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,    38,    39,
      40,    41,    42,    -1,    44,   489,    46,   491,   492,    49,
      50,    51,    52,    53,    54,   499,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    -1,    -1,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    -1,    -1,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      -1,    -1,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    37,    38,    39,    40,    41,    42,    37,    38,
      39,    40,    41,    42,    49,    50,    51,    52,    53,    54,
      -1,    50,    51,    52,    53
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    14,    73,    74,     6,    15,    76,     0,     4,     9,
      10,    11,    12,    13,    69,    77,    78,    83,    87,   101,
     102,   114,   133,   136,   142,   143,   149,   160,   166,   170,
     174,    74,    75,    12,   170,    64,    84,    29,    81,    12,
      82,   132,    31,    96,    33,    87,   103,   141,   149,   170,
      77,    77,    77,    77,    41,   148,    77,    12,   171,    47,
      47,    12,   171,    85,   103,     5,     8,    12,    20,    30,
      37,    98,   100,   108,   111,    48,    80,    81,    32,   131,
     134,    12,    18,    19,    21,    22,    23,    24,    26,    27,
      28,    37,    62,    63,    86,    87,    88,   100,   105,   111,
     115,   116,   117,   121,   125,   133,   136,   142,   143,   151,
     155,   156,   157,   159,   166,   167,   170,   174,    12,    33,
      48,   148,    12,    12,    41,   146,    12,    96,    96,    33,
      12,    98,    98,    98,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    99,    30,
      12,    83,    47,    48,    79,     5,    12,   135,    29,    47,
     131,    70,    71,    91,    30,    47,    47,    30,    30,    98,
     119,    86,    86,    12,    30,    30,    34,    97,    12,    95,
      29,    89,    94,    30,    30,    86,    86,    86,    86,    86,
      86,    86,    12,    29,    32,   104,   139,    87,   141,    12,
      29,    47,    87,   149,   163,   172,   173,   174,   163,    96,
      33,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    98,    98,    98,   134,     3,     5,     6,     7,     8,
      12,    33,   112,   113,    81,    77,    12,    82,    47,    35,
      96,   135,    12,    12,    37,    98,    86,    86,   119,    12,
      47,    47,     6,   122,     6,   126,    77,    94,    98,   108,
     134,    48,    93,    33,   112,    12,    47,    87,   118,   120,
      96,   135,    12,    12,    30,    44,   147,   150,    12,   148,
      97,    47,    47,    47,    97,    86,   110,    33,    48,    79,
      81,    77,     5,    96,    97,   137,   138,    35,   168,   169,
      47,    33,    33,    33,    86,    92,    48,   123,    33,    48,
     127,    33,    93,    94,    12,    95,    47,   107,    33,   119,
     120,   119,    94,   112,    35,   104,    87,   149,   147,   145,
      47,   134,   140,    12,   162,   163,   163,   163,   161,    97,
      86,   109,   113,    79,   137,    47,    97,    48,    29,    29,
      86,    96,    47,    96,    96,    86,    12,    98,   124,   129,
      47,    12,    44,   128,   129,    47,    47,    47,    94,    86,
      47,   106,    47,    94,    47,    93,    97,   140,   148,   144,
      47,    12,   164,   165,   164,    86,    97,    47,     5,    96,
     113,   113,    86,    86,    86,    25,   152,   130,   131,   123,
      86,    12,   127,    86,    86,    90,    93,    86,    47,   119,
      93,   119,    47,    47,    33,    47,    47,    48,    47,    48,
     137,    47,    47,    97,    97,     5,     8,   154,    66,   153,
      98,   127,    86,    86,    33,    47,    33,    67,    77,   165,
      77,   137,    97,    16,   158,    86,    65,    65,    97,    35,
      47,    96,    31,    47,    30,    48,    30,    17,    86,    86,
      86,   130,    86,    86,    86,    86,    68,   137,    98,    96,
     152,    97,    97,    30,    33,    86,    86,    86,   149,    96,
      97,    33,   148,    86,    33,    33,    97,    33,   158
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
    {printf("Syntax is Correct\n");return;}
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

  case 51:

/* Line 1455 of yacc.c  */
#line 494 ".\\semanticAnalysis.y"
    {
            strcpy(typeBuffer,(yyvsp[(1) - (1)].type));
            (yyval.type)=malloc(strlen((yyvsp[(1) - (1)].type))+1);
            strcpy((yyval.type),(yyvsp[(1) - (1)].type));
        }
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 501 ".\\semanticAnalysis.y"
    {dimit = 0;}
    break;

  case 55:

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

  case 57:

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

  case 59:

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

  case 64:

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

  case 66:

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

  case 67:

/* Line 1455 of yacc.c  */
#line 564 ".\\semanticAnalysis.y"
    {scope++;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 565 ".\\semanticAnalysis.y"
    {deleteDMT(scope);scope--;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 594 ".\\semanticAnalysis.y"
    {dimit = 0;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 595 ".\\semanticAnalysis.y"
    {dimit = 0;}
    break;

  case 101:

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

  case 103:

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

  case 104:

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

  case 105:

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

  case 106:

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

  case 107:

/* Line 1455 of yacc.c  */
#line 674 ".\\semanticAnalysis.y"
    {
                    struct SymbolTableEntry*new_entry = insertIdentifier(ptrBuf,CLASS[3],(yyvsp[(1) - (1)].type),pointerLen,yylinenumber,scope+1);
                    PD[noOfParameters]=pointerLen;
                    strcpy(PL[noOfParameters],(yyvsp[(1) - (1)].type));
                    PTL[noOfParameters]='p';
                    noOfParameters++;
                }
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 681 ".\\semanticAnalysis.y"
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

  case 109:

/* Line 1455 of yacc.c  */
#line 701 ".\\semanticAnalysis.y"
    {
    (yyval.type)=malloc(strlen("array")+1);strcpy((yyval.type),"array");

    }
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 704 ".\\semanticAnalysis.y"
    {(yyval.type)=malloc(strlen("variable")+1);strcpy((yyval.type),"variable");}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 707 ".\\semanticAnalysis.y"
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

  case 113:

/* Line 1455 of yacc.c  */
#line 742 ".\\semanticAnalysis.y"
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

  case 115:

/* Line 1455 of yacc.c  */
#line 790 ".\\semanticAnalysis.y"
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
#line 825 ".\\semanticAnalysis.y"
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
#line 871 ".\\semanticAnalysis.y"
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

  case 120:

/* Line 1455 of yacc.c  */
#line 888 ".\\semanticAnalysis.y"
    {
    strcpy(PL[noOfParameters],(yyvsp[(1) - (1)].type));
    PTL[noOfParameters]=pt;
    noOfParameters++;
}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 893 ".\\semanticAnalysis.y"
    {
            strcpy(PL[noOfParameters],(yyvsp[(3) - (3)].type));
            PTL[noOfParameters]=pt;
            noOfParameters++;
        }
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 898 ".\\semanticAnalysis.y"
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

  case 123:

/* Line 1455 of yacc.c  */
#line 926 ".\\semanticAnalysis.y"
    {(yyval.type)=malloc(strlen((yyvsp[(1) - (1)].type))+1);strcpy((yyval.type),(yyvsp[(1) - (1)].type));pt='v';parD[parDi++]=0;}
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

  case 128:

/* Line 1455 of yacc.c  */
#line 932 ".\\semanticAnalysis.y"
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

  case 133:

/* Line 1455 of yacc.c  */
#line 970 ".\\semanticAnalysis.y"
    {scope++;}
    break;

  case 140:

/* Line 1455 of yacc.c  */
#line 980 ".\\semanticAnalysis.y"
    {
    struct SymbolTableEntry * search=lookup((yyvsp[(1) - (1)].value),scope,false);
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

  case 159:

/* Line 1455 of yacc.c  */
#line 1010 ".\\semanticAnalysis.y"
    {ID_dim++;}
    break;

  case 160:

/* Line 1455 of yacc.c  */
#line 1012 ".\\semanticAnalysis.y"
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

  case 161:

/* Line 1455 of yacc.c  */
#line 1026 ".\\semanticAnalysis.y"
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

  case 164:

/* Line 1455 of yacc.c  */
#line 1037 ".\\semanticAnalysis.y"
    {dimbuffer[dimit++] = intval;}
    break;

  case 165:

/* Line 1455 of yacc.c  */
#line 1037 ".\\semanticAnalysis.y"
    {dimbuffer[dimit++] = 10000;}
    break;

  case 181:

/* Line 1455 of yacc.c  */
#line 1052 ".\\semanticAnalysis.y"
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

  case 183:

/* Line 1455 of yacc.c  */
#line 1068 ".\\semanticAnalysis.y"
    {if(strcmp((yyvsp[(3) - (6)].type),(yyvsp[(6) - (6)].type))!=0){
    char message[30]="Variable Types dont Match";
        int res=yyerror(message);
        return -1;}}
    break;

  case 185:

/* Line 1455 of yacc.c  */
#line 1071 ".\\semanticAnalysis.y"
    {if(strcmp((yyvsp[(3) - (5)].type),(yyvsp[(5) - (5)].type))!=0){
    char message[30]="Variable Types dont Match";
        int res=yyerror(message);
        return -1;
}}
    break;

  case 188:

/* Line 1455 of yacc.c  */
#line 1077 ".\\semanticAnalysis.y"
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

  case 189:

/* Line 1455 of yacc.c  */
#line 1091 ".\\semanticAnalysis.y"
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

  case 190:

/* Line 1455 of yacc.c  */
#line 1103 ".\\semanticAnalysis.y"
    {  
     pointerLen++;
}
    break;

  case 211:

/* Line 1455 of yacc.c  */
#line 1121 ".\\semanticAnalysis.y"
    {
        struct SymbolTableEntry*new_entry=insertIdentifier(userTypeNameBuffer,CLASS[4],userTypeBuffer,userTypeDim,yylinenumber,scope);
        userTypeDim = 0;
    }
    break;

  case 213:

/* Line 1455 of yacc.c  */
#line 1126 ".\\semanticAnalysis.y"
    {
        struct SymbolTableEntry*new_entry=insertIdentifier(userTypeNameBuffer,CLASS[4],userTypeBuffer,userTypeDim,yylinenumber,scope);
        userTypeDim = 0;
                }
    break;

  case 224:

/* Line 1455 of yacc.c  */
#line 1141 ".\\semanticAnalysis.y"
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

  case 228:

/* Line 1455 of yacc.c  */
#line 1156 ".\\semanticAnalysis.y"
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
                        }
    break;

  case 230:

/* Line 1455 of yacc.c  */
#line 1177 ".\\semanticAnalysis.y"
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
                        }
    break;

  case 232:

/* Line 1455 of yacc.c  */
#line 1199 ".\\semanticAnalysis.y"
    {
            strcpy(userTypeBuffer,(yyvsp[(1) - (1)].type));
            (yyval.type)=malloc(strlen((yyvsp[(1) - (1)].type))+1);
            strcpy((yyval.type),(yyvsp[(1) - (1)].type));
        }
    break;

  case 233:

/* Line 1455 of yacc.c  */
#line 1204 ".\\semanticAnalysis.y"
    {
            strcpy(userTypeBuffer,(yyvsp[(1) - (1)].type));
            (yyval.type)=malloc(strlen((yyvsp[(1) - (1)].type))+1);
            strcpy((yyval.type),(yyvsp[(1) - (1)].type));
        }
    break;

  case 234:

/* Line 1455 of yacc.c  */
#line 1210 ".\\semanticAnalysis.y"
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

  case 235:

/* Line 1455 of yacc.c  */
#line 1221 ".\\semanticAnalysis.y"
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

  case 236:

/* Line 1455 of yacc.c  */
#line 1237 ".\\semanticAnalysis.y"
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

  case 237:

/* Line 1455 of yacc.c  */
#line 1257 ".\\semanticAnalysis.y"
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
#line 3484 "y.tab.c"
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
#line 1280 ".\\semanticAnalysis.y"


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
