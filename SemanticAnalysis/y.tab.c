
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
    char datatypesArray[][20]={"int","char","float"};
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

    struct SymbolTableEntry* insertFunction(char* key,char * type,char * dataType,int dimension,int linenumber,int scope,int params,char ** parList) {
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

    //start globalVarDec startGlobal DG optionsG main mainParameters start1 varDec D options header newHeader file Exp function_declaration function_call function_defn parameter_list choice item params for while varDecF ExpF print printExpr printArguments printContent scanf scanfArguments scanfContent scanfExpr dimension BOX BALANCED_BRACK arrayElement arrayInitial arrayDeclr arrayAsAParameter arrayParams_unend higherDimention pointerAsAParameter PTR_DECLR PTR_EXP PTR_INITIAL PTR_STAR PTR_TYPE switch switchcase default comp ifElseLadder matched S elif unmatched userDefDataType userTypeDeclaration userTypeDefination userTypeInitialization userTypeObj userTypeParams


/* Line 189 of yacc.c  */
#line 422 "y.tab.c"

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
     ID = 260,
     INCLUDE = 261,
     PREDEF_HEADER = 262,
     STRING = 263,
     ELIF = 264,
     ELSE = 265,
     IF = 266,
     BREAK = 267,
     NOT = 268,
     FOR = 269,
     CONTINUE = 270,
     WHILE = 271,
     SWITCH = 272,
     CASE = 273,
     STRUCT = 274,
     UNION = 275,
     RETURN = 276,
     FLOATING_NUM = 277,
     SL_COMMENT = 278,
     ML_COMMENT = 279,
     CHAR_CONST = 280,
     EQUALTO = 281,
     OPEN_BRACK = 282,
     OPEN_FLOWER = 283,
     OPEN_SQ = 284,
     CLOSE_BRACK = 285,
     CLOSE_FLOWER = 286,
     CLOSE_SQ = 287,
     AND = 288,
     UNARY_OP = 289,
     PLUS = 290,
     MINUS = 291,
     DIV = 292,
     MUL = 293,
     MOD = 294,
     OR = 295,
     AMPERSAND = 296,
     BIT_OR = 297,
     BIT_XOR = 298,
     SEMICOLON = 299,
     COMMA = 300,
     ISEQUALTO = 301,
     LT = 302,
     LTE = 303,
     GT = 304,
     GTE = 305,
     NE = 306,
     PLUS_ET = 307,
     MINUS_ET = 308,
     MUL_ET = 309,
     DIV_ET = 310,
     OR_ET = 311,
     AND_ET = 312,
     XOR_ET = 313,
     PRINTF = 314,
     SCANF = 315,
     MAIN = 316,
     FUN_START = 317,
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
#define ID 260
#define INCLUDE 261
#define PREDEF_HEADER 262
#define STRING 263
#define ELIF 264
#define ELSE 265
#define IF 266
#define BREAK 267
#define NOT 268
#define FOR 269
#define CONTINUE 270
#define WHILE 271
#define SWITCH 272
#define CASE 273
#define STRUCT 274
#define UNION 275
#define RETURN 276
#define FLOATING_NUM 277
#define SL_COMMENT 278
#define ML_COMMENT 279
#define CHAR_CONST 280
#define EQUALTO 281
#define OPEN_BRACK 282
#define OPEN_FLOWER 283
#define OPEN_SQ 284
#define CLOSE_BRACK 285
#define CLOSE_FLOWER 286
#define CLOSE_SQ 287
#define AND 288
#define UNARY_OP 289
#define PLUS 290
#define MINUS 291
#define DIV 292
#define MUL 293
#define MOD 294
#define OR 295
#define AMPERSAND 296
#define BIT_OR 297
#define BIT_XOR 298
#define SEMICOLON 299
#define COMMA 300
#define ISEQUALTO 301
#define LT 302
#define LTE 303
#define GT 304
#define GTE 305
#define NE 306
#define PLUS_ET 307
#define MINUS_ET 308
#define MUL_ET 309
#define DIV_ET 310
#define OR_ET 311
#define AND_ET 312
#define XOR_ET 313
#define PRINTF 314
#define SCANF 315
#define MAIN 316
#define FUN_START 317
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
#line 349 ".\\semanticAnalysis.y"

    char * value;
    char * type;



/* Line 214 of yacc.c  */
#line 605 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 617 "y.tab.c"

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
#define YYLAST   699

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  71
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  72
/* YYNRULES -- Number of rules.  */
#define YYNRULES  194
/* YYNRULES -- Number of states.  */
#define YYNSTATES  446

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
     287,   293,   297,   299,   303,   305,   306,   313,   319,   321,
     325,   327,   329,   331,   333,   335,   347,   357,   369,   379,
     388,   395,   401,   406,   408,   409,   416,   418,   421,   425,
     428,   430,   432,   439,   442,   447,   451,   455,   458,   460,
     462,   465,   470,   474,   479,   484,   488,   497,   505,   507,
     510,   518,   525,   531,   535,   540,   546,   548,   552,   556,
     558,   559,   563,   568,   576,   583,   590,   593,   595,   598,
     600,   602,   615,   627,   637,   643,   644,   648,   649,   651,
     653,   655,   657,   659,   672,   681,   682,   691,   701,   710,
     716,   720,   726,   731,   734,   739,   741,   745,   746,   751,
     755,   764,   771,   778,   780
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      72,     0,    -1,    73,    76,    80,    -1,     6,    75,    74,
      -1,    73,    -1,    -1,     8,    -1,     7,    -1,    94,    -1,
      77,    -1,   137,    -1,   140,    76,    -1,    -1,    83,     5,
      79,    78,    44,    76,    -1,     5,    79,    78,    44,    76,
      -1,    45,     5,    79,    78,    -1,    -1,    26,    93,    -1,
      -1,    61,    81,    30,    91,    82,    92,    -1,    96,    -1,
      -1,    84,    -1,   105,    -1,   109,    -1,    98,    -1,   102,
      -1,   101,    -1,    21,   104,    44,    82,    -1,    15,    44,
      82,    -1,    12,    44,    82,    -1,    23,    82,    -1,    24,
      82,    -1,   115,    82,    -1,   117,    82,    -1,   128,    -1,
     124,    82,    -1,   123,    82,    -1,   132,    82,    -1,   140,
      82,    -1,   141,    82,    -1,    -1,     3,    -1,    83,    90,
      87,    86,    44,    82,    -1,    -1,     5,    85,    87,    86,
      44,    82,    -1,    45,    90,    87,    86,    -1,    -1,    26,
      93,    -1,    -1,    26,     5,    88,    27,    99,    30,    -1,
      -1,     5,    89,    27,    30,    -1,    -1,     5,    -1,    28,
      -1,    31,    -1,    27,    93,    30,    -1,    93,    35,    93,
      -1,    93,    36,    93,    -1,    93,    38,    93,    -1,    93,
      37,    93,    -1,    93,    39,    93,    -1,    93,    40,    93,
      -1,    93,    33,    93,    -1,    93,    43,    93,    -1,    93,
      41,    93,    -1,    93,    34,    -1,    34,    93,    -1,    13,
      93,    -1,    93,    42,    93,    -1,    93,    46,    93,    -1,
      93,    47,    93,    -1,    93,    48,    93,    -1,    93,    49,
      93,    -1,    93,    50,    93,    -1,    93,    51,    93,    -1,
      93,    52,    93,    -1,    93,    53,    93,    -1,    93,    54,
      93,    -1,    93,    55,    93,    -1,    93,    56,    93,    -1,
      93,    57,    93,    -1,    93,    58,    93,    -1,     5,    -1,
       4,    -1,    25,    -1,    95,    91,    82,    92,    76,    -1,
      62,    96,    30,    -1,    62,    30,    -1,    96,    45,    83,
       5,    97,    -1,    96,    45,   122,    -1,   122,    -1,    83,
       5,    97,    -1,   120,    -1,    -1,     5,    27,    99,    30,
      44,    82,    -1,     5,    27,    30,    44,    82,    -1,   100,
      -1,    99,    45,   100,    -1,     5,    -1,     4,    -1,     8,
      -1,    25,    -1,    22,    -1,    14,    27,   103,   104,    44,
     104,    30,    91,    82,    92,    82,    -1,    14,    27,   103,
     104,    44,   104,    30,    44,    82,    -1,    14,    27,    44,
     104,    44,   104,    30,    91,    82,    92,    82,    -1,    14,
      27,    44,   104,    44,   104,    30,    44,    82,    -1,    16,
      27,   104,    30,    91,    82,    92,    82,    -1,    16,    27,
     104,    30,    44,    82,    -1,    83,     5,    87,    86,    44,
      -1,     5,    87,    86,    44,    -1,    93,    -1,    -1,    59,
      27,   106,    30,    44,    82,    -1,     8,    -1,     8,   107,
      -1,    45,   108,   107,    -1,    45,   108,    -1,    93,    -1,
     113,    -1,    60,    27,   110,    30,    44,    82,    -1,     8,
     111,    -1,    45,    41,     5,   111,    -1,    45,    41,     5,
      -1,    45,   112,   111,    -1,    45,   112,    -1,     5,    -1,
     113,    -1,     5,   114,    -1,    29,    93,    32,   114,    -1,
      29,    93,    32,    -1,    83,     5,   116,    44,    -1,   116,
      29,     4,    32,    -1,    29,     4,    32,    -1,    83,     5,
     116,    26,    91,   118,    92,    44,    -1,    83,     5,   116,
      26,    91,    92,    44,    -1,   119,    -1,   119,    45,    -1,
     119,    45,    91,   118,    92,    45,   118,    -1,   119,    45,
      91,   118,    92,    45,    -1,   119,    45,    91,   118,    92,
      -1,    91,   118,    92,    -1,    91,   118,    92,    45,    -1,
      91,   118,    92,    45,   118,    -1,     4,    -1,   119,    45,
       4,    -1,    29,    32,   121,    -1,   116,    -1,    -1,   126,
     125,     5,    -1,   126,   125,     5,    44,    -1,   126,   125,
       5,    26,    41,     5,    44,    -1,   126,   125,     5,    26,
       5,    44,    -1,   126,   125,     5,    26,   127,    44,    -1,
     125,    38,    -1,    38,    -1,   142,     5,    -1,    83,    -1,
      65,    -1,    27,   126,   125,    30,    66,    27,    67,    27,
     126,   125,    30,    30,    -1,    27,   126,   125,    30,    66,
      27,    67,    27,   126,    30,    30,    -1,    17,    27,     5,
      30,    91,   129,   130,    92,    82,    -1,    18,   131,    63,
      82,   129,    -1,    -1,    64,    63,    82,    -1,    -1,    25,
      -1,     4,    -1,   133,    -1,   134,    -1,   136,    -1,    11,
      27,    93,    30,    91,    82,    92,   135,    10,    91,    82,
      92,    -1,     9,    27,    93,    30,    91,    82,    92,   135,
      -1,    -1,    11,    27,    93,    30,    91,    82,    92,   135,
      -1,    68,   142,     5,    91,   138,    92,   139,    44,    76,
      -1,   142,     5,    91,   138,    92,   139,    44,    76,    -1,
      83,     5,   121,    44,   138,    -1,   122,    44,   138,    -1,
     142,     5,     5,    44,   138,    -1,    83,     5,   121,    44,
      -1,   122,    44,    -1,   142,     5,     5,    44,    -1,     5,
      -1,   139,    45,     5,    -1,    -1,   142,     5,     5,    44,
      -1,     5,     5,    44,    -1,   142,     5,     5,    26,    91,
      99,    92,    44,    -1,     5,    69,     5,    26,   100,    44,
      -1,     5,    70,     5,    26,   100,    44,    -1,    19,    -1,
      20,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   376,   376,   377,   378,   378,   379,   379,   381,   381,
     381,   381,   381,   383,   384,   385,   385,   386,   386,   388,
     389,   389,   391,   391,   391,   391,   391,   391,   392,   392,
     392,   393,   393,   393,   393,   394,   394,   394,   394,   395,
     395,   395,   397,   400,   401,   401,   413,   413,   414,   414,
     414,   424,   424,   434,   436,   448,   449,   451,   452,   453,
     454,   455,   456,   457,   458,   459,   460,   461,   462,   463,
     464,   465,   466,   467,   468,   469,   470,   471,   472,   473,
     474,   475,   476,   477,   478,   489,   489,   491,   492,   493,
     494,   495,   496,   497,   498,   498,   499,   500,   501,   501,
     502,   502,   502,   502,   502,   504,   505,   506,   507,   509,
     510,   512,   513,   515,   515,   517,   518,   519,   520,   521,
     522,   522,   524,   525,   526,   527,   528,   529,   530,   530,
     532,   533,   533,   535,   536,   536,   537,   537,   538,   539,
     540,   541,   542,   543,   544,   545,   546,   546,   548,   549,
     549,   551,   553,   554,   554,   554,   555,   555,   556,   556,
     556,   557,   558,   560,   561,   561,   562,   562,   563,   563,
     565,   566,   566,   567,   568,   568,   569,   571,   571,   572,
     573,   574,   575,   576,   577,   578,   578,   578,   579,   579,
     580,   581,   582,   584,   584
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TYPE", "INTEGER", "ID", "INCLUDE",
  "PREDEF_HEADER", "STRING", "ELIF", "ELSE", "IF", "BREAK", "NOT", "FOR",
  "CONTINUE", "WHILE", "SWITCH", "CASE", "STRUCT", "UNION", "RETURN",
  "FLOATING_NUM", "SL_COMMENT", "ML_COMMENT", "CHAR_CONST", "EQUALTO",
  "OPEN_BRACK", "OPEN_FLOWER", "OPEN_SQ", "CLOSE_BRACK", "CLOSE_FLOWER",
  "CLOSE_SQ", "AND", "UNARY_OP", "PLUS", "MINUS", "DIV", "MUL", "MOD",
  "OR", "AMPERSAND", "BIT_OR", "BIT_XOR", "SEMICOLON", "COMMA",
  "ISEQUALTO", "LT", "LTE", "GT", "GTE", "NE", "PLUS_ET", "MINUS_ET",
  "MUL_ET", "DIV_ET", "OR_ET", "AND_ET", "XOR_ET", "PRINTF", "SCANF",
  "MAIN", "FUN_START", "COLON", "DEFAULT", "VOID", "MALLOC", "SIZEOF",
  "TYPEDEF", "DOT", "ARROW", "$accept", "start", "header", "newHeader",
  "file", "startGlobal", "globalVarDec", "DG", "optionsG", "main",
  "mainParameters", "start1", "type", "varDec", "$@1", "D", "options",
  "$@2", "$@3", "id", "open_flower", "close_flower", "Exp",
  "function_defn", "function_declaration", "parameter_list", "choice",
  "function_call", "params", "item", "for", "while", "varDecF", "ExpF",
  "print", "printExpr", "printArguments", "printContent", "scanf",
  "scanfExpr", "scanfArguments", "scanfContent", "arrayElement",
  "dimension", "arrayDeclr", "BOX", "arrayInitial", "BALANCED_BRACK",
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
      82,    82,    83,    84,    85,    84,    86,    86,    87,    88,
      87,    89,    87,    87,    90,    91,    92,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    94,    95,    95,
      96,    96,    96,    96,    97,    97,    98,    98,    99,    99,
     100,   100,   100,   100,   100,   101,   101,   101,   101,   102,
     102,   103,   103,   104,   104,   105,   106,   106,   107,   107,
     108,   108,   109,   110,   111,   111,   111,   111,   112,   112,
     113,   114,   114,   115,   116,   116,   117,   117,   118,   118,
     118,   118,   118,   118,   118,   118,   119,   119,   120,   121,
     121,   122,   123,   124,   124,   124,   125,   125,   126,   126,
     126,   127,   127,   128,   129,   129,   130,   130,   131,   131,
     132,   133,   133,   134,   135,   135,   136,   137,   137,   138,
     138,   138,   138,   138,   138,   139,   139,   139,   140,   140,
     141,   141,   141,   142,   142
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
       5,     3,     1,     3,     1,     0,     6,     5,     1,     3,
       1,     1,     1,     1,     1,    11,     9,    11,     9,     8,
       6,     5,     4,     1,     0,     6,     1,     2,     3,     2,
       1,     1,     6,     2,     4,     3,     3,     2,     1,     1,
       2,     4,     3,     4,     4,     3,     8,     7,     1,     2,
       7,     6,     5,     3,     4,     5,     1,     3,     3,     1,
       0,     3,     4,     7,     6,     6,     2,     1,     2,     1,
       1,    12,    11,     9,     5,     0,     3,     0,     1,     1,
       1,     1,     1,    12,     8,     0,     8,     9,     8,     5,
       3,     5,     4,     2,     4,     1,     3,     0,     4,     3,
       8,     6,     6,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,    12,     7,     6,     5,     1,    42,    18,
     193,   194,     0,     0,     0,     9,     0,     8,     0,    10,
      12,     0,     4,     3,     0,     0,    16,    89,   160,   159,
       0,    92,     0,     0,     0,    21,     2,    18,    55,    41,
      11,     0,   189,    85,    84,     0,    86,     0,     0,    17,
       0,     0,    95,    88,     0,   157,     0,   158,     0,     0,
      20,    16,    44,     0,     0,     0,     0,     0,     0,   114,
      41,    41,     0,     0,     0,   159,    22,    25,    27,    26,
      23,    24,    41,    41,    41,    41,     0,    35,    41,   170,
     171,   172,    41,    41,     0,     0,     0,    69,     0,    68,
       0,    67,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    18,    12,     0,    93,    94,   159,
      91,   151,   156,     0,     0,     0,     0,     0,     0,    53,
       0,    41,     0,    41,   114,     0,   113,     0,    31,    32,
       0,     0,    56,    12,    54,    53,    33,    34,    37,    36,
       0,    38,    39,    40,   158,   188,   159,     0,     0,     0,
      57,    64,    58,    59,    61,    60,    62,    63,    66,    70,
      65,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    16,    14,   150,    95,     0,    41,
      12,   101,   100,   102,   104,   103,     0,     0,    98,     0,
       0,    51,     0,    47,     0,    30,    53,   114,     0,   114,
      29,     0,     0,    41,   116,     0,     0,     0,    87,     0,
       0,    47,     0,     0,   150,   183,   187,   158,    15,   149,
     148,    90,   187,     0,    13,    41,     0,     0,     0,     0,
       0,    84,    48,     0,     0,     0,    47,     0,    53,     0,
       0,     0,    28,     0,   117,     0,     0,   123,     0,     0,
       0,     0,   133,     0,     0,   152,     0,     0,   180,   185,
       0,     0,     0,    19,    97,    41,    99,     0,     0,     0,
       0,    54,    53,    41,    41,     0,   114,    47,   114,    41,
      41,   165,    84,   120,   119,   121,    41,   128,     0,   127,
     129,    41,   135,     0,     0,    41,     0,     0,     0,     0,
       0,   182,    12,     0,   184,    12,    96,   191,   192,    52,
       0,    47,    45,     0,   112,     0,     0,     0,   110,     0,
       0,   167,     0,   130,   118,   115,   125,   126,   122,   146,
       0,     0,     0,   138,   134,    43,   154,   159,     0,     0,
     155,     0,   179,   178,   186,   181,   177,     0,    46,   175,
       0,   111,     0,    41,   169,   168,     0,     0,     0,     0,
     124,     0,   137,     0,   139,     0,   153,     0,    50,     0,
     176,    41,    41,    41,    41,   109,    41,    41,    41,   132,
     143,   136,   147,     0,     0,   190,     0,     0,   108,     0,
     106,     0,   165,   166,   163,   131,   144,     0,     0,     0,
      41,    41,    41,   164,   145,   142,     0,     0,     0,   107,
     105,   141,     0,    41,   173,   140,     0,     0,     0,   175,
       0,     0,   174,   162,     0,   161
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    23,     6,    14,    15,    51,    26,    36,
      59,    74,    75,    76,   139,   254,   213,   290,   250,   155,
     350,   153,   146,    17,    18,    30,   127,    77,   207,   208,
      78,    79,   219,   147,    80,   225,   264,   304,    81,   227,
     267,   309,   305,   343,    82,   239,    83,   352,   353,   128,
     240,   167,    84,    85,    56,    86,   319,    87,   341,   378,
     376,    88,    89,    90,   390,    91,    19,   168,   280,    92,
      93,    94
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -338
static const yytype_int16 yypact[] =
{
      25,   135,    47,    15,  -338,  -338,    25,  -338,  -338,    38,
    -338,  -338,   182,   132,    -8,  -338,    85,  -338,    87,  -338,
      15,   142,  -338,  -338,    75,   121,   104,  -338,  -338,   149,
     154,  -338,   148,   186,   212,    21,  -338,   133,  -338,   281,
    -338,    41,  -338,  -338,  -338,   121,  -338,   121,   121,   545,
     214,   166,   199,  -338,    21,  -338,    17,  -338,    87,   213,
     190,   104,    22,   219,   211,   240,   232,   243,   244,   121,
     281,   281,   251,   252,   249,   278,  -338,  -338,  -338,  -338,
    -338,  -338,   281,   281,   281,   281,   148,  -338,   281,  -338,
    -338,  -338,   281,   281,   280,   245,    21,   256,   434,  -338,
     121,  -338,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   133,    15,   259,  -338,  -338,   301,
    -338,  -338,  -338,    21,    87,   263,   226,   304,   305,    58,
     121,   281,    16,   281,   121,   306,   545,   269,  -338,  -338,
     308,   309,  -338,    15,   297,    58,  -338,  -338,  -338,  -338,
      24,  -338,  -338,  -338,   324,  -338,   326,   288,   249,   329,
    -338,   410,   203,   203,   256,   256,   256,   594,   648,   612,
     630,   381,   313,   313,   227,   227,   381,   571,   571,   571,
     571,   545,   545,   545,   104,  -338,   297,   199,   249,   281,
      15,  -338,  -338,  -338,  -338,  -338,   291,   168,  -338,   310,
     311,  -338,   191,   293,   463,  -338,    58,   121,   337,   121,
    -338,   314,   315,   281,   298,   323,   317,   325,  -338,   354,
     109,   293,   101,   114,   297,    21,   355,   358,  -338,   335,
    -338,  -338,   355,   249,  -338,   281,   322,    92,    92,    92,
     340,   342,   545,   365,   327,    87,   293,   328,    58,   330,
      76,    87,  -338,   202,  -338,   331,     9,  -338,   332,   341,
      87,   373,  -338,   339,    34,  -338,    87,   344,  -338,  -338,
     205,   345,   208,  -338,  -338,   281,  -338,   348,   350,   366,
     368,  -338,    58,   281,   281,   353,   121,   293,   121,   281,
     281,   380,   370,   545,   298,  -338,   281,   370,   395,   317,
    -338,   281,  -338,    70,   369,   281,   359,    21,   400,   362,
      92,    21,    15,   407,    21,    15,  -338,  -338,  -338,  -338,
      92,   293,  -338,   249,  -338,   383,   378,   384,  -338,   249,
      98,   360,   121,  -338,  -338,  -338,   317,  -338,  -338,  -338,
      61,   379,   249,   387,  -338,  -338,  -338,  -338,   148,   382,
    -338,   178,  -338,  -338,  -338,  -338,  -338,   175,  -338,   416,
      88,  -338,   113,   281,  -338,  -338,   371,   375,   249,   519,
    -338,   249,  -338,   392,    78,    18,  -338,   396,  -338,   414,
     432,   281,   281,   281,   281,  -338,   281,   281,   281,   370,
     405,  -338,  -338,    61,   389,  -338,   121,    87,  -338,   249,
    -338,   249,   380,  -338,  -338,  -338,    61,   249,   435,   492,
     281,   281,   281,  -338,  -338,   420,   411,    87,   249,  -338,
    -338,    61,   452,   281,  -338,  -338,    21,   249,    83,   416,
     464,   184,  -338,  -338,   465,  -338
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -338,  -338,   501,  -338,  -338,    68,  -338,   -57,   -29,  -338,
    -338,   -12,    -3,  -338,  -338,  -219,  -148,  -338,  -338,   255,
     -16,    26,    60,  -338,  -338,   488,   367,  -338,  -276,    10,
    -338,  -338,  -338,  -108,  -338,  -338,   220,  -338,  -338,  -338,
    -279,  -338,   270,   138,  -338,   409,  -338,  -337,  -338,  -338,
     356,    -2,  -338,  -338,   -81,    -9,  -338,  -338,   177,  -338,
    -338,  -338,  -338,  -338,   176,  -338,  -338,  -132,   374,     8,
    -338,     3
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -50
static const yytype_int16 yytable[] =
{
      16,   198,    39,    32,   135,   160,    21,   231,    61,    29,
      31,    20,   273,   381,   307,    33,    34,    16,     8,     8,
       9,   216,   131,    21,     8,    96,    32,    24,    20,   232,
     347,     1,    29,    31,    10,    11,   221,   295,    33,   316,
      10,    11,   133,    24,   361,    32,    95,     7,   404,   136,
     308,   129,   130,    35,   367,   132,   132,    33,   148,   149,
     217,   317,   132,   211,    25,   349,   417,   380,   256,    38,
     156,   157,   158,   159,   349,   318,   161,    12,   336,   424,
     162,   163,   402,    13,   212,    49,    28,    32,    40,    38,
      37,   137,   138,   166,   435,   194,   201,   202,    38,   169,
     203,   152,   374,   278,    38,    97,    38,    98,    99,   257,
     297,   259,   368,   440,   204,    38,    38,   205,   199,    42,
     299,    55,    16,   375,    32,    43,    44,   274,    21,   215,
     166,   220,   391,    20,    45,   270,   169,   238,   271,   218,
     276,    38,     4,     5,   331,   275,    46,    41,    47,    50,
      16,    10,    11,   272,    52,    48,    21,   393,   165,    25,
     171,    20,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,    53,     8,    55,   243,   335,   362,
     337,    57,   365,   195,   236,    43,   251,    16,   246,    54,
     214,    10,    11,    21,    45,   388,    43,   302,    20,   152,
     125,   262,    27,   247,   444,    45,    46,    58,    47,   124,
     247,   228,   132,   247,   242,    48,    32,    46,   126,    47,
     201,   202,   166,   284,   203,    54,    48,   101,   169,   294,
     104,   105,   106,   134,   300,   301,   140,    28,   204,   322,
     323,   205,   325,   323,   313,   141,   206,   286,   287,   288,
     320,   101,   102,   103,   104,   105,   106,   142,   244,   283,
     144,   145,   252,   326,   112,   113,   143,   385,   150,   151,
     152,   332,   333,   154,     8,   164,    62,   338,   339,   165,
     101,   196,    63,    64,   345,    65,    66,    67,    68,   348,
      10,    11,    69,   355,    70,    71,   197,   200,   358,   209,
     210,   222,    32,   223,   357,    32,   224,   226,   166,    16,
      33,   166,    16,   303,   169,    21,   229,   169,    21,   233,
      20,   234,   235,    20,   237,   245,   248,   249,   253,   351,
      72,    73,   258,   263,   260,   261,    28,   101,   102,   103,
     104,   105,   106,   265,   392,   268,   394,   441,   269,   369,
     279,   395,   266,   281,   271,   373,   285,   289,   403,   -49,
     291,   293,   296,   312,   298,   306,   311,   314,   383,   408,
     409,   410,   411,   315,   412,   413,   414,   387,   321,   324,
     363,   420,   327,   366,   328,   330,   329,   334,   340,   342,
     346,   354,   379,   356,   398,   359,   360,   400,   428,   429,
     430,   433,   364,   370,   372,   101,   102,   103,   104,   105,
     106,   437,   371,   382,   377,   389,   386,   438,   112,   113,
     114,   115,   384,   357,   396,   421,   401,   422,   397,    33,
     405,   406,   407,   425,   101,   102,   103,   104,   105,   106,
     416,   108,   109,   110,   434,   418,   111,   112,   113,   114,
     115,   116,   426,   439,   170,   431,   419,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   432,   436,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   255,   443,   445,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,    22,   292,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   427,    60,   344,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   310,   415,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   399,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   230,   241,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   423,
     277,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   442,   282,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   100,   101,   102,
     103,   104,   105,   106,     0,   108,   109,   110,     0,     0,
     111,   112,   113,   114,   115,   116,   101,   102,   103,   104,
     105,   106,     0,   108,     0,   110,     0,     0,   111,   112,
     113,   114,   115,   116,   101,   102,   103,   104,   105,   106,
       0,   108,     0,     0,     0,     0,   111,   112,   113,   114,
     115,   116,   101,   102,   103,   104,   105,   106,     0,     0,
       0,     0,     0,     0,   111,   112,   113,   114,   115,   116
};

static const yytype_int16 yycheck[] =
{
       3,   133,    18,    12,    61,    86,     3,   155,    37,    12,
      12,     3,   231,   350,     5,    12,    13,    20,     3,     3,
       5,     5,     5,    20,     3,    41,    35,     5,    20,     5,
     309,     6,    35,    35,    19,    20,   144,   256,    35,     5,
      19,    20,    58,     5,   320,    54,     5,     0,    30,    27,
      41,    54,    54,    61,   330,    38,    38,    54,    70,    71,
      44,    27,    38,     5,    26,     4,   403,   346,   216,    28,
      82,    83,    84,    85,     4,    41,    88,    62,   297,   416,
      92,    93,     4,    68,    26,    25,    65,    96,    20,    28,
       5,    69,    70,    96,   431,   124,     4,     5,    28,    96,
       8,    31,     4,   235,    28,    45,    28,    47,    48,   217,
     258,   219,   331,    30,    22,    28,    28,    25,   134,    44,
      44,    38,   125,    25,   133,     4,     5,    26,   125,   141,
     133,   143,    44,   125,    13,    26,   133,   194,    29,   142,
      26,    28,     7,     8,   292,    44,    25,     5,    27,    45,
     153,    19,    20,    44,     5,    34,   153,    44,    44,    26,
     100,   153,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,    30,     3,    38,   199,   296,   321,
     298,     5,   324,   125,   168,     4,     5,   200,    30,    45,
     140,    19,    20,   200,    13,    30,     4,     5,   200,    31,
      44,   223,    30,    45,    30,    13,    25,     5,    27,     5,
      45,   153,    38,    45,   198,    34,   235,    25,    29,    27,
       4,     5,   235,   245,     8,    45,    34,    34,   235,   255,
      37,    38,    39,    30,   260,   261,    27,    65,    22,    44,
      45,    25,    44,    45,   270,    44,    30,   247,   248,   249,
     276,    34,    35,    36,    37,    38,    39,    27,   200,   243,
      27,    27,   212,   285,    47,    48,    44,   358,    27,    27,
      31,   293,   294,     5,     3,     5,     5,   299,   300,    44,
      34,    32,    11,    12,   306,    14,    15,    16,    17,   311,
      19,    20,    21,   315,    23,    24,     5,    44,   317,     5,
       5,     5,   321,    44,   317,   324,     8,     8,   321,   322,
     317,   324,   325,   263,   321,   322,    29,   324,   325,     5,
     322,     5,    44,   325,     5,    44,    26,    26,    45,   313,
      59,    60,     5,    45,    30,    30,    65,    34,    35,    36,
      37,    38,    39,    30,   370,    30,   372,   438,     4,   333,
       5,   373,    45,     5,    29,   339,    44,    27,   384,    27,
       5,    44,    44,    32,    44,    44,    44,     4,   352,   391,
     392,   393,   394,    44,   396,   397,   398,   361,    44,    44,
     322,   407,    44,   325,    44,    27,    30,    44,    18,    29,
       5,    32,   342,    44,   378,     5,    44,   381,   420,   421,
     422,   427,     5,    30,    30,    34,    35,    36,    37,    38,
      39,   433,    44,    44,    64,     9,    44,   436,    47,    48,
      49,    50,    45,   436,    63,   409,    44,   411,    63,   436,
      44,    27,    10,   417,    34,    35,    36,    37,    38,    39,
      45,    41,    42,    43,   428,    66,    46,    47,    48,    49,
      50,    51,    27,   437,    30,    45,   406,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    67,    27,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    30,    30,    30,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,     6,   253,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    30,    35,   304,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,   266,   399,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,   154,   197,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,   412,
     234,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,   439,   242,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    33,    34,    35,
      36,    37,    38,    39,    -1,    41,    42,    43,    -1,    -1,
      46,    47,    48,    49,    50,    51,    34,    35,    36,    37,
      38,    39,    -1,    41,    -1,    43,    -1,    -1,    46,    47,
      48,    49,    50,    51,    34,    35,    36,    37,    38,    39,
      -1,    41,    -1,    -1,    -1,    -1,    46,    47,    48,    49,
      50,    51,    34,    35,    36,    37,    38,    39,    -1,    -1,
      -1,    -1,    -1,    -1,    46,    47,    48,    49,    50,    51
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,    72,    73,     7,     8,    75,     0,     3,     5,
      19,    20,    62,    68,    76,    77,    83,    94,    95,   137,
     140,   142,    73,    74,     5,    26,    79,    30,    65,    83,
      96,   122,   126,   142,   142,    61,    80,     5,    28,    91,
      76,     5,    44,     4,     5,    13,    25,    27,    34,    93,
      45,    78,     5,    30,    45,    38,   125,     5,     5,    81,
      96,    79,     5,    11,    12,    14,    15,    16,    17,    21,
      23,    24,    59,    60,    82,    83,    84,    98,   101,   102,
     105,   109,   115,   117,   123,   124,   126,   128,   132,   133,
     134,   136,   140,   141,   142,     5,    91,    93,    93,    93,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,     5,    44,    29,    97,   120,    83,
     122,     5,    38,    91,    30,    78,    27,    69,    70,    85,
      27,    44,    27,    44,    27,    27,    93,   104,    82,    82,
      27,    27,    31,    92,     5,    90,    82,    82,    82,    82,
     125,    82,    82,    82,     5,    44,    83,   122,   138,   142,
      30,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    79,    76,    32,     5,   138,    91,
      44,     4,     5,     8,    22,    25,    30,    99,   100,     5,
       5,     5,    26,    87,    93,    82,     5,    44,    83,   103,
      82,   104,     5,    44,     8,   106,     8,   110,    76,    29,
     116,    87,     5,     5,     5,    44,    92,     5,    78,   116,
     121,    97,    92,    82,    76,    44,    30,    45,    26,    26,
      89,     5,    93,    45,    86,    30,    87,   104,     5,   104,
      30,    30,    82,    45,   107,    30,    45,   111,    30,     4,
      26,    29,    44,    86,    26,    44,    26,   121,   138,     5,
     139,     5,   139,    92,    82,    44,   100,   100,   100,    27,
      88,     5,    90,    44,    91,    86,    44,    87,    44,    44,
      91,    91,     5,    93,   108,   113,    44,     5,    41,   112,
     113,    44,    32,    91,     4,    44,     5,    27,    41,   127,
      91,    44,    44,    45,    44,    44,    82,    44,    44,    30,
      27,    87,    82,    82,    44,   104,    86,   104,    82,    82,
      18,   129,    29,   114,   107,    82,     5,   111,    82,     4,
      91,    92,   118,   119,    32,    82,    44,    83,   126,     5,
      44,    99,   138,    76,     5,   138,    76,    99,    86,    92,
      30,    44,    30,    92,     4,    25,   131,    64,   130,    93,
     111,   118,    44,    92,    45,   125,    44,    92,    30,     9,
     135,    44,    91,    44,    91,    82,    63,    63,    92,    32,
      92,    44,     4,    91,    30,    44,    27,    10,    82,    82,
      82,    82,    82,    82,    82,   114,    45,   118,    66,    93,
      91,    92,    92,   129,   118,    92,    27,    30,    82,    82,
      82,    45,    67,    91,    92,   118,    27,    82,   126,    92,
      30,   125,   135,    30,    30,    30
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
#line 376 ".\\semanticAnalysis.y"
    {printf("Syntax is Correct\n");return;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 397 ".\\semanticAnalysis.y"
    {
            strcpy(typeBuffer,(yyvsp[(1) - (1)].type));
        }
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 401 ".\\semanticAnalysis.y"
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
#line 414 ".\\semanticAnalysis.y"
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
#line 424 ".\\semanticAnalysis.y"
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
#line 436 ".\\semanticAnalysis.y"
    {
    struct SymbolTableEntry * search=lookup((yyvsp[(1) - (1)].value),scope,true);
    if(search!=NULL){
        char message[30]="Variable Already Declared";
        int res=yyerror(message);
        return -1;
    }
    else{
        struct SymbolTableEntry*new_entry=insertIdentifier((yyvsp[(1) - (1)].value),CLASS[0],typeBuffer,1,yylinenumber,scope);
    }
}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 448 ".\\semanticAnalysis.y"
    {scope++;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 449 ".\\semanticAnalysis.y"
    {deleteDMT(scope);scope--;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 478 ".\\semanticAnalysis.y"
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



/* Line 1455 of yacc.c  */
#line 2384 "y.tab.c"
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
#line 586 ".\\semanticAnalysis.y"


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
