
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

/* Line 214 of yacc.c  */
#line 415 ".\\semanticAnalysis.y"

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
#define YYLAST   816

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  71
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  96
/* YYNRULES -- Number of rules.  */
#define YYNRULES  222
/* YYNRULES -- Number of states.  */
#define YYNSTATES  486

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
      22,    24,    27,    28,    35,    41,    46,    47,    52,    53,
      56,    59,    60,    62,    64,    71,    73,    74,    76,    78,
      80,    82,    84,    86,    91,    95,    99,   102,   105,   108,
     111,   113,   116,   119,   122,   125,   128,   129,   131,   138,
     144,   145,   146,   154,   159,   160,   163,   166,   167,   169,
     171,   173,   177,   181,   185,   189,   193,   197,   201,   205,
     209,   213,   216,   219,   222,   226,   230,   234,   238,   242,
     246,   250,   254,   258,   262,   266,   270,   274,   278,   280,
     281,   285,   287,   289,   291,   297,   301,   304,   310,   314,
     316,   320,   322,   323,   324,   332,   333,   340,   341,   348,
     349,   355,   357,   359,   363,   365,   367,   369,   371,   373,
     375,   387,   397,   409,   419,   428,   435,   441,   446,   448,
     449,   456,   458,   461,   465,   468,   470,   472,   479,   482,
     487,   491,   495,   498,   500,   502,   505,   510,   514,   516,
     518,   523,   528,   532,   534,   543,   551,   553,   556,   564,
     571,   577,   581,   586,   592,   594,   598,   603,   605,   606,
     610,   615,   616,   625,   626,   634,   641,   643,   645,   648,
     650,   653,   655,   657,   670,   682,   692,   698,   699,   703,
     704,   706,   708,   710,   712,   714,   727,   736,   737,   746,
     747,   758,   759,   769,   773,   777,   781,   784,   787,   790,
     792,   796,   797,   802,   806,   815,   822,   829,   831,   833,
     835,   839,   843
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      72,     0,    -1,    73,    76,    83,    -1,    13,    75,    74,
      -1,    73,    -1,    -1,     5,    -1,    14,    -1,    98,    -1,
      77,    -1,   155,    -1,   160,    76,    -1,    -1,    86,    81,
      80,    78,    46,    76,    -1,    82,    80,    79,    46,    76,
      -1,    47,    81,    80,    78,    -1,    -1,    47,    82,    80,
      78,    -1,    -1,    28,    95,    -1,    28,   105,    -1,    -1,
      11,    -1,    11,    -1,    63,    84,    32,    93,    85,    94,
      -1,   100,    -1,    -1,    87,    -1,   116,    -1,   120,    -1,
     102,    -1,   113,    -1,   112,    -1,    25,   115,    46,    85,
      -1,    21,    46,    85,    -1,    18,    46,    85,    -1,    26,
      85,    -1,    27,    85,    -1,   128,    85,    -1,   131,    85,
      -1,   146,    -1,   138,    85,    -1,   137,    85,    -1,   150,
      85,    -1,   160,    85,    -1,   161,    85,    -1,    -1,     3,
      -1,    86,    92,    91,    90,    46,    85,    -1,    97,    91,
      90,    46,    85,    -1,    -1,    -1,    97,    88,   129,    91,
      46,    89,    85,    -1,    47,    92,    91,    90,    -1,    -1,
      28,    95,    -1,    28,   105,    -1,    -1,    11,    -1,    30,
      -1,    33,    -1,    29,    95,    32,    -1,    95,    37,    95,
      -1,    95,    38,    95,    -1,    95,    40,    95,    -1,    95,
      39,    95,    -1,    95,    41,    95,    -1,    95,    42,    95,
      -1,    95,    35,    95,    -1,    95,    45,    95,    -1,    95,
      43,    95,    -1,    95,    36,    -1,    36,    95,    -1,    19,
      95,    -1,    95,    44,    95,    -1,    95,    48,    95,    -1,
      95,    49,    95,    -1,    95,    50,    95,    -1,    95,    51,
      95,    -1,    95,    52,    95,    -1,    95,    53,    95,    -1,
      95,    54,    95,    -1,    95,    55,    95,    -1,    95,    56,
      95,    -1,    95,    57,    95,    -1,    95,    58,    95,    -1,
      95,    59,    95,    -1,    95,    60,    95,    -1,    97,    -1,
      -1,    97,    96,   129,    -1,     4,    -1,     7,    -1,    11,
      -1,    99,    93,    85,    94,    76,    -1,   111,   100,    32,
      -1,   111,    32,    -1,   100,    47,    86,    11,   101,    -1,
     100,    47,   136,    -1,   136,    -1,    86,    11,   101,    -1,
     134,    -1,    -1,    -1,   108,    29,   109,    32,   103,    46,
      85,    -1,    -1,   108,    29,    32,   104,    46,    85,    -1,
      -1,   108,    29,   109,    32,   106,    85,    -1,    -1,   108,
      29,    32,   107,    85,    -1,    11,    -1,   110,    -1,   109,
      47,   110,    -1,    11,    -1,     4,    -1,     5,    -1,     7,
      -1,     6,    -1,    12,    -1,    20,    29,   114,   115,    46,
     115,    32,    93,    85,    94,    85,    -1,    20,    29,   114,
     115,    46,   115,    32,    46,    85,    -1,    20,    29,    46,
     115,    46,   115,    32,    93,    85,    94,    85,    -1,    20,
      29,    46,   115,    46,   115,    32,    46,    85,    -1,    22,
      29,   115,    32,    93,    85,    94,    85,    -1,    22,    29,
     115,    32,    46,    85,    -1,    86,    11,    91,    90,    46,
      -1,    11,    91,    90,    46,    -1,    95,    -1,    -1,    61,
      29,   117,    32,    46,    85,    -1,     5,    -1,     5,   118,
      -1,    47,   119,   118,    -1,    47,   119,    -1,    95,    -1,
     124,    -1,    62,    29,   121,    32,    46,    85,    -1,     5,
     122,    -1,    47,    43,    11,   122,    -1,    47,    43,    11,
      -1,    47,   123,   122,    -1,    47,   123,    -1,    11,    -1,
     124,    -1,    11,   125,    -1,   126,    95,    34,   125,    -1,
     126,    95,    34,    -1,    31,    -1,    11,    -1,    86,   127,
     129,    46,    -1,   129,   126,   130,    34,    -1,   126,   130,
      34,    -1,     4,    -1,    86,   127,   129,    28,    93,   132,
      94,    46,    -1,    86,   127,   129,    28,    93,    94,    46,
      -1,   133,    -1,   133,    47,    -1,   133,    47,    93,   132,
      94,    47,   132,    -1,   133,    47,    93,   132,    94,    47,
      -1,   133,    47,    93,   132,    94,    -1,    93,   132,    94,
      -1,    93,   132,    94,    47,    -1,    93,   132,    94,    47,
     132,    -1,     4,    -1,   133,    47,     4,    -1,    31,   130,
      34,   135,    -1,   129,    -1,    -1,   144,   143,    11,    -1,
     144,   143,   141,    46,    -1,    -1,   144,   143,   141,    28,
      43,   142,   139,    46,    -1,    -1,   144,   143,   141,    28,
     142,   140,    46,    -1,   144,   143,   141,    28,   145,    46,
      -1,    11,    -1,    11,    -1,   143,    40,    -1,    40,    -1,
     162,    11,    -1,    86,    -1,    10,    -1,    29,   144,   143,
      32,    66,    29,    67,    29,   144,   143,    32,    32,    -1,
      29,   144,   143,    32,    66,    29,    67,    29,   144,    32,
      32,    -1,    23,    29,    11,    32,    93,   147,   148,    94,
      85,    -1,    24,   149,    64,    85,   147,    -1,    -1,    65,
      64,    85,    -1,    -1,     7,    -1,     4,    -1,   151,    -1,
     152,    -1,   154,    -1,    17,    29,    95,    32,    93,    85,
      94,   153,    16,    93,    85,    94,    -1,    15,    29,    95,
      32,    93,    85,    94,   153,    -1,    -1,    17,    29,    95,
      32,    93,    85,    94,   153,    -1,    -1,    68,   162,   163,
      93,   158,    94,   156,   159,    46,    76,    -1,    -1,   162,
     163,    93,   158,    94,   157,   159,    46,    76,    -1,   165,
      46,   158,    -1,   164,    46,   158,    -1,   166,    46,   158,
      -1,   165,    46,    -1,   164,    46,    -1,   166,    46,    -1,
      11,    -1,   159,    47,    11,    -1,    -1,   162,    11,    11,
      46,    -1,    11,    11,    46,    -1,   162,    11,    11,    28,
      93,   109,    94,    46,    -1,    11,    69,    11,    28,   110,
      46,    -1,    11,    70,    11,    28,   110,    46,    -1,     8,
      -1,     9,    -1,    11,    -1,   144,   143,    11,    -1,    86,
      11,   135,    -1,   162,    11,    11,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   442,   442,   443,   444,   444,   445,   445,   447,   447,
     447,   447,   447,   449,   450,   451,   451,   452,   452,   453,
     453,   459,   461,   472,   484,   485,   485,   487,   487,   487,
     487,   487,   487,   488,   488,   488,   489,   489,   489,   489,
     490,   490,   490,   490,   491,   491,   491,   493,   498,   499,
     500,   500,   500,   520,   520,   521,   521,   527,   529,   541,
     542,   544,   545,   546,   547,   548,   549,   550,   551,   552,
     553,   554,   555,   556,   557,   558,   559,   560,   561,   562,
     563,   564,   565,   566,   567,   568,   569,   570,   571,   572,
     572,   573,   573,   575,   590,   591,   602,   613,   646,   653,
     660,   680,   683,   686,   686,   720,   720,   766,   766,   800,
     800,   845,   862,   867,   872,   900,   901,   902,   903,   905,
     938,   939,   940,   941,   943,   944,   946,   947,   949,   949,
     951,   952,   953,   954,   955,   956,   956,   958,   959,   960,
     961,   962,   963,   964,   964,   966,   967,   967,   969,   971,
     984,   986,   986,   988,   993,   993,   994,   995,   996,   997,
     998,   999,  1000,  1001,  1002,  1002,  1004,  1005,  1005,  1007,
    1022,  1023,  1023,  1026,  1026,  1030,  1032,  1046,  1058,  1060,
    1061,  1061,  1061,  1062,  1063,  1065,  1066,  1066,  1067,  1067,
    1068,  1068,  1070,  1071,  1071,  1072,  1073,  1073,  1074,  1076,
    1076,  1081,  1080,  1086,  1087,  1088,  1089,  1090,  1091,  1094,
    1094,  1094,  1097,  1097,  1098,  1099,  1100,  1102,  1107,  1113,
    1124,  1139,  1159
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TYPE", "INTEGER", "STRING",
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
  "varDec", "$@1", "$@2", "D", "options", "id", "open_flower",
  "close_flower", "Exp", "$@3", "id3", "function_defn",
  "function_declaration", "parameter_list", "choice", "function_call",
  "$@4", "$@5", "function_call1", "$@6", "$@7", "funName", "params",
  "item", "fun_start", "for", "while", "varDecF", "ExpF", "print",
  "printExpr", "printArguments", "printContent", "scanf", "scanfExpr",
  "scanfArguments", "scanfContent", "arrayElement", "dimension", "open_sq",
  "ID2", "arrayDeclr", "BOX", "integer_dim", "arrayInitial",
  "BALANCED_BRACK", "arrayParams_unend", "arrayAsAParameter",
  "higherDimention", "pointerAsAParameter", "PTR_DECLR", "PTR_INITIAL",
  "$@8", "$@9", "idinsert", "idlook", "PTR_STAR", "PTR_TYPE", "PTR_EXP",
  "switch", "switchcase", "default", "comp", "ifElseLadder", "S",
  "matched", "elif", "unmatched", "userTypeDefination", "$@10", "$@11",
  "userTypeParams", "userTypeObj", "userTypeDeclaration",
  "userTypeInitialization", "userDefDataType", "sidi", "pointerInStruct",
  "varInStruct", "structInStruct", 0
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
      80,    80,    81,    82,    83,    84,    84,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    86,    87,    87,
      88,    89,    87,    90,    90,    91,    91,    91,    92,    93,
      94,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    96,
      95,    95,    95,    97,    98,    99,    99,   100,   100,   100,
     100,   101,   101,   103,   102,   104,   102,   106,   105,   107,
     105,   108,   109,   109,   110,   110,   110,   110,   110,   111,
     112,   112,   112,   112,   113,   113,   114,   114,   115,   115,
     116,   117,   117,   118,   118,   119,   119,   120,   121,   122,
     122,   122,   122,   123,   123,   124,   125,   125,   126,   127,
     128,   129,   129,   130,   131,   131,   132,   132,   132,   132,
     132,   132,   132,   132,   133,   133,   134,   135,   135,   136,
     137,   139,   138,   140,   138,   138,   141,   142,   143,   143,
     144,   144,   144,   145,   145,   146,   147,   147,   148,   148,
     149,   149,   150,   151,   151,   152,   153,   153,   154,   156,
     155,   157,   155,   158,   158,   158,   158,   158,   158,   159,
     159,   159,   160,   160,   161,   161,   161,   162,   162,   163,
     164,   165,   166
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     3,     1,     0,     1,     1,     1,     1,
       1,     2,     0,     6,     5,     4,     0,     4,     0,     2,
       2,     0,     1,     1,     6,     1,     0,     1,     1,     1,
       1,     1,     1,     4,     3,     3,     2,     2,     2,     2,
       1,     2,     2,     2,     2,     2,     0,     1,     6,     5,
       0,     0,     7,     4,     0,     2,     2,     0,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     0,
       3,     1,     1,     1,     5,     3,     2,     5,     3,     1,
       3,     1,     0,     0,     7,     0,     6,     0,     6,     0,
       5,     1,     1,     3,     1,     1,     1,     1,     1,     1,
      11,     9,    11,     9,     8,     6,     5,     4,     1,     0,
       6,     1,     2,     3,     2,     1,     1,     6,     2,     4,
       3,     3,     2,     1,     1,     2,     4,     3,     1,     1,
       4,     4,     3,     1,     8,     7,     1,     2,     7,     6,
       5,     3,     4,     5,     1,     3,     4,     1,     0,     3,
       4,     0,     8,     0,     7,     6,     1,     1,     2,     1,
       2,     1,     1,    12,    11,     9,     5,     0,     3,     0,
       1,     1,     1,     1,     1,    12,     8,     0,     8,     0,
      10,     0,     9,     3,     3,     3,     2,     2,     2,     1,
       3,     0,     4,     3,     8,     6,     6,     1,     1,     1,
       3,     3,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,    12,     6,     7,     5,     1,    47,   217,
     218,    23,   119,     0,     0,     9,    21,     0,     8,     0,
       0,    10,    12,     0,     4,     3,     0,     0,    26,     2,
       0,    18,    22,    21,    59,    46,   182,    96,   181,     0,
      99,     0,     0,    11,   219,     0,   213,   219,     0,     0,
      25,    91,    92,    93,     0,     0,     0,    19,    88,    20,
       0,     0,     0,    16,    93,     0,     0,     0,     0,     0,
       0,   129,    46,    46,     0,     0,     0,   181,    27,    57,
      30,     0,    32,    31,    28,    29,    46,    46,    46,    46,
       0,    40,    46,   192,   193,   194,    46,    46,     0,   102,
      95,     0,   179,     0,   180,     0,     0,     0,     0,    93,
      73,     0,    72,     0,    71,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    23,
      21,    12,     0,     0,     0,     0,     0,    46,     0,    46,
     129,     0,   128,     0,    36,    37,     0,     0,    60,    12,
      58,    57,     0,     0,     0,    54,     0,    38,    39,    42,
      41,     0,    43,    44,    45,   180,     0,   100,   101,   181,
      98,   169,   178,   212,   181,     0,     0,     0,     0,     0,
       0,     0,    46,    61,    68,    62,    63,    65,    64,    66,
      67,    70,    74,    69,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,   148,     0,    90,
     115,   116,   118,   117,   114,   109,     0,   112,    16,    14,
      21,    12,     0,     0,     0,    35,    57,   129,     0,   129,
      34,     0,     0,    46,   131,     0,     0,     0,    94,    54,
       0,    55,    56,    57,     0,     0,   105,     0,   176,     0,
       0,   153,     0,   102,   168,     0,   201,   180,   207,   206,
     208,   199,     0,     0,     0,    46,   107,     0,    17,    16,
      13,     0,     0,     0,    54,     0,    57,     0,     0,     0,
      33,     0,   132,     0,     0,   138,     0,     0,     0,   150,
       0,    58,    57,    46,     0,   103,     0,   170,     0,   168,
      97,   167,   221,   220,   211,   222,   204,   203,   205,   211,
      24,   152,     0,   110,    46,   113,    15,     0,     0,    46,
       0,   129,    54,   129,    46,    46,   187,    93,   135,   134,
     136,    46,   143,     0,   142,   144,    46,    46,     0,    51,
      54,    49,    46,     0,   177,     0,     0,   173,     0,     0,
     166,   209,     0,     0,   151,   108,   215,   216,     0,   127,
       0,     0,     0,   125,     0,     0,   189,   145,     0,   133,
     130,   140,   141,   137,    48,   164,     0,     0,     0,   156,
      46,    53,   106,    46,   181,     0,   171,     0,   175,     0,
      12,     0,    12,   197,     0,   126,     0,    46,   191,   190,
       0,     0,     0,     0,   139,     0,   155,     0,   157,    52,
     104,     0,     0,   174,     0,   202,   210,   200,     0,   198,
      46,    46,    46,    46,   124,    46,    46,    46,   147,   161,
     154,   165,     0,     0,   172,   214,     0,     0,   123,     0,
     121,     0,   187,   188,   185,   146,   162,     0,     0,     0,
      46,    46,    46,   186,   163,   160,     0,     0,     0,   122,
     120,   159,     0,    46,   195,   158,     0,     0,     0,   197,
       0,     0,   196,   184,     0,   183
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    25,     6,    14,    15,   143,    62,    31,
      33,    16,    29,    49,    76,    77,    78,   164,   390,   255,
     165,   161,   386,   159,   152,   137,    58,    18,    19,    39,
     177,    80,   353,   304,    59,   324,   275,    81,   226,   227,
      20,    82,    83,   239,   153,    84,   245,   292,   339,    85,
     247,   295,   344,   340,   377,   218,   162,    86,   311,   262,
      87,   388,   389,   178,   312,    40,    88,    89,   422,   397,
     259,   357,   103,    90,   358,    91,   376,   412,   410,    92,
      93,    94,   429,    95,    21,   319,   314,   186,   362,    96,
      97,    98,    45,   188,   189,   190
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -349
static const yytype_int16 yypact[] =
{
      27,    29,    54,    49,  -349,  -349,    27,  -349,  -349,  -349,
    -349,    84,  -349,    82,    90,  -349,    99,   120,  -349,   133,
     111,  -349,    49,   192,  -349,  -349,   159,   213,   318,  -349,
      64,   179,  -349,    99,  -349,   512,  -349,  -349,   232,    97,
    -349,   205,   242,  -349,   244,   133,  -349,  -349,   133,   216,
     209,  -349,  -349,   229,   253,   253,   253,   511,   230,  -349,
     233,   252,   227,   228,    10,   245,   238,   250,   241,   254,
     259,   253,   512,   512,   261,   262,   265,   281,  -349,    14,
    -349,   266,  -349,  -349,  -349,  -349,   512,   512,   512,   512,
     205,  -349,   512,  -349,  -349,  -349,   512,   512,   283,   269,
    -349,   318,  -349,    16,  -349,   256,   318,   318,   133,  -349,
     268,   589,  -349,   253,  -349,   253,   253,   253,   253,   253,
     253,   253,   253,   253,   253,   253,   253,   253,   253,   253,
     253,   253,   253,   253,   253,   253,   253,   277,   208,  -349,
      99,    49,   120,   263,   306,   308,   253,   512,    26,   512,
     253,   311,   511,   279,  -349,  -349,   300,   332,  -349,    49,
     307,   317,   277,    64,   277,   292,   309,  -349,  -349,  -349,
    -349,    65,  -349,  -349,  -349,   340,   349,  -349,  -349,   345,
    -349,  -349,  -349,  -349,   346,   205,   265,   347,   319,   337,
     339,   265,   512,  -349,   722,   194,   194,   268,   268,   268,
     553,   758,   323,   740,   764,   341,   341,   294,   294,   764,
     700,   700,   700,   700,   511,   511,   511,  -349,   349,   277,
    -349,  -349,  -349,  -349,  -349,  -349,   174,  -349,   228,  -349,
      99,    49,   358,   359,   618,  -349,   317,   253,   377,   253,
    -349,   357,   363,   512,   322,   372,   344,   373,  -349,   292,
     104,   511,  -349,    61,   400,   369,  -349,   178,  -349,   106,
     112,  -349,   383,   269,   277,   114,  -349,   407,   318,   318,
     318,  -349,   265,   385,   349,   512,  -349,   343,  -349,   228,
    -349,   343,   343,   133,   292,   374,   317,   375,   100,   133,
    -349,   274,  -349,   376,     4,  -349,   378,   380,   133,  -349,
     381,  -349,   317,   512,   382,  -349,    19,  -349,   133,   277,
    -349,   277,  -349,  -349,   412,  -349,  -349,  -349,  -349,   412,
    -349,  -349,   395,  -349,   512,  -349,  -349,   384,   386,   512,
     388,   253,   292,   253,   512,   512,   416,   277,   511,   322,
    -349,   512,   277,   420,   344,  -349,   512,   512,    51,  -349,
     292,  -349,   512,   397,  -349,   318,   430,  -349,   398,   343,
    -349,  -349,   151,   170,  -349,  -349,  -349,  -349,   265,  -349,
     413,   401,   414,  -349,   265,   237,   387,  -349,   253,  -349,
    -349,   344,  -349,  -349,  -349,  -349,    47,   402,   265,   404,
     512,  -349,  -349,   512,  -349,   205,  -349,   403,  -349,    -1,
      49,   443,    49,   444,   121,  -349,   165,   512,  -349,  -349,
     394,   396,   265,   674,  -349,   265,  -349,   415,   118,  -349,
    -349,    46,   417,  -349,   418,  -349,  -349,  -349,   433,   449,
     512,   512,   512,   512,  -349,   512,   512,   512,   277,   419,
    -349,  -349,    47,   405,  -349,  -349,   253,   133,  -349,   265,
    -349,   265,   416,  -349,  -349,  -349,    47,   265,   439,   647,
     512,   512,   512,  -349,  -349,   422,   408,   133,   265,  -349,
    -349,    47,   441,   512,  -349,  -349,   318,   265,   164,   444,
     440,   168,  -349,  -349,   445,  -349
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -349,  -349,   472,  -349,  -349,    -4,  -349,  -220,  -349,   -28,
     348,   421,  -349,  -349,   150,    -3,  -349,  -349,  -349,  -214,
    -137,   234,   -12,    68,    55,  -349,   -23,  -349,  -349,   453,
     223,  -349,  -349,  -349,   324,  -349,  -349,   -16,  -160,  -120,
    -349,  -349,  -349,  -349,  -124,  -349,  -349,   153,  -349,  -349,
    -349,  -328,  -349,   195,    56,  -209,  -349,  -349,     2,  -207,
    -349,  -348,  -349,  -349,   184,   399,  -349,  -349,  -349,  -349,
    -349,   139,   -88,   -19,  -349,  -349,    52,  -349,  -349,  -349,
    -349,  -349,    20,  -349,  -349,  -349,  -349,   -76,   186,     1,
    -349,     0,   471,  -349,  -349,  -349
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -150
static const yytype_int16 yytable[] =
{
      17,    41,   171,    23,    22,    63,   257,    35,   278,    41,
     274,   273,    79,    27,    60,   342,   382,    38,    43,    17,
      42,    26,    23,    22,   249,    38,   241,   181,    42,     8,
     354,   191,   158,   106,     4,   297,   107,   236,   415,  -111,
       1,   274,   163,     5,   274,   -50,   277,   343,   355,    79,
      79,   385,     8,   414,     7,   385,   182,     9,    10,   326,
      11,    12,   356,    79,    79,    79,    79,   322,    51,    79,
     330,    52,   237,    79,    79,    53,   258,    34,   443,   144,
     145,    34,    41,    54,   158,    57,   182,   185,   185,   163,
       9,    10,   217,    55,   457,    26,   192,   265,   179,   284,
      56,    42,   274,   184,   184,   182,   187,   187,   464,   110,
     111,   112,   228,   285,     8,   287,   300,    13,   371,     9,
      10,    36,   441,   475,    79,   313,    79,    30,   378,   100,
      34,    32,   298,   378,   306,   217,   391,   229,    17,   219,
     308,    23,    22,    37,   101,   238,   334,    60,    34,   332,
     299,    34,   307,    28,   182,   248,    17,   325,   183,    23,
      22,   327,   328,    34,   250,   350,   253,   430,   194,    79,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   316,   317,   318,    34,   480,   400,   401,   399,
     484,   234,   279,    44,   102,    46,   276,   370,   182,   372,
     305,   432,   220,   221,   222,   223,   402,   401,   251,   224,
      79,   277,   154,   155,    47,   277,    61,   280,    17,   378,
     114,    23,    22,   117,   118,   119,   167,   168,   169,   170,
     225,   408,   172,    99,   409,   102,   173,   174,   108,   185,
     185,   185,    79,   104,   266,   105,   101,    51,  -111,   271,
      52,   -89,   138,   139,   109,   184,   184,   184,   187,   187,
     187,   329,    54,   141,   146,   142,   335,   336,    51,   148,
      79,    52,    55,   150,   147,   337,   348,   149,   151,    56,
     156,   157,   160,    54,   175,   166,   359,   235,   158,   240,
     176,    79,   183,    55,   114,   244,    79,   421,   217,   231,
      56,    79,    79,   220,   221,   222,   223,   232,    79,   233,
     224,     8,   242,    79,    79,   243,     9,    10,    36,    79,
     114,   115,   116,   117,   118,   119,   395,   246,  -149,   254,
     320,   256,   272,   125,   126,   163,   338,   220,   221,   222,
     223,   260,   394,   261,   224,    42,   263,   264,   267,   114,
     115,   116,   117,   118,   119,   268,   121,    79,   123,   291,
      79,   124,   125,   126,   127,   128,   129,   114,   115,   116,
     117,   118,   119,   269,    79,   270,   281,   282,   286,   288,
     481,   294,   431,   290,   433,   289,   425,    17,   427,    17,
      23,    22,    23,    22,   293,   296,   442,    79,    79,    79,
      79,   301,    79,    79,    79,   303,   387,   309,   315,   321,
     331,   333,   341,   361,   346,   323,   347,   349,   352,   364,
     366,   381,   367,   413,   369,   460,   403,    79,    79,    79,
     375,   354,   407,   393,   398,   404,   406,   405,   416,   423,
      79,   418,   411,   351,   426,   473,   417,   478,   435,   428,
     436,   440,   446,   444,   445,   447,   456,   424,   466,   471,
     476,   458,   483,   394,   365,   472,    42,   485,    24,   368,
     437,    50,   140,   439,   373,   374,   310,   252,   302,   345,
     230,   380,   379,   360,   455,   396,   383,   384,    48,   482,
     180,   459,   392,     0,   463,   363,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     8,     0,   461,     0,   462,
       9,    10,    36,    64,     0,   465,     0,     0,     0,    65,
      66,     0,    67,    68,    69,    70,   474,    71,    72,    73,
     419,     0,     0,   420,     0,   479,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   434,     0,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,     0,    74,    75,     0,     0,     0,     0,     0,
     448,   449,   450,   451,     0,   452,   453,   454,   113,   114,
     115,   116,   117,   118,   119,     0,   121,   122,   123,     0,
       0,   124,   125,   126,   127,   128,   129,     0,     0,     0,
     468,   469,   470,     0,     0,     0,     0,     0,     0,     0,
       0,   193,     0,   477,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,     0,     0,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     283,     0,     0,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,     0,     0,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   467,
       0,     0,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,     0,     0,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   438,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
       0,     0,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,     0,     0,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   114,   115,
     116,   117,   118,   119,     0,   121,   122,   123,     0,     0,
     124,   125,   126,   127,   128,   129,   114,   115,   116,   117,
     118,   119,     0,   121,     0,     0,     0,     0,   124,   125,
     126,   127,   128,   129,   114,   115,   116,   117,   118,   119,
     114,   115,   116,   117,   118,   119,   124,   125,   126,   127,
     128,   129,     0,   125,   126,   127,   128
};

static const yytype_int16 yycheck[] =
{
       3,    20,    90,     3,     3,    33,   166,    19,   228,    28,
     219,   218,    35,    13,    30,    11,   344,    20,    22,    22,
      20,    11,    22,    22,   161,    28,   150,    11,    28,     3,
      11,   107,    33,    45,     5,   249,    48,    11,   386,    29,
      13,   250,    28,    14,   253,    31,    47,    43,    29,    72,
      73,     4,     3,   381,     0,     4,    40,     8,     9,   279,
      11,    12,    43,    86,    87,    88,    89,   274,     4,    92,
     284,     7,    46,    96,    97,    11,    11,    30,    32,    69,
      70,    30,   101,    19,    33,    30,    40,   106,   107,    28,
       8,     9,    31,    29,   442,    11,   108,   185,   101,   236,
      36,   101,   311,   106,   107,    40,   106,   107,   456,    54,
      55,    56,   140,   237,     3,   239,   253,    68,   332,     8,
       9,    10,     4,   471,   147,    11,   149,    28,   337,    32,
      30,    11,    28,   342,    28,    31,   350,   141,   141,   137,
      28,   141,   141,    32,    47,   148,    46,   163,    30,   286,
      46,    30,    46,    63,    40,   159,   159,   277,    46,   159,
     159,   281,   282,    30,   162,   302,   164,    46,   113,   192,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   268,   269,   270,    30,    32,    46,    47,   359,
      32,   146,   230,    11,    40,    46,    32,   331,    40,   333,
      32,    46,     4,     5,     6,     7,    46,    47,   163,    11,
     243,    47,    72,    73,    11,    47,    47,   231,   231,   438,
      36,   231,   231,    39,    40,    41,    86,    87,    88,    89,
      32,     4,    92,    11,     7,    40,    96,    97,    32,   268,
     269,   270,   275,    11,   186,    11,    47,     4,    29,   191,
       7,    31,    29,    11,    11,   268,   269,   270,   268,   269,
     270,   283,    19,    46,    29,    47,   288,   289,     4,    29,
     303,     7,    29,    29,    46,    11,   298,    46,    29,    36,
      29,    29,    11,    19,    11,    29,   308,   147,    33,   149,
      31,   324,    46,    29,    36,     5,   329,   395,    31,    46,
      36,   334,   335,     4,     5,     6,     7,    11,   341,    11,
      11,     3,    11,   346,   347,    46,     8,     9,    10,   352,
      36,    37,    38,    39,    40,    41,   355,     5,    31,    47,
     272,    32,   192,    49,    50,    28,   291,     4,     5,     6,
       7,    11,   355,     4,    11,   355,    11,    11,    11,    36,
      37,    38,    39,    40,    41,    46,    43,   390,    45,    47,
     393,    48,    49,    50,    51,    52,    53,    36,    37,    38,
      39,    40,    41,    46,   407,    46,    28,    28,    11,    32,
     478,    47,   404,   243,   406,    32,   400,   400,   402,   402,
     400,   400,   402,   402,    32,    32,   418,   430,   431,   432,
     433,    11,   435,   436,   437,    46,   348,    34,    11,    34,
      46,    46,    46,    11,    46,   275,    46,    46,    46,    34,
      46,    11,    46,   378,    46,   447,   368,   460,   461,   462,
      24,    11,   374,    46,    46,    32,    32,    46,    46,    46,
     473,    47,    65,   303,    11,   467,   388,   476,    64,    15,
      64,    46,    29,    46,    46,    16,    47,   399,    29,    47,
      29,    66,    32,   476,   324,    67,   476,    32,     6,   329,
     412,    28,    61,   415,   334,   335,   263,   163,   254,   294,
     142,   341,   339,   309,   438,   356,   346,   347,    27,   479,
     101,   446,   352,    -1,   452,   319,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     3,    -1,   449,    -1,   451,
       8,     9,    10,    11,    -1,   457,    -1,    -1,    -1,    17,
      18,    -1,    20,    21,    22,    23,   468,    25,    26,    27,
     390,    -1,    -1,   393,    -1,   477,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,   407,    -1,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    -1,    61,    62,    -1,    -1,    -1,    -1,    -1,
     430,   431,   432,   433,    -1,   435,   436,   437,    35,    36,
      37,    38,    39,    40,    41,    -1,    43,    44,    45,    -1,
      -1,    48,    49,    50,    51,    52,    53,    -1,    -1,    -1,
     460,   461,   462,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    32,    -1,   473,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    -1,    -1,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      32,    -1,    -1,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    -1,    -1,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    32,
      -1,    -1,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    -1,    -1,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      -1,    -1,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    -1,    -1,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    36,    37,
      38,    39,    40,    41,    -1,    43,    44,    45,    -1,    -1,
      48,    49,    50,    51,    52,    53,    36,    37,    38,    39,
      40,    41,    -1,    43,    -1,    -1,    -1,    -1,    48,    49,
      50,    51,    52,    53,    36,    37,    38,    39,    40,    41,
      36,    37,    38,    39,    40,    41,    48,    49,    50,    51,
      52,    53,    -1,    49,    50,    51,    52
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    13,    72,    73,     5,    14,    75,     0,     3,     8,
       9,    11,    12,    68,    76,    77,    82,    86,    98,    99,
     111,   155,   160,   162,    73,    74,    11,   162,    63,    83,
      28,    80,    11,    81,    30,    93,    10,    32,    86,   100,
     136,   144,   162,    76,    11,   163,    46,    11,   163,    84,
     100,     4,     7,    11,    19,    29,    36,    95,    97,   105,
     108,    47,    79,    80,    11,    17,    18,    20,    21,    22,
      23,    25,    26,    27,    61,    62,    85,    86,    87,    97,
     102,   108,   112,   113,   116,   120,   128,   131,   137,   138,
     144,   146,   150,   151,   152,   154,   160,   161,   162,    11,
      32,    47,    40,   143,    11,    11,    93,    93,    32,    11,
      95,    95,    95,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    96,    29,    11,
      82,    46,    47,    78,    69,    70,    29,    46,    29,    46,
      29,    29,    95,   115,    85,    85,    29,    29,    33,    94,
      11,    92,   127,    28,    88,    91,    29,    85,    85,    85,
      85,   143,    85,    85,    85,    11,    31,   101,   134,    86,
     136,    11,    40,    46,    86,   144,   158,   162,   164,   165,
     166,   158,    93,    32,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    31,   126,   129,
       4,     5,     6,     7,    11,    32,   109,   110,    80,    76,
      81,    46,    11,    11,    95,    85,    11,    46,    86,   114,
      85,   115,    11,    46,     5,   117,     5,   121,    76,    91,
     129,    95,   105,   129,    47,    90,    32,   109,    11,   141,
      11,     4,   130,    11,    11,   143,    94,    11,    46,    46,
      46,    94,    85,   130,   126,   107,    32,    47,    78,    80,
      76,    28,    28,    32,    91,   115,    11,   115,    32,    32,
      85,    47,   118,    32,    47,   122,    32,    90,    28,    46,
      91,    11,    92,    46,   104,    32,    28,    46,    28,    34,
     101,   129,   135,    11,   157,    11,   158,   158,   158,   156,
      94,    34,   130,    85,   106,   110,    78,   110,   110,    93,
      90,    46,    91,    46,    46,    93,    93,    11,    95,   119,
     124,    46,    11,    43,   123,   124,    46,    46,    93,    46,
      91,    85,    46,   103,    11,    29,    43,   142,   145,    93,
     135,    11,   159,   159,    34,    85,    46,    46,    85,    46,
     115,    90,   115,    85,    85,    24,   147,   125,   126,   118,
      85,    11,   122,    85,    85,     4,    93,    94,   132,   133,
      89,    90,    85,    46,    86,   144,   142,   140,    46,   109,
      46,    47,    46,    94,    32,    46,    32,    94,     4,     7,
     149,    65,   148,    95,   122,   132,    46,    94,    47,    85,
      85,   143,   139,    46,    94,    76,    11,    76,    15,   153,
      46,    93,    46,    93,    85,    64,    64,    94,    34,    94,
      46,     4,    93,    32,    46,    46,    29,    16,    85,    85,
      85,    85,    85,    85,    85,   125,    47,   132,    66,    95,
      93,    94,    94,   147,   132,    94,    29,    32,    85,    85,
      85,    47,    67,    93,    94,   132,    29,    85,   144,    94,
      32,   143,   153,    32,    32,    32
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

  case 20:

/* Line 1455 of yacc.c  */
#line 453 ".\\semanticAnalysis.y"
    {
    if(strcmp(forFunc->dataType,"void")==0){
        char const errorMessage[100]="Void Function Does not return anything";
        int a=yyerror(errorMessage);
        return -1;
    }
}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 461 ".\\semanticAnalysis.y"
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

  case 23:

/* Line 1455 of yacc.c  */
#line 472 ".\\semanticAnalysis.y"
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

  case 47:

/* Line 1455 of yacc.c  */
#line 493 ".\\semanticAnalysis.y"
    {
            strcpy(typeBuffer,(yyvsp[(1) - (1)].type));
            (yyval.type)=malloc(strlen((yyvsp[(1) - (1)].type))+1);
            strcpy((yyval.type),(yyvsp[(1) - (1)].type));
        }
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 500 ".\\semanticAnalysis.y"
    {dimit = 0;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 500 ".\\semanticAnalysis.y"
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

  case 56:

/* Line 1455 of yacc.c  */
#line 521 ".\\semanticAnalysis.y"
    {
    if(strcmp(forFunc->dataType,"void")==0){
        char const errorMessage[100]="Void Function Does not return anything";
        int a=yyerror(errorMessage);
        return -1;
    }
}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 529 ".\\semanticAnalysis.y"
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

  case 59:

/* Line 1455 of yacc.c  */
#line 541 ".\\semanticAnalysis.y"
    {scope++;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 542 ".\\semanticAnalysis.y"
    {deleteDMT(scope);scope--;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 571 ".\\semanticAnalysis.y"
    {dimit = 0;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 572 ".\\semanticAnalysis.y"
    {dimit = 0;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 575 ".\\semanticAnalysis.y"
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

  case 95:

/* Line 1455 of yacc.c  */
#line 591 ".\\semanticAnalysis.y"
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

  case 96:

/* Line 1455 of yacc.c  */
#line 602 ".\\semanticAnalysis.y"
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

  case 97:

/* Line 1455 of yacc.c  */
#line 613 ".\\semanticAnalysis.y"
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
#line 646 ".\\semanticAnalysis.y"
    {
                    struct SymbolTableEntry*new_entry = insertIdentifier(ptrBuf,CLASS[3],(yyvsp[(3) - (3)].type),pointerLen,yylinenumber,scope+1);
                    PD[noOfParameters]=pointerLen;
                    strcpy(PL[noOfParameters],(yyvsp[(3) - (3)].type));
                    PTL[noOfParameters]='p';
                    noOfParameters++;
                }
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 653 ".\\semanticAnalysis.y"
    {
                    struct SymbolTableEntry*new_entry = insertIdentifier(ptrBuf,CLASS[3],(yyvsp[(1) - (1)].type),pointerLen,yylinenumber,scope+1);
                    PD[noOfParameters]=pointerLen;
                    strcpy(PL[noOfParameters],(yyvsp[(1) - (1)].type));
                    PTL[noOfParameters]='p';
                    noOfParameters++;
                }
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 660 ".\\semanticAnalysis.y"
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

  case 101:

/* Line 1455 of yacc.c  */
#line 680 ".\\semanticAnalysis.y"
    {
    (yyval.type)=malloc(strlen("array")+1);strcpy((yyval.type),"array");

    }
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 683 ".\\semanticAnalysis.y"
    {(yyval.type)=malloc(strlen("variable")+1);strcpy((yyval.type),"variable");}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 686 ".\\semanticAnalysis.y"
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

  case 105:

/* Line 1455 of yacc.c  */
#line 720 ".\\semanticAnalysis.y"
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

  case 107:

/* Line 1455 of yacc.c  */
#line 766 ".\\semanticAnalysis.y"
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

  case 109:

/* Line 1455 of yacc.c  */
#line 800 ".\\semanticAnalysis.y"
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

  case 111:

/* Line 1455 of yacc.c  */
#line 845 ".\\semanticAnalysis.y"
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

  case 112:

/* Line 1455 of yacc.c  */
#line 862 ".\\semanticAnalysis.y"
    {
    strcpy(PL[noOfParameters],(yyvsp[(1) - (1)].type));
    PTL[noOfParameters]=pt;
    noOfParameters++;
}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 867 ".\\semanticAnalysis.y"
    {
            strcpy(PL[noOfParameters],(yyvsp[(3) - (3)].type));
            PTL[noOfParameters]=pt;
            noOfParameters++;
        }
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 872 ".\\semanticAnalysis.y"
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

  case 115:

/* Line 1455 of yacc.c  */
#line 900 ".\\semanticAnalysis.y"
    {(yyval.type)=malloc(strlen((yyvsp[(1) - (1)].type))+1);strcpy((yyval.type),(yyvsp[(1) - (1)].type));pt='v';parD[parDi++]=0;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 901 ".\\semanticAnalysis.y"
    {(yyval.type)=malloc(strlen((yyvsp[(1) - (1)].type))+1);strcpy((yyval.type),(yyvsp[(1) - (1)].type));pt='v';parD[parDi++]=0;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 902 ".\\semanticAnalysis.y"
    {(yyval.type)=malloc(strlen((yyvsp[(1) - (1)].type))+1);strcpy((yyval.type),(yyvsp[(1) - (1)].type));pt='v';parD[parDi++]=0;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 903 ".\\semanticAnalysis.y"
    {(yyval.type)=malloc(strlen((yyvsp[(1) - (1)].type))+1);strcpy((yyval.type),(yyvsp[(1) - (1)].type));pt='v';parD[parDi++]=0;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 905 ".\\semanticAnalysis.y"
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

  case 148:

/* Line 1455 of yacc.c  */
#line 969 ".\\semanticAnalysis.y"
    {ID_dim++;}
    break;

  case 149:

/* Line 1455 of yacc.c  */
#line 971 ".\\semanticAnalysis.y"
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

  case 150:

/* Line 1455 of yacc.c  */
#line 985 ".\\semanticAnalysis.y"
    {struct SymbolTableEntry* temp = insertArray(IDBuffer,CLASS[2],typeBuffer,dimit,yylinenumber,scope,dimbuffer);dimit = 0;}
    break;

  case 153:

/* Line 1455 of yacc.c  */
#line 988 ".\\semanticAnalysis.y"
    {dimbuffer[dimit++] = intval;if(intval<=0){
    char message[50]="Array Index Should be Greater Than Equal to 0";
    int a=yyerror(message);
    return -1;
}}
    break;

  case 169:

/* Line 1455 of yacc.c  */
#line 1007 ".\\semanticAnalysis.y"
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

  case 171:

/* Line 1455 of yacc.c  */
#line 1023 ".\\semanticAnalysis.y"
    {if(strcmp((yyvsp[(3) - (6)].type),(yyvsp[(6) - (6)].type))!=0){
    char message[30]="Variable Types dont Match";
        int res=yyerror(message);
        return -1;}}
    break;

  case 173:

/* Line 1455 of yacc.c  */
#line 1026 ".\\semanticAnalysis.y"
    {if(strcmp((yyvsp[(3) - (5)].type),(yyvsp[(5) - (5)].type))!=0){
    char message[30]="Variable Types dont Match";
        int res=yyerror(message);
        return -1;
}}
    break;

  case 176:

/* Line 1455 of yacc.c  */
#line 1032 ".\\semanticAnalysis.y"
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

  case 177:

/* Line 1455 of yacc.c  */
#line 1046 ".\\semanticAnalysis.y"
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

  case 178:

/* Line 1455 of yacc.c  */
#line 1058 ".\\semanticAnalysis.y"
    {  
     pointerLen++;
}
    break;

  case 199:

/* Line 1455 of yacc.c  */
#line 1076 ".\\semanticAnalysis.y"
    {
        struct SymbolTableEntry*new_entry=insertIdentifier(userTypeNameBuffer,CLASS[4],userTypeBuffer,userTypeDim,yylinenumber,scope);
        userTypeDim = 0;
    }
    break;

  case 201:

/* Line 1455 of yacc.c  */
#line 1081 ".\\semanticAnalysis.y"
    {
        struct SymbolTableEntry*new_entry=insertIdentifier(userTypeNameBuffer,CLASS[4],userTypeBuffer,userTypeDim,yylinenumber,scope);
        userTypeDim = 0;
                }
    break;

  case 217:

/* Line 1455 of yacc.c  */
#line 1102 ".\\semanticAnalysis.y"
    {
            strcpy(userTypeBuffer,(yyvsp[(1) - (1)].type));
            (yyval.type)=malloc(strlen((yyvsp[(1) - (1)].type))+1);
            strcpy((yyval.type),(yyvsp[(1) - (1)].type));
        }
    break;

  case 218:

/* Line 1455 of yacc.c  */
#line 1107 ".\\semanticAnalysis.y"
    {
            strcpy(userTypeBuffer,(yyvsp[(1) - (1)].type));
            (yyval.type)=malloc(strlen((yyvsp[(1) - (1)].type))+1);
            strcpy((yyval.type),(yyvsp[(1) - (1)].type));
        }
    break;

  case 219:

/* Line 1455 of yacc.c  */
#line 1113 ".\\semanticAnalysis.y"
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

  case 220:

/* Line 1455 of yacc.c  */
#line 1124 ".\\semanticAnalysis.y"
    {
    struct SymbolTableEntry * found=lookup((yyvsp[(3) - (3)].value),scope,true);
    if(found != NULL)
    {
        char const errorMessage[100]="Variable Already Declared!!";
        int a=yyerror(errorMessage);
        return -1;
    }
    else{
        struct SymbolTableEntry*new_entry=insertIdentifier((yyvsp[(3) - (3)].value),CLASS[3],userTypeNameBuffer,pointerLen,yylinenumber,scope);
        pointerLen = 1;
    }
    userTypeDim++;
}
    break;

  case 221:

/* Line 1455 of yacc.c  */
#line 1140 ".\\semanticAnalysis.y"
    {
    struct SymbolTableEntry * search=lookup((yyvsp[(2) - (3)].value),scope,true);
    if(search!=NULL){
        char message[30]="Variable Already Declared";
        int res=yyerror(message);
        return -1;
    }
    else{
        if(dimit==0){
            struct SymbolTableEntry*new_entry=insertIdentifier((yyvsp[(2) - (3)].value),CLASS[0],userTypeNameBuffer,dimit,yylinenumber,scope);
        }else{
            struct SymbolTableEntry*new_entry=insertIdentifier((yyvsp[(2) - (3)].value),CLASS[2],userTypeNameBuffer,dimit,yylinenumber,scope);
        }
        
        userTypeDim++;
        dimit = 0;
    }
}
    break;

  case 222:

/* Line 1455 of yacc.c  */
#line 1160 ".\\semanticAnalysis.y"
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
                    else{struct SymbolTableEntry * search=lookup((yyvsp[(3) - (3)].value),scope,true);
                        if(search!=NULL){
                        char message[30]="Variable Already Declared";
                        int res=yyerror(message);
                        return -1;
                        }else{
                            struct SymbolTableEntry*new_entry=insertIdentifier((yyvsp[(3) - (3)].value),CLASS[4],(yyvsp[(2) - (3)].value),0,yylinenumber,scope);
                        }
                    }
                    userTypeDim++;       
                }
    break;



/* Line 1455 of yacc.c  */
#line 3301 "y.tab.c"
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
#line 1183 ".\\semanticAnalysis.y"


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
