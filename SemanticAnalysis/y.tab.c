
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

    #include <string.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #define TABLE_SIZE 1003
    #define MAX_SYMBOLS 1000000

    //Scope Number
    int scope=1; //Scope of Global Variables = 1
    int stIterator=0;


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

        new_entry->paraTypes=NULL;
        new_entrydst->paraTypes=NULL;

        new_entry->tail = new_entry->head;
        new_entrydst->tail = new_entrydst->head;

        new_entry->dimSize=(int *)malloc(sizeof(int)*dimension);
        for(int i=0;i<dimension;i++){
            new_entry->dimSize[i]=dimList[i];
        }
        new_entrydst->dimSize=(int *)malloc(sizeof(int)*dimension);
        for(int i=0;i<dimension;i++){
            new_entrydst->dimSize[i]=dimList[i];
        }

        new_entry->noOfParams=-1;
        new_entrydst->noOfParams=-1;
        new_entry->paraList=NULL;
        new_entrydst->paraList=NULL;

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

    //start globalVarDec startGlobal DG optionsG main mainParameters start1 varDec D options header newHeader file Exp function_declaration function_call function_defn parameter_list choice item params for while varDecF ExpF print printExpr printArguments printContent scanf scanfArguments scanfContent scanfExpr dimension BOX BALANCED_BRACK arrayElement arrayInitial arrayDeclr arrayAsAParameter arrayParams_unend higherDimention pointerAsAParameter PTR_DECLR PTR_EXP PTR_INITIAL PTR_STAR PTR_TYPE switch switchcase default comp ifElseLadder matched S elif unmatched userDefDataType userTypeDeclaration userTypeDefination userTypeInitialization userTypeObj userTypeParams


/* Line 189 of yacc.c  */
#line 452 "y.tab.c"

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
#line 379 ".\\semanticAnalysis.y"

    char * value;
    char * type;



/* Line 214 of yacc.c  */
#line 635 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 647 "y.tab.c"

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
#define YYLAST   704

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  71
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  76
/* YYNRULES -- Number of rules.  */
#define YYNRULES  198
/* YYNRULES -- Number of states.  */
#define YYNSTATES  450

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
     112,   115,   116,   118,   125,   126,   133,   138,   139,   142,
     143,   150,   151,   156,   157,   159,   161,   163,   167,   171,
     175,   179,   183,   187,   191,   195,   199,   203,   206,   209,
     212,   216,   220,   224,   228,   232,   236,   240,   244,   248,
     252,   256,   260,   264,   268,   270,   272,   274,   280,   284,
     287,   293,   297,   299,   303,   305,   306,   307,   315,   316,
     323,   325,   327,   331,   333,   335,   337,   339,   341,   343,
     355,   365,   377,   387,   396,   403,   409,   414,   416,   417,
     424,   426,   429,   433,   436,   438,   440,   447,   450,   455,
     459,   463,   466,   468,   470,   473,   478,   482,   487,   492,
     496,   505,   513,   515,   518,   526,   533,   539,   543,   548,
     554,   556,   560,   564,   566,   567,   571,   576,   584,   591,
     598,   601,   603,   606,   608,   610,   623,   635,   645,   651,
     652,   656,   657,   659,   661,   663,   665,   667,   680,   689,
     690,   699,   709,   718,   724,   728,   734,   739,   742,   747,
     749,   753,   754,   759,   763,   772,   779,   786,   788
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      72,     0,    -1,    73,    76,    80,    -1,    10,    75,    74,
      -1,    73,    -1,    -1,     5,    -1,    11,    -1,    94,    -1,
      77,    -1,   141,    -1,   144,    76,    -1,    -1,    83,     8,
      79,    78,    45,    76,    -1,     8,    79,    78,    45,    76,
      -1,    46,     8,    79,    78,    -1,    -1,    27,    93,    -1,
      -1,    62,    81,    31,    91,    82,    92,    -1,    96,    -1,
      -1,    84,    -1,   109,    -1,   113,    -1,    98,    -1,   106,
      -1,   105,    -1,    24,   108,    45,    82,    -1,    18,    45,
      82,    -1,    15,    45,    82,    -1,    25,    82,    -1,    26,
      82,    -1,   119,    82,    -1,   121,    82,    -1,   132,    -1,
     128,    82,    -1,   127,    82,    -1,   136,    82,    -1,   144,
      82,    -1,   145,    82,    -1,    -1,     3,    -1,    83,    90,
      87,    86,    45,    82,    -1,    -1,     8,    85,    87,    86,
      45,    82,    -1,    46,    90,    87,    86,    -1,    -1,    27,
      93,    -1,    -1,    27,     8,    88,    28,   102,    31,    -1,
      -1,     8,    89,    28,    31,    -1,    -1,     8,    -1,    29,
      -1,    32,    -1,    28,    93,    31,    -1,    93,    36,    93,
      -1,    93,    37,    93,    -1,    93,    39,    93,    -1,    93,
      38,    93,    -1,    93,    40,    93,    -1,    93,    41,    93,
      -1,    93,    34,    93,    -1,    93,    44,    93,    -1,    93,
      42,    93,    -1,    93,    35,    -1,    35,    93,    -1,    16,
      93,    -1,    93,    43,    93,    -1,    93,    47,    93,    -1,
      93,    48,    93,    -1,    93,    49,    93,    -1,    93,    50,
      93,    -1,    93,    51,    93,    -1,    93,    52,    93,    -1,
      93,    53,    93,    -1,    93,    54,    93,    -1,    93,    55,
      93,    -1,    93,    56,    93,    -1,    93,    57,    93,    -1,
      93,    58,    93,    -1,    93,    59,    93,    -1,     8,    -1,
       4,    -1,     7,    -1,    95,    91,    82,    92,    76,    -1,
     104,    96,    31,    -1,   104,    31,    -1,    96,    46,    83,
       8,    97,    -1,    96,    46,   126,    -1,   126,    -1,    83,
       8,    97,    -1,   124,    -1,    -1,    -1,   101,    28,   102,
      31,    99,    45,    82,    -1,    -1,   101,    28,    31,   100,
      45,    82,    -1,     8,    -1,   103,    -1,   102,    46,   103,
      -1,     8,    -1,     4,    -1,     5,    -1,     7,    -1,     6,
      -1,     9,    -1,    17,    28,   107,   108,    45,   108,    31,
      91,    82,    92,    82,    -1,    17,    28,   107,   108,    45,
     108,    31,    45,    82,    -1,    17,    28,    45,   108,    45,
     108,    31,    91,    82,    92,    82,    -1,    17,    28,    45,
     108,    45,   108,    31,    45,    82,    -1,    19,    28,   108,
      31,    91,    82,    92,    82,    -1,    19,    28,   108,    31,
      45,    82,    -1,    83,     8,    87,    86,    45,    -1,     8,
      87,    86,    45,    -1,    93,    -1,    -1,    60,    28,   110,
      31,    45,    82,    -1,     5,    -1,     5,   111,    -1,    46,
     112,   111,    -1,    46,   112,    -1,    93,    -1,   117,    -1,
      61,    28,   114,    31,    45,    82,    -1,     5,   115,    -1,
      46,    42,     8,   115,    -1,    46,    42,     8,    -1,    46,
     116,   115,    -1,    46,   116,    -1,     8,    -1,   117,    -1,
       8,   118,    -1,    30,    93,    33,   118,    -1,    30,    93,
      33,    -1,    83,     8,   120,    45,    -1,   120,    30,     4,
      33,    -1,    30,     4,    33,    -1,    83,     8,   120,    27,
      91,   122,    92,    45,    -1,    83,     8,   120,    27,    91,
      92,    45,    -1,   123,    -1,   123,    46,    -1,   123,    46,
      91,   122,    92,    46,   122,    -1,   123,    46,    91,   122,
      92,    46,    -1,   123,    46,    91,   122,    92,    -1,    91,
     122,    92,    -1,    91,   122,    92,    46,    -1,    91,   122,
      92,    46,   122,    -1,     4,    -1,   123,    46,     4,    -1,
      30,    33,   125,    -1,   120,    -1,    -1,   130,   129,     8,
      -1,   130,   129,     8,    45,    -1,   130,   129,     8,    27,
      42,     8,    45,    -1,   130,   129,     8,    27,     8,    45,
      -1,   130,   129,     8,    27,   131,    45,    -1,   129,    39,
      -1,    39,    -1,   146,     8,    -1,    83,    -1,    65,    -1,
      28,   130,   129,    31,    66,    28,    67,    28,   130,   129,
      31,    31,    -1,    28,   130,   129,    31,    66,    28,    67,
      28,   130,    31,    31,    -1,    20,    28,     8,    31,    91,
     133,   134,    92,    82,    -1,    21,   135,    63,    82,   133,
      -1,    -1,    64,    63,    82,    -1,    -1,     7,    -1,     4,
      -1,   137,    -1,   138,    -1,   140,    -1,    14,    28,    93,
      31,    91,    82,    92,   139,    13,    91,    82,    92,    -1,
      12,    28,    93,    31,    91,    82,    92,   139,    -1,    -1,
      14,    28,    93,    31,    91,    82,    92,   139,    -1,    68,
     146,     8,    91,   142,    92,   143,    45,    76,    -1,   146,
       8,    91,   142,    92,   143,    45,    76,    -1,    83,     8,
     125,    45,   142,    -1,   126,    45,   142,    -1,   146,     8,
       8,    45,   142,    -1,    83,     8,   125,    45,    -1,   126,
      45,    -1,   146,     8,     8,    45,    -1,     8,    -1,   143,
      46,     8,    -1,    -1,   146,     8,     8,    45,    -1,     8,
       8,    45,    -1,   146,     8,     8,    27,    91,   102,    92,
      45,    -1,     8,    69,     8,    27,   103,    45,    -1,     8,
      70,     8,    27,   103,    45,    -1,    22,    -1,    23,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   406,   406,   407,   408,   408,   409,   409,   411,   411,
     411,   411,   411,   413,   414,   415,   415,   416,   416,   418,
     419,   419,   421,   421,   421,   421,   421,   421,   422,   422,
     422,   423,   423,   423,   423,   424,   424,   424,   424,   425,
     425,   425,   427,   432,   433,   433,   445,   445,   446,   446,
     446,   456,   456,   466,   468,   480,   481,   483,   484,   485,
     486,   487,   488,   489,   490,   491,   492,   493,   494,   495,
     496,   497,   498,   499,   500,   501,   502,   503,   504,   505,
     506,   507,   508,   509,   510,   521,   521,   523,   524,   534,
     544,   573,   574,   575,   591,   591,   594,   594,   629,   629,
     665,   682,   687,   692,   714,   715,   716,   717,   719,   753,
     754,   755,   756,   758,   759,   761,   762,   764,   764,   766,
     767,   768,   769,   770,   771,   771,   773,   774,   775,   776,
     777,   778,   779,   779,   781,   782,   782,   784,   785,   785,
     786,   786,   787,   788,   789,   790,   791,   792,   793,   794,
     795,   795,   797,   798,   798,   800,   802,   803,   803,   803,
     804,   804,   805,   805,   805,   806,   807,   809,   810,   810,
     811,   811,   812,   812,   814,   815,   815,   816,   817,   817,
     818,   820,   820,   821,   822,   823,   824,   825,   826,   827,
     827,   827,   828,   828,   829,   830,   831,   833,   833
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
  "main", "mainParameters", "start1", "type", "varDec", "$@1", "D",
  "options", "$@2", "$@3", "id", "open_flower", "close_flower", "Exp",
  "function_defn", "function_declaration", "parameter_list", "choice",
  "function_call", "$@4", "$@5", "funName", "params", "item", "fun_start",
  "for", "while", "varDecF", "ExpF", "print", "printExpr",
  "printArguments", "printContent", "scanf", "scanfExpr", "scanfArguments",
  "scanfContent", "arrayElement", "dimension", "arrayDeclr", "BOX",
  "arrayInitial", "BALANCED_BRACK", "arrayParams_unend",
  "arrayAsAParameter", "higherDimention", "pointerAsAParameter",
  "PTR_DECLR", "PTR_INITIAL", "PTR_STAR", "PTR_TYPE", "PTR_EXP", "switch",
  "switchcase", "default", "comp", "ifElseLadder", "S", "matched", "elif",
  "unmatched", "userTypeDefination", "userTypeParams", "userTypeObj",
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
      82,    82,    83,    84,    85,    84,    86,    86,    87,    88,
      87,    89,    87,    87,    90,    91,    92,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    94,    95,    95,
      96,    96,    96,    96,    97,    97,    99,    98,   100,    98,
     101,   102,   102,   103,   103,   103,   103,   103,   104,   105,
     105,   105,   105,   106,   106,   107,   107,   108,   108,   109,
     110,   110,   111,   111,   112,   112,   113,   114,   115,   115,
     115,   115,   116,   116,   117,   118,   118,   119,   120,   120,
     121,   121,   122,   122,   122,   122,   122,   122,   122,   122,
     123,   123,   124,   125,   125,   126,   127,   128,   128,   128,
     129,   129,   130,   130,   130,   131,   131,   132,   133,   133,
     134,   134,   135,   135,   136,   137,   137,   138,   139,   139,
     140,   141,   141,   142,   142,   142,   142,   142,   142,   143,
     143,   143,   144,   144,   145,   145,   145,   146,   146
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     3,     1,     0,     1,     1,     1,     1,
       1,     2,     0,     6,     5,     4,     0,     2,     0,     6,
       1,     0,     1,     1,     1,     1,     1,     1,     4,     3,
       3,     2,     2,     2,     2,     1,     2,     2,     2,     2,
       2,     0,     1,     6,     0,     6,     4,     0,     2,     0,
       6,     0,     4,     0,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     1,     1,     1,     5,     3,     2,
       5,     3,     1,     3,     1,     0,     0,     7,     0,     6,
       1,     1,     3,     1,     1,     1,     1,     1,     1,    11,
       9,    11,     9,     8,     6,     5,     4,     1,     0,     6,
       1,     2,     3,     2,     1,     1,     6,     2,     4,     3,
       3,     2,     1,     1,     2,     4,     3,     4,     4,     3,
       8,     7,     1,     2,     7,     6,     5,     3,     4,     5,
       1,     3,     3,     1,     0,     3,     4,     7,     6,     6,
       2,     1,     2,     1,     1,    12,    11,     9,     5,     0,
       3,     0,     1,     1,     1,     1,     1,    12,     8,     0,
       8,     9,     8,     5,     3,     5,     4,     2,     4,     1,
       3,     0,     4,     3,     8,     6,     6,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,    12,     6,     7,     5,     1,    42,    18,
     108,   197,   198,     0,     0,     9,     0,     8,     0,     0,
      10,    12,     0,     4,     3,     0,     0,    16,     0,    21,
       2,    18,    55,    41,    89,   164,   163,     0,    92,     0,
       0,    11,     0,   193,    85,    86,    84,     0,     0,     0,
      17,     0,     0,     0,     0,    20,    16,    44,     0,     0,
       0,     0,     0,     0,   118,    41,    41,     0,     0,     0,
     163,    22,    25,     0,    27,    26,    23,    24,    41,    41,
      41,    41,     0,    35,    41,   174,   175,   176,    41,    41,
       0,    95,    88,     0,   161,     0,   162,     0,     0,    69,
       0,    68,     0,    67,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    18,    12,     0,     0,
       0,     0,     0,    53,     0,    41,     0,    41,   118,     0,
     117,     0,    31,    32,     0,     0,    56,    12,    54,    53,
       0,    33,    34,    37,    36,     0,    38,    39,    40,   162,
       0,    93,    94,   163,    91,   155,   160,   192,   163,     0,
       0,     0,    57,    64,    58,    59,    61,    60,    62,    63,
      66,    70,    65,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    16,    14,     0,    41,
      12,     0,     0,    51,     0,    47,     0,    30,    53,   118,
       0,   118,    29,     0,     0,    41,   120,     0,     0,     0,
      87,     0,     0,    47,   104,   105,   107,   106,   103,    98,
       0,   101,     0,     0,   154,    95,   154,   187,   191,   162,
      15,   191,     0,    13,     0,     0,     0,    84,    48,     0,
       0,     0,    47,     0,    53,     0,     0,     0,    28,     0,
     121,     0,     0,   127,     0,     0,     0,     0,   137,     0,
       0,    96,     0,     0,   156,     0,   153,   152,    90,     0,
     184,   189,     0,     0,     0,    19,     0,     0,     0,     0,
      54,    53,    41,    41,     0,   118,    47,   118,    41,    41,
     169,    84,   124,   123,   125,    41,   132,     0,   131,   133,
      41,   139,     0,     0,    41,    41,     0,   102,     0,     0,
       0,     0,     0,   186,    12,     0,   188,    12,   195,   196,
      52,     0,    47,    45,     0,   116,     0,     0,     0,   114,
       0,     0,   171,     0,   134,   122,   119,   129,   130,   126,
     150,     0,     0,     0,   142,   138,    43,    99,    41,   158,
     163,     0,     0,   159,     0,   183,   182,   190,   185,   181,
       0,    46,   179,     0,   115,     0,    41,   173,   172,     0,
       0,     0,     0,   128,     0,   141,     0,   143,    97,     0,
     157,     0,    50,     0,   180,    41,    41,    41,    41,   113,
      41,    41,    41,   136,   147,   140,   151,     0,     0,   194,
       0,     0,   112,     0,   110,     0,   169,   170,   167,   135,
     148,     0,     0,     0,    41,    41,    41,   168,   149,   146,
       0,     0,     0,   111,   109,   145,     0,    41,   177,   144,
       0,     0,     0,   179,     0,     0,   178,   166,     0,   165
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    24,     6,    14,    15,    52,    27,    30,
      54,    69,    70,    71,   133,   250,   205,   289,   246,   149,
     351,   147,   140,    17,    18,    37,   161,    72,   316,   270,
      73,   230,   231,    19,    74,    75,   211,   141,    76,   217,
     260,   303,    77,   219,   263,   308,   304,   344,    78,   276,
      79,   353,   354,   162,   277,   169,    80,    81,    95,    82,
     321,    83,   342,   381,   379,    84,    85,    86,   394,    87,
      20,   170,   282,    88,    89,    90
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -342
static const yytype_int16 yypact[] =
{
      10,   121,    42,    32,  -342,  -342,    10,  -342,  -342,    83,
    -342,  -342,  -342,   183,   -38,  -342,   148,  -342,   160,    55,
    -342,    32,   185,  -342,  -342,   146,   188,   161,   201,    48,
    -342,   184,  -342,   207,  -342,  -342,   206,    29,  -342,   180,
     220,  -342,    24,  -342,  -342,  -342,  -342,   188,   188,   188,
     562,   228,   195,   160,   213,   200,   161,    59,   223,   210,
     229,   211,   230,   235,   188,   207,   207,   236,   237,   238,
     261,  -342,  -342,   243,  -342,  -342,  -342,  -342,   207,   207,
     207,   207,   180,  -342,   207,  -342,  -342,  -342,   207,   207,
     265,   245,  -342,    48,  -342,    22,  -342,   233,    48,   244,
     451,  -342,   188,  -342,   188,   188,   188,   188,   188,   188,
     188,   188,   188,   188,   188,   188,   188,   188,   188,   188,
     188,   188,   188,   188,   188,   188,   184,    32,    48,   160,
     241,   272,   279,    91,   188,   207,    14,   207,   188,   280,
     562,   247,  -342,  -342,   285,   286,  -342,    32,   263,    91,
     339,  -342,  -342,  -342,  -342,    30,  -342,  -342,  -342,   287,
     264,  -342,  -342,   288,  -342,  -342,  -342,  -342,   292,   256,
     238,   295,  -342,   403,   112,   112,   244,   244,   244,   611,
     647,   629,   353,   653,   376,   376,   314,   314,   653,   588,
     588,   588,   588,   562,   562,   562,   161,  -342,   238,   207,
      32,   277,   278,  -342,   231,   262,   480,  -342,    91,   188,
     299,   188,  -342,   281,   282,   207,   271,   291,   273,   294,
    -342,   306,    62,   262,  -342,  -342,  -342,  -342,  -342,  -342,
      92,  -342,    95,   104,   263,   245,   263,    48,   310,   318,
    -342,   310,   238,  -342,   424,   424,   300,   301,   562,   322,
     293,   160,   262,   296,    91,   303,    98,   160,  -342,   246,
    -342,   311,    15,  -342,   312,   304,   160,   329,  -342,   313,
     319,  -342,   424,     6,  -342,   160,   336,  -342,  -342,   323,
    -342,  -342,   172,   324,   203,  -342,   326,   327,   309,   346,
    -342,    91,   207,   207,   330,   188,   262,   188,   207,   207,
     355,   337,   562,   271,  -342,   207,   337,   370,   273,  -342,
     207,  -342,   113,   354,   207,   207,   349,  -342,   361,    48,
     390,   373,   424,    48,    32,   411,    48,    32,  -342,  -342,
    -342,   424,   262,  -342,   238,  -342,   389,   377,   394,  -342,
     238,   150,   362,   188,  -342,  -342,  -342,   273,  -342,  -342,
    -342,    27,   388,   238,   398,  -342,  -342,  -342,   207,  -342,
    -342,   180,   391,  -342,   154,  -342,  -342,  -342,  -342,  -342,
     157,  -342,   422,   101,  -342,   108,   207,  -342,  -342,   372,
     386,   238,   536,  -342,   238,  -342,   412,    80,  -342,    13,
    -342,   414,  -342,   432,   448,   207,   207,   207,   207,  -342,
     207,   207,   207,   337,   416,  -342,  -342,    27,   397,  -342,
     188,   160,  -342,   238,  -342,   238,   355,  -342,  -342,  -342,
      27,   238,   437,   509,   207,   207,   207,  -342,  -342,   421,
     401,   160,   238,  -342,  -342,    27,   441,   207,  -342,  -342,
      48,   238,    54,   422,   439,   163,  -342,  -342,   440,  -342
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -342,  -342,   466,  -342,  -342,   -13,  -342,   -55,   -18,  -342,
    -342,   -16,    -3,  -342,  -342,  -216,  -106,  -342,  -342,   224,
     -14,    43,    56,  -342,  -342,   445,   242,  -342,  -342,  -342,
    -342,  -234,  -198,  -342,  -342,  -342,  -342,  -113,  -342,  -342,
     173,  -342,  -342,  -342,  -302,  -342,   216,    76,  -342,   332,
    -342,  -341,  -342,  -342,   260,   -10,  -342,  -342,   -77,   -17,
    -342,  -342,    65,  -342,  -342,  -342,  -342,  -342,    40,  -342,
    -342,  -125,   284,    12,  -342,     8
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -101
static const yytype_int16 yytable[] =
{
      16,   130,    39,   198,    33,   155,   348,   269,    41,    38,
     384,    22,    39,    56,   318,    21,    36,     8,    16,    38,
       1,    28,   208,   306,    29,   213,    36,    40,    98,    22,
     165,   350,    97,    21,   319,     8,   294,    40,   232,   128,
       9,    10,     7,   223,   408,   383,   286,   287,   320,   142,
     143,     8,   166,    32,    11,    12,    32,   307,     8,   209,
      92,   166,   151,   152,   153,   154,   421,    25,   156,   166,
      11,    12,   157,   158,   317,    93,    39,    11,    12,   428,
     337,    39,    50,   164,   406,   444,    34,  -100,   364,   266,
     163,    25,   267,    94,   439,   168,   253,   370,   255,   203,
      13,    40,   252,    99,   100,   101,   171,   268,   196,    32,
      26,    39,   280,    35,   197,   199,   371,   350,   204,   207,
      35,   212,   273,   271,    16,   168,     4,    32,   131,   132,
      32,   275,     5,   210,   220,    22,   171,    32,   272,    21,
     274,   240,    32,   298,    16,   146,   395,   103,   296,   167,
     106,   107,   108,   397,   377,    22,    31,   378,   173,    21,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   336,   242,   338,   332,   146,   243,   392,    32,
     206,    43,    44,    42,   448,    45,    46,    16,   365,   258,
     272,   368,   166,   272,    47,    11,    12,    51,    22,    53,
       8,    26,    21,   238,    91,    57,    48,   324,   325,    94,
      39,    58,    59,    49,    60,    61,    62,    63,    96,    11,
      12,    64,    65,    66,   168,    44,   126,   293,    45,   247,
     127,   241,   299,   300,   129,   171,    93,    47,   327,   325,
      44,   134,   312,    45,   301,   135,   137,   136,   138,    48,
     248,   322,    47,   139,   144,   145,    49,    67,    68,   148,
     146,   150,    35,   159,    48,   160,   333,   334,   167,   103,
     201,    49,   339,   340,   389,   285,   200,   202,   214,   346,
     216,   218,   215,   221,   349,   233,   235,   234,   356,   357,
     236,   237,   361,   239,   244,   245,    39,   254,   249,    39,
     265,   366,   256,   257,   369,   302,   360,   259,   281,   262,
     168,    16,   261,   168,    16,   264,   283,    40,   288,   -49,
     290,   171,    22,   313,   171,    22,    21,   311,   292,    21,
     330,   295,   388,   224,   225,   226,   227,   228,   297,   103,
     104,   105,   106,   107,   108,   352,   305,   310,   314,   396,
     399,   398,   114,   115,   315,   445,   267,   343,   323,   326,
     229,   328,   329,   407,   331,   335,   341,   372,   347,   412,
     413,   414,   415,   376,   416,   417,   418,   355,   103,   104,
     105,   106,   107,   108,   358,   110,   386,   424,   362,   382,
     113,   114,   115,   116,   117,   118,   359,   391,   432,   433,
     434,   103,   104,   105,   106,   107,   108,   437,   363,   367,
     373,   441,   374,   442,   402,   375,   380,   404,   224,   225,
     226,   227,   228,   385,   393,   400,   390,   360,   103,   104,
     105,   106,   107,   108,   387,   110,   111,   112,    40,   401,
     113,   114,   115,   116,   117,   118,   425,   405,   426,   409,
     410,   411,   420,   422,   429,   430,   423,   435,   436,   440,
     447,   449,    23,   291,    55,   438,   345,   278,   309,   419,
     222,   427,   172,   446,   443,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   279,     0,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   251,     0,     0,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   284,     0,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     431,     0,     0,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,     0,     0,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   403,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,     0,     0,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,     0,     0,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,     0,     0,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   102,   103,   104,   105,   106,
     107,   108,     0,   110,   111,   112,     0,     0,   113,   114,
     115,   116,   117,   118,   103,   104,   105,   106,   107,   108,
       0,   110,     0,   112,     0,     0,   113,   114,   115,   116,
     117,   118,   103,   104,   105,   106,   107,   108,   103,   104,
     105,   106,   107,   108,   113,   114,   115,   116,   117,   118,
       0,   114,   115,   116,   117
};

static const yytype_int16 yycheck[] =
{
       3,    56,    19,   128,    18,    82,   308,   223,    21,    19,
     351,     3,    29,    31,     8,     3,    19,     3,    21,    29,
      10,    13,     8,     8,    62,   138,    29,    19,    42,    21,
       8,     4,     8,    21,    28,     3,   252,    29,     8,    53,
       8,     9,     0,   149,    31,   347,   244,   245,    42,    65,
      66,     3,    39,    29,    22,    23,    29,    42,     3,    45,
      31,    39,    78,    79,    80,    81,   407,     8,    84,    39,
      22,    23,    88,    89,   272,    46,    93,    22,    23,   420,
     296,    98,    26,    93,     4,    31,    31,    28,   322,    27,
      93,     8,    30,    39,   435,    98,   209,   331,   211,     8,
      68,    93,   208,    47,    48,    49,    98,    45,   126,    29,
      27,   128,   237,    65,   127,   129,   332,     4,    27,   135,
      65,   137,    27,    31,   127,   128,     5,    29,    69,    70,
      29,    27,    11,   136,   147,   127,   128,    29,    46,   127,
      45,   196,    29,    45,   147,    32,    45,    35,   254,    45,
      38,    39,    40,    45,     4,   147,     8,     7,   102,   147,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   295,   199,   297,   291,    32,   200,    31,    29,
     134,    45,     4,     8,    31,     7,     8,   200,   323,   215,
      46,   326,    39,    46,    16,    22,    23,    46,   200,     8,
       3,    27,   200,   170,     8,     8,    28,    45,    46,    39,
     237,    14,    15,    35,    17,    18,    19,    20,     8,    22,
      23,    24,    25,    26,   237,     4,     8,   251,     7,     8,
      45,   198,   256,   257,    31,   237,    46,    16,    45,    46,
       4,    28,   266,     7,     8,    45,    45,    28,    28,    28,
     204,   275,    16,    28,    28,    28,    35,    60,    61,     8,
      32,    28,    65,     8,    28,    30,   292,   293,    45,    35,
       8,    35,   298,   299,   361,   242,    45,     8,     8,   305,
       5,     5,    45,    30,   310,     8,     8,    33,   314,   315,
       8,    45,   319,     8,    27,    27,   323,     8,    46,   326,
       4,   324,    31,    31,   327,   259,   319,    46,     8,    46,
     323,   324,    31,   326,   327,    31,     8,   319,    28,    28,
       8,   323,   324,     4,   326,   327,   324,    33,    45,   327,
      31,    45,   358,     4,     5,     6,     7,     8,    45,    35,
      36,    37,    38,    39,    40,   312,    45,    45,    45,   373,
     376,   375,    48,    49,    45,   442,    30,    30,    45,    45,
      31,    45,    45,   387,    28,    45,    21,   334,     8,   395,
     396,   397,   398,   340,   400,   401,   402,    33,    35,    36,
      37,    38,    39,    40,    45,    42,   353,   411,     8,   343,
      47,    48,    49,    50,    51,    52,    45,   364,   424,   425,
     426,    35,    36,    37,    38,    39,    40,   431,    45,     8,
      31,   437,    45,   440,   381,    31,    64,   384,     4,     5,
       6,     7,     8,    45,    12,    63,    45,   440,    35,    36,
      37,    38,    39,    40,    46,    42,    43,    44,   440,    63,
      47,    48,    49,    50,    51,    52,   413,    45,   415,    45,
      28,    13,    46,    66,   421,    28,   410,    46,    67,    28,
      31,    31,     6,   249,    29,   432,   303,   235,   262,   403,
     148,   416,    31,   443,   441,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,   236,    -1,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    31,    -1,    -1,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,   241,    -1,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      31,    -1,    -1,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    -1,    -1,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    -1,    -1,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    -1,    -1,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    -1,    -1,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    34,    35,    36,    37,    38,
      39,    40,    -1,    42,    43,    44,    -1,    -1,    47,    48,
      49,    50,    51,    52,    35,    36,    37,    38,    39,    40,
      -1,    42,    -1,    44,    -1,    -1,    47,    48,    49,    50,
      51,    52,    35,    36,    37,    38,    39,    40,    35,    36,
      37,    38,    39,    40,    47,    48,    49,    50,    51,    52,
      -1,    48,    49,    50,    51
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    10,    72,    73,     5,    11,    75,     0,     3,     8,
       9,    22,    23,    68,    76,    77,    83,    94,    95,   104,
     141,   144,   146,    73,    74,     8,    27,    79,   146,    62,
      80,     8,    29,    91,    31,    65,    83,    96,   126,   130,
     146,    76,     8,    45,     4,     7,     8,    16,    28,    35,
      93,    46,    78,     8,    81,    96,    79,     8,    14,    15,
      17,    18,    19,    20,    24,    25,    26,    60,    61,    82,
      83,    84,    98,   101,   105,   106,   109,   113,   119,   121,
     127,   128,   130,   132,   136,   137,   138,   140,   144,   145,
     146,     8,    31,    46,    39,   129,     8,     8,    91,    93,
      93,    93,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,     8,    45,    91,    31,
      78,    69,    70,    85,    28,    45,    28,    45,    28,    28,
      93,   108,    82,    82,    28,    28,    32,    92,     8,    90,
      28,    82,    82,    82,    82,   129,    82,    82,    82,     8,
      30,    97,   124,    83,   126,     8,    39,    45,    83,   126,
     142,   146,    31,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    79,    76,   142,    91,
      45,     8,     8,     8,    27,    87,    93,    82,     8,    45,
      83,   107,    82,   108,     8,    45,     5,   110,     5,   114,
      76,    30,   120,    87,     4,     5,     6,     7,     8,    31,
     102,   103,     8,     8,    33,     8,     8,    45,    92,     8,
      78,    92,    82,    76,    27,    27,    89,     8,    93,    46,
      86,    31,    87,   108,     8,   108,    31,    31,    82,    46,
     111,    31,    46,   115,    31,     4,    27,    30,    45,    86,
     100,    31,    46,    27,    45,    27,   120,   125,    97,   125,
     142,     8,   143,     8,   143,    92,   103,   103,    28,    88,
       8,    90,    45,    91,    86,    45,    87,    45,    45,    91,
      91,     8,    93,   112,   117,    45,     8,    42,   116,   117,
      45,    33,    91,     4,    45,    45,    99,   103,     8,    28,
      42,   131,    91,    45,    45,    46,    45,    45,    45,    45,
      31,    28,    87,    82,    82,    45,   108,    86,   108,    82,
      82,    21,   133,    30,   118,   111,    82,     8,   115,    82,
       4,    91,    92,   122,   123,    33,    82,    82,    45,    45,
      83,   130,     8,    45,   102,   142,    76,     8,   142,    76,
     102,    86,    92,    31,    45,    31,    92,     4,     7,   135,
      64,   134,    93,   115,   122,    45,    92,    46,    82,   129,
      45,    92,    31,    12,   139,    45,    91,    45,    91,    82,
      63,    63,    92,    33,    92,    45,     4,    91,    31,    45,
      28,    13,    82,    82,    82,    82,    82,    82,    82,   118,
      46,   122,    66,    93,    91,    92,    92,   133,   122,    92,
      28,    31,    82,    82,    82,    46,    67,    91,    92,   122,
      28,    82,   130,    92,    31,   129,   139,    31,    31,    31
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
#line 406 ".\\semanticAnalysis.y"
    {printf("Syntax is Correct\n");return;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 427 ".\\semanticAnalysis.y"
    {
            strcpy(typeBuffer,(yyvsp[(1) - (1)].type));
            (yyval.type)=malloc(strlen((yyvsp[(1) - (1)].type))+1);
            strcpy((yyval.type),(yyvsp[(1) - (1)].type));
        }
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 433 ".\\semanticAnalysis.y"
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

  case 49:

/* Line 1455 of yacc.c  */
#line 446 ".\\semanticAnalysis.y"
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

  case 51:

/* Line 1455 of yacc.c  */
#line 456 ".\\semanticAnalysis.y"
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

  case 54:

/* Line 1455 of yacc.c  */
#line 468 ".\\semanticAnalysis.y"
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

  case 55:

/* Line 1455 of yacc.c  */
#line 480 ".\\semanticAnalysis.y"
    {scope++;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 481 ".\\semanticAnalysis.y"
    {deleteDMT(scope);scope--;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 510 ".\\semanticAnalysis.y"
    {
        struct SymbolTableEntry * found=lookup((yyvsp[(1) - (1)].value),scope,false);
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

  case 88:

/* Line 1455 of yacc.c  */
#line 524 ".\\semanticAnalysis.y"
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

  case 89:

/* Line 1455 of yacc.c  */
#line 534 ".\\semanticAnalysis.y"
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

  case 90:

/* Line 1455 of yacc.c  */
#line 544 ".\\semanticAnalysis.y"
    {
    char flag;
    if(strcmp((yyvsp[(5) - (5)].type),"array")==0){
        flag='a';
    }
    else{
        flag='v';
    }
    char T[10];
    if(flag=='a'){
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
    else{
        struct SymbolTableEntry*new_entry = insertIdentifier((yyvsp[(4) - (5)].value),T,(yyvsp[(3) - (5)].type),0,yylinenumber,scope+1);
    }
    strcpy(PL[noOfParameters],(yyvsp[(3) - (5)].type));
    // printf("%s ",PL[noOfParameters]);
    PTL[noOfParameters]=flag;
    noOfParameters++;
}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 575 ".\\semanticAnalysis.y"
    {
                    printf("%s %s %s\n",(yyvsp[(1) - (3)].type),(yyvsp[(2) - (3)].value),(yyvsp[(3) - (3)].type));
                    struct SymbolTableEntry * search=lookup((yyvsp[(2) - (3)].value),scope+1,true);
                    if(search!=NULL){
                        char message[30]="Variable Already Declared";
                        int res=yyerror(message);
                        return -1;
                    }
                    else{
                        struct SymbolTableEntry*new_entry = insertIdentifier((yyvsp[(2) - (3)].value),(yyvsp[(3) - (3)].type),(yyvsp[(1) - (3)].type),0,yylinenumber,scope+1);
                    }
                    strcpy(PL[noOfParameters],(yyvsp[(1) - (3)].type));
                    // printf("%s %d",PL[noOfParameters],noOfParameters);
                    PTL[noOfParameters]='v';
                    noOfParameters++;
                }
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 591 ".\\semanticAnalysis.y"
    {(yyval.type)=malloc(strlen("array")+1);strcpy((yyval.type),"array");}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 591 ".\\semanticAnalysis.y"
    {(yyval.type)=malloc(strlen("variable")+1);strcpy((yyval.type),"variable");}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 594 ".\\semanticAnalysis.y"
    {
    int nop=forFunc->noOfParams;
    printf("%d %d",nop,noOfParameters);
    if(noOfParameters!=nop){
        char message[50]="No of Parameters of the Function Does not match";
        int res=yyerror(message);
        return -1;
    }
    // char temp[20];
    // char t;
    // for(int i=0;i<nop/2;i++){
    //     strcpy(temp,PL[i]);
    //     strcpy(PL[i],PL[nop-i-1]);
    //     strcpy(PL[nop-i-1],temp);
    //     t=PTL[i];
    //     PTL[i]=PTL[nop-i-1];
    //     PTL[nop-i-1]=t;
    // }

    for(int i=0;i<nop;i++){
        if(strcmp(PL[i],forFunc->paraList[i])!=0){
            char message[50]="DataTypes of Parameters did not match";
            int res=yyerror(message);
            return -1;
        }
    }
    
    for(int i=0;i<nop;i++){
        if(PTL[i]!=forFunc->paraTypes[i]){
            char message[50]="Type(Class) of Parameters did not match";
            int res=yyerror(message);
            return -1;
        }
    }
}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 629 ".\\semanticAnalysis.y"
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
                }
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 665 ".\\semanticAnalysis.y"
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

  case 101:

/* Line 1455 of yacc.c  */
#line 682 ".\\semanticAnalysis.y"
    {
    strcpy(PL[noOfParameters],(yyvsp[(1) - (1)].type));
    PTL[noOfParameters]=pt;
    noOfParameters++;
}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 687 ".\\semanticAnalysis.y"
    {
            strcpy(PL[noOfParameters],(yyvsp[(3) - (3)].type));
            PTL[noOfParameters]=pt;
            noOfParameters++;
        }
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 692 ".\\semanticAnalysis.y"
    {
    struct SymbolTableEntry * entry = lookup((yyvsp[(1) - (1)].value),scope,false);
    if(entry==NULL){
        char message[40]="Variable is not Declared";
        int res=yyerror(message);
        return -1;
    }
    if(strcmp(entry->type,CLASS[0])==0){
        //printf("Here ");
        pt='v';
        update(entry,yylinenumber);
    }
    else if(strcmp(entry->type,CLASS[1])==0){
        char message[40]="Function can't be passed as a parameter";
        int res=yyerror(message);
        return -1;
    }
    else if(strcmp(entry->type,CLASS[2])==0){
        pt='a';
        update(entry,yylinenumber);
    }
    (yyval.type)=malloc(strlen(entry->dataType)+1);strcpy((yyval.type),entry->dataType);}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 714 ".\\semanticAnalysis.y"
    {(yyval.type)=malloc(strlen((yyvsp[(1) - (1)].type))+1);strcpy((yyval.type),(yyvsp[(1) - (1)].type));pt='v';}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 715 ".\\semanticAnalysis.y"
    {(yyval.type)=malloc(strlen((yyvsp[(1) - (1)].type))+1);strcpy((yyval.type),(yyvsp[(1) - (1)].type));pt='v';}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 716 ".\\semanticAnalysis.y"
    {(yyval.type)=malloc(strlen((yyvsp[(1) - (1)].type))+1);strcpy((yyval.type),(yyvsp[(1) - (1)].type));pt='v';}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 717 ".\\semanticAnalysis.y"
    {(yyval.type)=malloc(strlen((yyvsp[(1) - (1)].type))+1);strcpy((yyval.type),(yyvsp[(1) - (1)].type));pt='v';}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 719 ".\\semanticAnalysis.y"
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
    // printf("%s %s\n",funTypeBuffer,funNameBuffer);
}
    break;



/* Line 1455 of yacc.c  */
#line 2742 "y.tab.c"
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
#line 835 ".\\semanticAnalysis.y"


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
