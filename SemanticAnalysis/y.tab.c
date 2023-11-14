
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


/* Line 189 of yacc.c  */
#line 485 "y.tab.c"

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
#line 412 ".\\semanticAnalysis.y"

    char * value;
    char * type;



/* Line 214 of yacc.c  */
#line 668 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 680 "y.tab.c"

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
#define YYLAST   800

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  71
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  90
/* YYNRULES -- Number of rules.  */
#define YYNRULES  215
/* YYNRULES -- Number of states.  */
#define YYNSTATES  476

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
      56,    57,    59,    61,    68,    70,    71,    73,    75,    77,
      79,    81,    83,    88,    92,    96,    99,   102,   105,   108,
     110,   113,   116,   119,   122,   125,   126,   128,   135,   141,
     142,   143,   151,   156,   157,   160,   163,   164,   166,   168,
     170,   174,   178,   182,   186,   190,   194,   198,   202,   206,
     210,   213,   216,   219,   223,   227,   231,   235,   239,   243,
     247,   251,   255,   259,   263,   267,   271,   275,   277,   278,
     282,   284,   286,   288,   294,   298,   301,   307,   311,   313,
     317,   319,   320,   321,   329,   330,   337,   338,   345,   346,
     352,   354,   356,   360,   362,   364,   366,   368,   370,   372,
     384,   394,   406,   416,   425,   432,   438,   443,   445,   446,
     453,   455,   458,   462,   465,   467,   469,   476,   479,   484,
     488,   492,   495,   497,   499,   502,   507,   511,   513,   515,
     520,   525,   529,   531,   540,   548,   550,   553,   561,   568,
     574,   578,   583,   589,   591,   595,   600,   602,   603,   607,
     612,   613,   622,   623,   631,   638,   640,   642,   645,   647,
     650,   652,   654,   667,   679,   689,   695,   696,   700,   701,
     703,   705,   707,   709,   711,   724,   733,   734,   743,   753,
     762,   768,   772,   778,   783,   786,   791,   793,   797,   798,
     803,   807,   816,   823,   830,   832
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      72,     0,    -1,    73,    76,    83,    -1,    10,    75,    74,
      -1,    73,    -1,    -1,     5,    -1,    11,    -1,    98,    -1,
      77,    -1,   155,    -1,   158,    76,    -1,    -1,    86,    81,
      80,    78,    45,    76,    -1,    82,    80,    79,    45,    76,
      -1,    46,    81,    80,    78,    -1,    -1,    46,    82,    80,
      78,    -1,    -1,    27,    95,    -1,    -1,     8,    -1,     8,
      -1,    62,    84,    31,    93,    85,    94,    -1,   100,    -1,
      -1,    87,    -1,   116,    -1,   120,    -1,   102,    -1,   113,
      -1,   112,    -1,    24,   115,    45,    85,    -1,    18,    45,
      85,    -1,    15,    45,    85,    -1,    25,    85,    -1,    26,
      85,    -1,   128,    85,    -1,   131,    85,    -1,   146,    -1,
     138,    85,    -1,   137,    85,    -1,   150,    85,    -1,   158,
      85,    -1,   159,    85,    -1,    -1,     3,    -1,    86,    92,
      91,    90,    45,    85,    -1,    97,    91,    90,    45,    85,
      -1,    -1,    -1,    97,    88,   129,    91,    45,    89,    85,
      -1,    46,    92,    91,    90,    -1,    -1,    27,    95,    -1,
      27,   105,    -1,    -1,     8,    -1,    29,    -1,    32,    -1,
      28,    95,    31,    -1,    95,    36,    95,    -1,    95,    37,
      95,    -1,    95,    39,    95,    -1,    95,    38,    95,    -1,
      95,    40,    95,    -1,    95,    41,    95,    -1,    95,    34,
      95,    -1,    95,    44,    95,    -1,    95,    42,    95,    -1,
      95,    35,    -1,    35,    95,    -1,    16,    95,    -1,    95,
      43,    95,    -1,    95,    47,    95,    -1,    95,    48,    95,
      -1,    95,    49,    95,    -1,    95,    50,    95,    -1,    95,
      51,    95,    -1,    95,    52,    95,    -1,    95,    53,    95,
      -1,    95,    54,    95,    -1,    95,    55,    95,    -1,    95,
      56,    95,    -1,    95,    57,    95,    -1,    95,    58,    95,
      -1,    95,    59,    95,    -1,    97,    -1,    -1,    97,    96,
     129,    -1,     4,    -1,     7,    -1,     8,    -1,    99,    93,
      85,    94,    76,    -1,   111,   100,    31,    -1,   111,    31,
      -1,   100,    46,    86,     8,   101,    -1,   100,    46,   136,
      -1,   136,    -1,    86,     8,   101,    -1,   134,    -1,    -1,
      -1,   108,    28,   109,    31,   103,    45,    85,    -1,    -1,
     108,    28,    31,   104,    45,    85,    -1,    -1,   108,    28,
     109,    31,   106,    85,    -1,    -1,   108,    28,    31,   107,
      85,    -1,     8,    -1,   110,    -1,   109,    46,   110,    -1,
       8,    -1,     4,    -1,     5,    -1,     7,    -1,     6,    -1,
       9,    -1,    17,    28,   114,   115,    45,   115,    31,    93,
      85,    94,    85,    -1,    17,    28,   114,   115,    45,   115,
      31,    45,    85,    -1,    17,    28,    45,   115,    45,   115,
      31,    93,    85,    94,    85,    -1,    17,    28,    45,   115,
      45,   115,    31,    45,    85,    -1,    19,    28,   115,    31,
      93,    85,    94,    85,    -1,    19,    28,   115,    31,    45,
      85,    -1,    86,     8,    91,    90,    45,    -1,     8,    91,
      90,    45,    -1,    95,    -1,    -1,    60,    28,   117,    31,
      45,    85,    -1,     5,    -1,     5,   118,    -1,    46,   119,
     118,    -1,    46,   119,    -1,    95,    -1,   124,    -1,    61,
      28,   121,    31,    45,    85,    -1,     5,   122,    -1,    46,
      42,     8,   122,    -1,    46,    42,     8,    -1,    46,   123,
     122,    -1,    46,   123,    -1,     8,    -1,   124,    -1,     8,
     125,    -1,   126,    95,    33,   125,    -1,   126,    95,    33,
      -1,    30,    -1,     8,    -1,    86,   127,   129,    45,    -1,
     129,   126,   130,    33,    -1,   126,   130,    33,    -1,     4,
      -1,    86,   127,   129,    27,    93,   132,    94,    45,    -1,
      86,   127,   129,    27,    93,    94,    45,    -1,   133,    -1,
     133,    46,    -1,   133,    46,    93,   132,    94,    46,   132,
      -1,   133,    46,    93,   132,    94,    46,    -1,   133,    46,
      93,   132,    94,    -1,    93,   132,    94,    -1,    93,   132,
      94,    46,    -1,    93,   132,    94,    46,   132,    -1,     4,
      -1,   133,    46,     4,    -1,    30,   130,    33,   135,    -1,
     129,    -1,    -1,   144,   143,     8,    -1,   144,   143,   141,
      45,    -1,    -1,   144,   143,   141,    27,    42,   142,   139,
      45,    -1,    -1,   144,   143,   141,    27,   142,   140,    45,
      -1,   144,   143,   141,    27,   145,    45,    -1,     8,    -1,
       8,    -1,   143,    39,    -1,    39,    -1,   160,     8,    -1,
      86,    -1,    65,    -1,    28,   144,   143,    31,    66,    28,
      67,    28,   144,   143,    31,    31,    -1,    28,   144,   143,
      31,    66,    28,    67,    28,   144,    31,    31,    -1,    20,
      28,     8,    31,    93,   147,   148,    94,    85,    -1,    21,
     149,    63,    85,   147,    -1,    -1,    64,    63,    85,    -1,
      -1,     7,    -1,     4,    -1,   151,    -1,   152,    -1,   154,
      -1,    14,    28,    95,    31,    93,    85,    94,   153,    13,
      93,    85,    94,    -1,    12,    28,    95,    31,    93,    85,
      94,   153,    -1,    -1,    14,    28,    95,    31,    93,    85,
      94,   153,    -1,    68,   160,     8,    93,   156,    94,   157,
      45,    76,    -1,   160,     8,    93,   156,    94,   157,    45,
      76,    -1,    86,     8,   135,    45,   156,    -1,   136,    45,
     156,    -1,   160,     8,     8,    45,   156,    -1,    86,     8,
     135,    45,    -1,   136,    45,    -1,   160,     8,     8,    45,
      -1,     8,    -1,   157,    46,     8,    -1,    -1,   160,     8,
       8,    45,    -1,     8,     8,    45,    -1,   160,     8,     8,
      27,    93,   109,    94,    45,    -1,     8,    69,     8,    27,
     110,    45,    -1,     8,    70,     8,    27,   110,    45,    -1,
      22,    -1,    23,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   439,   439,   440,   441,   441,   442,   442,   444,   444,
     444,   444,   444,   446,   447,   448,   448,   449,   449,   450,
     450,   452,   463,   475,   476,   476,   478,   478,   478,   478,
     478,   478,   479,   479,   479,   480,   480,   480,   480,   481,
     481,   481,   481,   482,   482,   482,   484,   489,   490,   491,
     491,   491,   511,   511,   512,   512,   518,   520,   532,   533,
     535,   536,   537,   538,   539,   540,   541,   542,   543,   544,
     545,   546,   547,   548,   549,   550,   551,   552,   553,   554,
     555,   556,   557,   558,   559,   560,   561,   562,   563,   563,
     564,   564,   566,   581,   582,   593,   604,   637,   644,   651,
     671,   674,   677,   677,   711,   711,   757,   757,   791,   791,
     836,   853,   858,   863,   891,   892,   893,   894,   896,   929,
     930,   931,   932,   934,   935,   937,   938,   940,   940,   942,
     943,   944,   945,   946,   947,   947,   949,   950,   951,   952,
     953,   954,   955,   955,   957,   958,   958,   960,   962,   975,
     977,   977,   979,   980,   980,   981,   982,   983,   984,   985,
     986,   987,   988,   989,   989,   991,   992,   992,   994,  1009,
    1010,  1010,  1013,  1013,  1017,  1019,  1033,  1045,  1047,  1048,
    1048,  1048,  1049,  1050,  1052,  1053,  1053,  1054,  1054,  1055,
    1055,  1057,  1058,  1058,  1059,  1060,  1060,  1061,  1063,  1063,
    1064,  1065,  1066,  1067,  1068,  1069,  1070,  1070,  1070,  1071,
    1071,  1072,  1073,  1074,  1076,  1076
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
  "matched", "elif", "unmatched", "userTypeDefination", "userTypeParams",
  "userTypeObj", "userTypeDeclaration", "userTypeInitialization",
  "userDefDataType", 0
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
      80,    81,    82,    83,    84,    84,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    86,    87,    87,    88,
      89,    87,    90,    90,    91,    91,    91,    92,    93,    94,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    96,    95,
      95,    95,    97,    98,    99,    99,   100,   100,   100,   100,
     101,   101,   103,   102,   104,   102,   106,   105,   107,   105,
     108,   109,   109,   110,   110,   110,   110,   110,   111,   112,
     112,   112,   112,   113,   113,   114,   114,   115,   115,   116,
     117,   117,   118,   118,   119,   119,   120,   121,   122,   122,
     122,   122,   123,   123,   124,   125,   125,   126,   127,   128,
     129,   129,   130,   131,   131,   132,   132,   132,   132,   132,
     132,   132,   132,   133,   133,   134,   135,   135,   136,   137,
     139,   138,   140,   138,   138,   141,   142,   143,   143,   144,
     144,   144,   145,   145,   146,   147,   147,   148,   148,   149,
     149,   150,   151,   151,   152,   153,   153,   154,   155,   155,
     156,   156,   156,   156,   156,   156,   157,   157,   157,   158,
     158,   159,   159,   159,   160,   160
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     3,     1,     0,     1,     1,     1,     1,
       1,     2,     0,     6,     5,     4,     0,     4,     0,     2,
       0,     1,     1,     6,     1,     0,     1,     1,     1,     1,
       1,     1,     4,     3,     3,     2,     2,     2,     2,     1,
       2,     2,     2,     2,     2,     0,     1,     6,     5,     0,
       0,     7,     4,     0,     2,     2,     0,     1,     1,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     1,     0,     3,
       1,     1,     1,     5,     3,     2,     5,     3,     1,     3,
       1,     0,     0,     7,     0,     6,     0,     6,     0,     5,
       1,     1,     3,     1,     1,     1,     1,     1,     1,    11,
       9,    11,     9,     8,     6,     5,     4,     1,     0,     6,
       1,     2,     3,     2,     1,     1,     6,     2,     4,     3,
       3,     2,     1,     1,     2,     4,     3,     1,     1,     4,
       4,     3,     1,     8,     7,     1,     2,     7,     6,     5,
       3,     4,     5,     1,     3,     4,     1,     0,     3,     4,
       0,     8,     0,     7,     6,     1,     1,     2,     1,     2,
       1,     1,    12,    11,     9,     5,     0,     3,     0,     1,
       1,     1,     1,     1,    12,     8,     0,     8,     9,     8,
       5,     3,     5,     4,     2,     4,     1,     3,     0,     4,
       3,     8,     6,     6,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,    12,     6,     7,     5,     1,    46,    22,
     118,   214,   215,     0,     0,     9,    20,     0,     8,     0,
       0,    10,    12,     0,     4,     3,     0,     0,    25,     2,
       0,    18,    21,    20,    58,    45,    95,   181,   180,     0,
      98,     0,     0,    11,     0,   210,     0,     0,    24,    90,
      91,    92,     0,     0,     0,    19,    87,     0,     0,    16,
      92,     0,     0,     0,     0,     0,     0,   128,    45,    45,
       0,     0,     0,   180,    26,    56,    29,     0,    31,    30,
      27,    28,    45,    45,    45,    45,     0,    39,    45,   191,
     192,   193,    45,    45,     0,   101,    94,     0,   178,     0,
     179,     0,     0,     0,     0,    72,     0,    71,     0,    70,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    22,    20,    12,     0,     0,     0,     0,
       0,    45,     0,    45,   128,     0,   127,     0,    35,    36,
       0,     0,    59,    12,    57,    56,     0,     0,     0,    53,
       0,    37,    38,    41,    40,     0,    42,    43,    44,   179,
       0,    99,   100,   180,    97,   168,   177,   209,   180,     0,
       0,     0,     0,    45,    60,    67,    61,    62,    64,    63,
      65,    66,    69,    73,    68,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,   147,     0,
      89,    16,    14,    20,    12,     0,     0,     0,    34,    56,
     128,     0,   128,    33,     0,     0,    45,   130,     0,     0,
       0,    93,    53,     0,    92,    54,    55,     0,    56,     0,
       0,   114,   115,   117,   116,   113,   104,     0,   111,   175,
       0,     0,   152,     0,   101,   167,   204,   208,   179,   208,
       0,     0,     0,    17,    16,    13,     0,     0,     0,    53,
       0,    56,     0,     0,     0,    32,     0,   131,     0,     0,
     137,     0,     0,     0,   149,     0,     0,    57,    56,    45,
       0,   102,     0,     0,   169,     0,   167,    96,   166,     0,
     201,   206,     0,     0,     0,    23,   151,     0,    15,     0,
       0,    45,     0,   128,    53,   128,    45,    45,   186,    92,
     134,   133,   135,    45,   142,     0,   141,   143,    45,    45,
       0,   108,     0,    50,    53,    48,    45,     0,   112,   176,
       0,     0,   172,     0,     0,   165,   203,    12,     0,   205,
      12,   150,   212,   213,     0,   126,     0,     0,     0,   124,
       0,     0,   188,   144,     0,   132,   129,   139,   140,   136,
      47,   163,     0,     0,     0,   155,    45,   106,    45,    52,
     105,    45,   180,     0,   170,     0,   174,     0,   200,   199,
     207,   202,   198,   196,     0,   125,     0,    45,   190,   189,
       0,     0,     0,     0,   138,     0,   154,     0,   156,   109,
      45,    51,   103,     0,     0,   173,     0,     0,   197,    45,
      45,    45,    45,   123,    45,    45,    45,   146,   160,   153,
     164,     0,   107,     0,   171,   211,     0,     0,   122,     0,
     120,     0,   186,   187,   184,   145,   161,     0,     0,     0,
      45,    45,    45,   185,   162,   159,     0,     0,     0,   121,
     119,   158,     0,    45,   194,   157,     0,     0,     0,   196,
       0,     0,   195,   183,     0,   182
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    25,     6,    14,    15,   137,    58,    31,
      33,    16,    29,    47,    72,    73,    74,   158,   378,   240,
     159,   155,   372,   153,   146,   132,    56,    18,    19,    39,
     171,    76,   337,   290,   236,   410,   376,    77,   247,   248,
      20,    78,    79,   222,   147,    80,   228,   277,   321,    81,
     230,   280,   326,   322,   363,   209,   156,    82,   298,   253,
      83,   374,   375,   172,   299,   179,    84,    85,   414,   385,
     250,   342,    99,    86,   343,    87,   362,   402,   400,    88,
      89,    90,   418,    91,    21,   180,   302,    92,    93,    94
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -306
static const yytype_int16 yypact[] =
{
      47,   190,    92,    36,  -306,  -306,    47,  -306,  -306,    89,
    -306,  -306,  -306,   192,    52,  -306,   108,   138,  -306,   125,
      11,  -306,    36,   151,  -306,  -306,   153,   188,    43,  -306,
     232,   173,  -306,   108,  -306,   464,  -306,  -306,   220,    94,
    -306,   196,   241,  -306,    33,  -306,   125,   215,   209,  -306,
    -306,  -306,   232,   232,   232,   682,   228,   253,   223,   219,
      53,   249,   236,   259,   243,   263,   266,   232,   464,   464,
     267,   268,   265,   291,  -306,    21,  -306,   274,  -306,  -306,
    -306,  -306,   464,   464,   464,   464,   196,  -306,   464,  -306,
    -306,  -306,   464,   464,   297,   277,  -306,    43,  -306,    -2,
    -306,   264,    43,    43,   125,   276,   571,  -306,   232,  -306,
     232,   232,   232,   232,   232,   232,   232,   232,   232,   232,
     232,   232,   232,   232,   232,   232,   232,   232,   232,   232,
     232,   232,   282,  -306,   108,    36,   138,   272,   310,   311,
     232,   464,     5,   464,   232,   314,   682,   281,  -306,  -306,
     323,   324,  -306,    36,   301,   306,   282,   255,   282,   290,
     200,  -306,  -306,  -306,  -306,    82,  -306,  -306,  -306,   330,
     336,  -306,  -306,   333,  -306,  -306,  -306,  -306,   334,   300,
     265,   342,   265,   464,  -306,   497,   235,   235,   276,   276,
     276,   458,   743,   707,   725,   749,   363,   363,   386,   386,
     749,   534,   534,   534,   534,   682,   682,   682,  -306,   336,
     282,   219,  -306,   108,    36,   326,   329,   600,  -306,   306,
     232,   343,   232,  -306,   328,   331,   464,   315,   335,   318,
     344,  -306,   290,   118,   332,   682,  -306,   346,   139,   368,
     337,  -306,  -306,  -306,  -306,  -306,  -306,   121,  -306,  -306,
      46,    68,  -306,   345,   277,   282,    43,   372,   373,   372,
     265,   350,   336,  -306,   219,  -306,   382,   382,   125,   290,
     347,   306,   348,    67,   125,  -306,   285,  -306,   349,    44,
    -306,   359,   360,   125,  -306,   365,   369,  -306,   306,   464,
     370,  -306,   382,    32,  -306,   125,   282,  -306,   282,   371,
    -306,  -306,   234,   374,   240,  -306,  -306,   362,  -306,   383,
     384,   464,   387,   232,   290,   232,   464,   464,   389,   282,
     682,   315,  -306,   464,   282,   409,   318,  -306,   464,   464,
     115,  -306,   122,  -306,   290,  -306,   464,   388,  -306,  -306,
      43,   410,  -306,   391,   382,  -306,    43,    36,   423,    43,
      36,  -306,  -306,  -306,   265,  -306,   411,   396,   412,  -306,
     265,   238,   380,  -306,   232,  -306,  -306,   318,  -306,  -306,
    -306,  -306,    73,   400,   265,   402,   464,  -306,   464,  -306,
    -306,   464,  -306,   196,  -306,   401,  -306,    22,  -306,  -306,
    -306,  -306,  -306,   437,   113,  -306,   120,   464,  -306,  -306,
     390,   392,   265,   656,  -306,   265,  -306,   406,   102,  -306,
     464,  -306,  -306,   133,   414,  -306,   415,   426,   443,   464,
     464,   464,   464,  -306,   464,   464,   464,   282,   416,  -306,
    -306,    73,  -306,   395,  -306,  -306,   232,   125,  -306,   265,
    -306,   265,   389,  -306,  -306,  -306,    73,   265,   438,   629,
     464,   464,   464,  -306,  -306,   419,   404,   125,   265,  -306,
    -306,    73,   440,   464,  -306,  -306,    43,   265,   199,   437,
     442,   213,  -306,  -306,   444,  -306
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -306,  -306,   470,  -306,  -306,   -15,  -306,  -201,  -306,    -1,
     355,   428,  -306,  -306,   141,    -3,  -306,  -306,  -306,  -216,
    -137,   273,   -17,  -133,    63,  -306,   -13,  -306,  -306,   452,
     250,  -306,  -306,  -306,  -306,  -306,  -306,   354,  -259,   -49,
    -306,  -306,  -306,  -306,  -113,  -306,  -306,   182,  -306,  -306,
    -306,  -303,  -306,   237,    86,  -195,  -306,  -306,     4,  -174,
    -306,  -305,  -306,  -306,   218,    -8,  -306,  -306,  -306,  -306,
    -306,   174,   -83,   -19,  -306,  -306,    76,  -306,  -306,  -306,
    -306,  -306,    51,  -306,  -306,   -99,   262,     2,  -306,     8
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -149
static const yytype_int16 yytable[] =
{
      17,    41,    35,   165,   182,    22,   175,    43,     8,    41,
     263,    23,    40,   219,     8,   262,   282,    38,   232,    17,
      40,    27,    75,   368,    22,    38,   332,   102,    42,   103,
      23,   224,    59,    11,    12,   261,    42,   176,   262,     8,
     339,   101,    36,   262,     9,    10,     8,   257,   157,   259,
     220,   -49,   324,   312,   152,    75,    75,     1,    11,    12,
     340,    26,    34,   308,   404,    11,    12,   405,   292,    75,
      75,    75,    75,   293,   341,    75,    37,   371,    41,    75,
      75,  -110,   269,    41,    41,   387,   325,   183,   307,   174,
     249,   294,     7,    55,   173,   295,    34,    26,   357,   178,
     178,   286,    34,   262,    13,    42,   430,   270,    37,   272,
     181,   181,   316,   177,    28,   105,   106,   107,   379,   371,
     212,   176,   138,   139,   364,    96,   447,   305,    75,   364,
      75,    34,    17,   211,   314,    30,   210,    22,   231,   221,
      97,   454,    34,    23,    34,   283,    32,   152,   208,    34,
      17,   334,   291,   377,    34,    22,   465,   300,   419,    44,
     233,    23,   238,   284,   433,   421,   157,   292,   292,   208,
      75,   185,   176,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,     4,    46,   373,    45,   265,
     356,     5,   358,   217,   241,   242,   243,   244,   245,   148,
     149,    17,   264,    75,    11,    12,    22,   309,   310,    57,
     235,   393,    23,   161,   162,   163,   164,   397,    95,   166,
     470,   246,   364,   167,   168,    98,    49,    41,    98,    50,
      51,   407,   398,   338,   474,   399,   104,   388,    52,   100,
     391,   311,   176,   178,   416,    97,   317,   318,   -88,    49,
      53,   133,    50,   234,   181,   136,   330,    54,   135,   426,
     109,    52,   428,   112,   113,   114,    75,   140,   344,   347,
     348,   141,   218,    53,   223,   350,   348,   142,   143,    49,
      54,   144,    50,   319,   145,   150,   151,   152,    75,   154,
     413,    52,   160,    75,    75,   169,   451,   170,   452,   177,
      75,   109,   208,    53,   455,    75,    75,   214,   215,   216,
      54,   383,   225,    75,   260,   464,   226,    41,   227,   229,
      41,  -148,   389,   157,   469,   392,   239,   382,   251,   320,
     252,   254,   255,   178,    17,   256,   178,    17,    42,    22,
     258,   271,    22,   266,   181,    23,   267,   181,    23,   273,
    -110,   276,   274,    75,   279,    75,   278,   275,    75,   241,
     242,   243,   244,   245,   285,   281,   287,   420,   296,   422,
     301,   303,   289,   306,    75,   471,   241,   242,   243,   244,
     245,   431,   313,   315,   323,   351,   331,    75,   109,   110,
     111,   112,   113,   114,   328,   329,    75,    75,    75,    75,
     361,    75,    75,    75,   333,   336,   346,   367,   339,   349,
     450,   109,   110,   111,   112,   113,   114,   403,   352,   353,
     335,   390,   355,   381,   120,   121,   386,    75,    75,    75,
     463,   395,   394,   396,   401,   406,   415,   468,   408,   417,
      75,   429,   354,   424,   436,   425,   437,   359,   360,   434,
     435,   448,   446,   382,   366,   461,   456,     8,   466,   369,
     370,   462,    60,   473,    42,   475,    24,   380,    61,    62,
      48,    63,    64,    65,    66,   134,    11,    12,    67,    68,
      69,   213,   108,   109,   110,   111,   112,   113,   114,   449,
     116,   117,   118,   365,   297,   119,   120,   121,   122,   123,
     124,   237,   288,   445,   345,   384,   327,   409,   453,   411,
     472,   304,   412,     0,    70,    71,     0,     0,     0,    37,
       0,     0,   109,   110,   111,   112,   113,   114,   423,   116,
     117,   118,     0,     0,   119,   120,   121,   122,   123,   124,
       0,   432,     0,     0,     0,     0,     0,     0,     0,     0,
     438,   439,   440,   441,     0,   442,   443,   444,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,     0,
       0,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   458,   459,   460,     0,     0,     0,     0,     0,     0,
       0,     0,   184,     0,   467,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,     0,     0,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   268,     0,     0,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,     0,     0,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     457,     0,     0,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,     0,     0,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   427,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,     0,     0,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,     0,     0,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   109,   110,   111,   112,   113,   114,     0,   116,
       0,   118,     0,     0,   119,   120,   121,   122,   123,   124,
     109,   110,   111,   112,   113,   114,     0,   116,     0,     0,
       0,     0,   119,   120,   121,   122,   123,   124,   109,   110,
     111,   112,   113,   114,   109,   110,   111,   112,   113,   114,
     119,   120,   121,   122,   123,   124,     0,   120,   121,   122,
     123
};

static const yytype_int16 yycheck[] =
{
       3,    20,    19,    86,   103,     3,     8,    22,     3,    28,
     211,     3,    20,     8,     3,   210,   232,    20,   155,    22,
      28,    13,    35,   326,    22,    28,   285,    44,    20,    46,
      22,   144,    33,    22,    23,   209,    28,    39,   233,     3,
       8,     8,    31,   238,     8,     9,     3,   180,    27,   182,
      45,    30,     8,   269,    32,    68,    69,    10,    22,    23,
      28,     8,    29,   264,   367,    22,    23,   372,    46,    82,
      83,    84,    85,    27,    42,    88,    65,     4,    97,    92,
      93,    28,   219,   102,   103,   344,    42,   104,   262,    97,
       8,    45,     0,    30,    97,    27,    29,     8,   314,   102,
     103,   238,    29,   298,    68,    97,     4,   220,    65,   222,
     102,   103,    45,    45,    62,    52,    53,    54,   334,     4,
     135,    39,    69,    70,   319,    31,   431,   260,   141,   324,
     143,    29,   135,   134,   271,    27,   132,   135,   153,   142,
      46,   446,    29,   135,    29,    27,     8,    32,    30,    29,
     153,   288,    31,    31,    29,   153,   461,   256,    45,     8,
     156,   153,   158,    45,    31,    45,    27,    46,    46,    30,
     183,   108,    39,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,     5,     8,   330,    45,   214,
     313,    11,   315,   140,     4,     5,     6,     7,     8,    68,
      69,   214,   213,   226,    22,    23,   214,   266,   267,    46,
     157,   354,   214,    82,    83,    84,    85,   360,     8,    88,
      31,    31,   427,    92,    93,    39,     4,   256,    39,     7,
       8,   374,     4,   292,    31,     7,    31,   346,    16,     8,
     349,   268,    39,   256,   387,    46,   273,   274,    30,     4,
      28,     8,     7,     8,   256,    46,   283,    35,    45,   402,
      35,    16,   405,    38,    39,    40,   289,    28,   295,    45,
      46,    45,   141,    28,   143,    45,    46,    28,    45,     4,
      35,    28,     7,     8,    28,    28,    28,    32,   311,     8,
     383,    16,    28,   316,   317,     8,   439,    30,   441,    45,
     323,    35,    30,    28,   447,   328,   329,    45,     8,     8,
      35,   340,     8,   336,   183,   458,    45,   346,     5,     5,
     349,    30,   347,    27,   467,   350,    46,   340,     8,   276,
       4,     8,     8,   346,   347,    45,   349,   350,   340,   347,
       8,     8,   350,    27,   346,   347,    27,   349,   350,    31,
      28,    46,    31,   376,    46,   378,    31,   226,   381,     4,
       5,     6,     7,     8,    28,    31,     8,   394,    33,   396,
       8,     8,    45,    33,   397,   468,     4,     5,     6,     7,
       8,   408,    45,    45,    45,    33,    31,   410,    35,    36,
      37,    38,    39,    40,    45,    45,   419,   420,   421,   422,
      21,   424,   425,   426,    45,    45,    45,     8,     8,    45,
     437,    35,    36,    37,    38,    39,    40,   364,    45,    45,
     289,     8,    45,    45,    48,    49,    45,   450,   451,   452,
     457,    45,    31,    31,    64,    45,    45,   466,    46,    12,
     463,    45,   311,    63,    28,    63,    13,   316,   317,    45,
      45,    66,    46,   466,   323,    46,    28,     3,    28,   328,
     329,    67,     8,    31,   466,    31,     6,   336,    14,    15,
      28,    17,    18,    19,    20,    57,    22,    23,    24,    25,
      26,   136,    34,    35,    36,    37,    38,    39,    40,   436,
      42,    43,    44,   321,   254,    47,    48,    49,    50,    51,
      52,   157,   239,   427,   296,   341,   279,   376,   442,   378,
     469,   259,   381,    -1,    60,    61,    -1,    -1,    -1,    65,
      -1,    -1,    35,    36,    37,    38,    39,    40,   397,    42,
      43,    44,    -1,    -1,    47,    48,    49,    50,    51,    52,
      -1,   410,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     419,   420,   421,   422,    -1,   424,   425,   426,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    -1,
      -1,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,   450,   451,   452,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    31,    -1,   463,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    -1,    -1,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    31,    -1,    -1,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    -1,    -1,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      31,    -1,    -1,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    -1,    -1,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    -1,    -1,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    -1,    -1,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    35,    36,    37,    38,    39,    40,    -1,    42,
      -1,    44,    -1,    -1,    47,    48,    49,    50,    51,    52,
      35,    36,    37,    38,    39,    40,    -1,    42,    -1,    -1,
      -1,    -1,    47,    48,    49,    50,    51,    52,    35,    36,
      37,    38,    39,    40,    35,    36,    37,    38,    39,    40,
      47,    48,    49,    50,    51,    52,    -1,    48,    49,    50,
      51
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    10,    72,    73,     5,    11,    75,     0,     3,     8,
       9,    22,    23,    68,    76,    77,    82,    86,    98,    99,
     111,   155,   158,   160,    73,    74,     8,   160,    62,    83,
      27,    80,     8,    81,    29,    93,    31,    65,    86,   100,
     136,   144,   160,    76,     8,    45,     8,    84,   100,     4,
       7,     8,    16,    28,    35,    95,    97,    46,    79,    80,
       8,    14,    15,    17,    18,    19,    20,    24,    25,    26,
      60,    61,    85,    86,    87,    97,   102,   108,   112,   113,
     116,   120,   128,   131,   137,   138,   144,   146,   150,   151,
     152,   154,   158,   159,   160,     8,    31,    46,    39,   143,
       8,     8,    93,    93,    31,    95,    95,    95,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    96,     8,    82,    45,    46,    78,    69,    70,
      28,    45,    28,    45,    28,    28,    95,   115,    85,    85,
      28,    28,    32,    94,     8,    92,   127,    27,    88,    91,
      28,    85,    85,    85,    85,   143,    85,    85,    85,     8,
      30,   101,   134,    86,   136,     8,    39,    45,    86,   136,
     156,   160,   156,    93,    31,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    30,   126,
     129,    80,    76,    81,    45,     8,     8,    95,    85,     8,
      45,    86,   114,    85,   115,     8,    45,     5,   117,     5,
     121,    76,    91,   129,     8,    95,   105,   108,   129,    46,
      90,     4,     5,     6,     7,     8,    31,   109,   110,     8,
     141,     8,     4,   130,     8,     8,    45,    94,     8,    94,
      85,   130,   126,    78,    80,    76,    27,    27,    31,    91,
     115,     8,   115,    31,    31,    85,    46,   118,    31,    46,
     122,    31,    90,    27,    45,    28,    91,     8,    92,    45,
     104,    31,    46,    27,    45,    27,    33,   101,   129,   135,
     156,     8,   157,     8,   157,    94,    33,   130,    78,   110,
     110,    93,    90,    45,    91,    45,    45,    93,    93,     8,
      95,   119,   124,    45,     8,    42,   123,   124,    45,    45,
      93,    31,   109,    45,    91,    85,    45,   103,   110,     8,
      28,    42,   142,   145,    93,   135,    45,    45,    46,    45,
      45,    33,    45,    45,    85,    45,   115,    90,   115,    85,
      85,    21,   147,   125,   126,   118,    85,     8,   122,    85,
      85,     4,    93,    94,   132,   133,   107,    31,    89,    90,
      85,    45,    86,   144,   142,   140,    45,   109,   156,    76,
       8,   156,    76,    94,    31,    45,    31,    94,     4,     7,
     149,    64,   148,    95,   122,   132,    45,    94,    46,    85,
     106,    85,    85,   143,   139,    45,    94,    12,   153,    45,
      93,    45,    93,    85,    63,    63,    94,    33,    94,    45,
       4,    93,    85,    31,    45,    45,    28,    13,    85,    85,
      85,    85,    85,    85,    85,   125,    46,   132,    66,    95,
      93,    94,    94,   147,   132,    94,    28,    31,    85,    85,
      85,    46,    67,    93,    94,   132,    28,    85,   144,    94,
      31,   143,   153,    31,    31,    31
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
#line 439 ".\\semanticAnalysis.y"
    {printf("Syntax is Correct\n");return;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 452 ".\\semanticAnalysis.y"
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

  case 22:

/* Line 1455 of yacc.c  */
#line 463 ".\\semanticAnalysis.y"
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

  case 46:

/* Line 1455 of yacc.c  */
#line 484 ".\\semanticAnalysis.y"
    {
            strcpy(typeBuffer,(yyvsp[(1) - (1)].type));
            (yyval.type)=malloc(strlen((yyvsp[(1) - (1)].type))+1);
            strcpy((yyval.type),(yyvsp[(1) - (1)].type));
        }
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 491 ".\\semanticAnalysis.y"
    {dimit = 0;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 491 ".\\semanticAnalysis.y"
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

  case 55:

/* Line 1455 of yacc.c  */
#line 512 ".\\semanticAnalysis.y"
    {
    if(strcmp(forFunc->dataType,"void")==0){
        char const errorMessage[100]="Void Function Does not return anything";
        int a=yyerror(errorMessage);
        return -1;
    }
}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 520 ".\\semanticAnalysis.y"
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

  case 58:

/* Line 1455 of yacc.c  */
#line 532 ".\\semanticAnalysis.y"
    {scope++;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 533 ".\\semanticAnalysis.y"
    {deleteDMT(scope);scope--;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 562 ".\\semanticAnalysis.y"
    {dimit = 0;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 563 ".\\semanticAnalysis.y"
    {dimit = 0;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 566 ".\\semanticAnalysis.y"
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

  case 94:

/* Line 1455 of yacc.c  */
#line 582 ".\\semanticAnalysis.y"
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

  case 95:

/* Line 1455 of yacc.c  */
#line 593 ".\\semanticAnalysis.y"
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
#line 604 ".\\semanticAnalysis.y"
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

  case 97:

/* Line 1455 of yacc.c  */
#line 637 ".\\semanticAnalysis.y"
    {
                    struct SymbolTableEntry*new_entry = insertIdentifier(ptrBuf,CLASS[3],(yyvsp[(3) - (3)].type),pointerLen,yylinenumber,scope+1);
                    PD[noOfParameters]=pointerLen;
                    strcpy(PL[noOfParameters],(yyvsp[(3) - (3)].type));
                    PTL[noOfParameters]='p';
                    noOfParameters++;
                }
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 644 ".\\semanticAnalysis.y"
    {
                    struct SymbolTableEntry*new_entry = insertIdentifier(ptrBuf,CLASS[3],(yyvsp[(1) - (1)].type),pointerLen,yylinenumber,scope+1);
                    PD[noOfParameters]=pointerLen;
                    strcpy(PL[noOfParameters],(yyvsp[(1) - (1)].type));
                    PTL[noOfParameters]='p';
                    noOfParameters++;
                }
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 651 ".\\semanticAnalysis.y"
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

  case 100:

/* Line 1455 of yacc.c  */
#line 671 ".\\semanticAnalysis.y"
    {
    (yyval.type)=malloc(strlen("array")+1);strcpy((yyval.type),"array");

    }
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 674 ".\\semanticAnalysis.y"
    {(yyval.type)=malloc(strlen("variable")+1);strcpy((yyval.type),"variable");}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 677 ".\\semanticAnalysis.y"
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

  case 104:

/* Line 1455 of yacc.c  */
#line 711 ".\\semanticAnalysis.y"
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

  case 106:

/* Line 1455 of yacc.c  */
#line 757 ".\\semanticAnalysis.y"
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

  case 108:

/* Line 1455 of yacc.c  */
#line 791 ".\\semanticAnalysis.y"
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

  case 110:

/* Line 1455 of yacc.c  */
#line 836 ".\\semanticAnalysis.y"
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

  case 111:

/* Line 1455 of yacc.c  */
#line 853 ".\\semanticAnalysis.y"
    {
    strcpy(PL[noOfParameters],(yyvsp[(1) - (1)].type));
    PTL[noOfParameters]=pt;
    noOfParameters++;
}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 858 ".\\semanticAnalysis.y"
    {
            strcpy(PL[noOfParameters],(yyvsp[(3) - (3)].type));
            PTL[noOfParameters]=pt;
            noOfParameters++;
        }
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 863 ".\\semanticAnalysis.y"
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

  case 114:

/* Line 1455 of yacc.c  */
#line 891 ".\\semanticAnalysis.y"
    {(yyval.type)=malloc(strlen((yyvsp[(1) - (1)].type))+1);strcpy((yyval.type),(yyvsp[(1) - (1)].type));pt='v';parD[parDi++]=0;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 892 ".\\semanticAnalysis.y"
    {(yyval.type)=malloc(strlen((yyvsp[(1) - (1)].type))+1);strcpy((yyval.type),(yyvsp[(1) - (1)].type));pt='v';parD[parDi++]=0;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 893 ".\\semanticAnalysis.y"
    {(yyval.type)=malloc(strlen((yyvsp[(1) - (1)].type))+1);strcpy((yyval.type),(yyvsp[(1) - (1)].type));pt='v';parD[parDi++]=0;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 894 ".\\semanticAnalysis.y"
    {(yyval.type)=malloc(strlen((yyvsp[(1) - (1)].type))+1);strcpy((yyval.type),(yyvsp[(1) - (1)].type));pt='v';parD[parDi++]=0;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 896 ".\\semanticAnalysis.y"
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

  case 147:

/* Line 1455 of yacc.c  */
#line 960 ".\\semanticAnalysis.y"
    {ID_dim++;}
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 962 ".\\semanticAnalysis.y"
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

  case 149:

/* Line 1455 of yacc.c  */
#line 976 ".\\semanticAnalysis.y"
    {struct SymbolTableEntry* temp = insertArray(IDBuffer,CLASS[2],typeBuffer,dimit,yylinenumber,scope,dimbuffer);dimit = 0;}
    break;

  case 152:

/* Line 1455 of yacc.c  */
#line 979 ".\\semanticAnalysis.y"
    {dimbuffer[dimit++] = intval;}
    break;

  case 168:

/* Line 1455 of yacc.c  */
#line 994 ".\\semanticAnalysis.y"
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

  case 170:

/* Line 1455 of yacc.c  */
#line 1010 ".\\semanticAnalysis.y"
    {if(strcmp((yyvsp[(3) - (6)].type),(yyvsp[(6) - (6)].type))!=0){
    char message[30]="Variable Types dont Match";
        int res=yyerror(message);
        return -1;}}
    break;

  case 172:

/* Line 1455 of yacc.c  */
#line 1013 ".\\semanticAnalysis.y"
    {if(strcmp((yyvsp[(3) - (5)].type),(yyvsp[(5) - (5)].type))!=0){
    char message[30]="Variable Types dont Match";
        int res=yyerror(message);
        return -1;
}}
    break;

  case 175:

/* Line 1455 of yacc.c  */
#line 1019 ".\\semanticAnalysis.y"
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

  case 176:

/* Line 1455 of yacc.c  */
#line 1033 ".\\semanticAnalysis.y"
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

  case 177:

/* Line 1455 of yacc.c  */
#line 1045 ".\\semanticAnalysis.y"
    {  
     pointerLen++;
}
    break;



/* Line 1455 of yacc.c  */
#line 3137 "y.tab.c"
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
#line 1078 ".\\semanticAnalysis.y"


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
