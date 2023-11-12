%{
    #include<stdio.h>
    int yylex();
    int yyerror(char const * s);
    extern FILE * yyin;
    extern char *yytext;

    #include <string.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #define TABLE_SIZE 100003
    #define MAX_SYMBOLS 1000000

    //Scope Number
    int scope=1; //Scope of Global Variables = 1

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
    };

    struct SymbolTable {
        struct SymbolTableEntry * symTable[TABLE_SIZE];
    };

    struct SymbolTable Table;

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

    void insert(char* key,char * type,char * dataType,int dimension,int linenumber,int scope) {
        int index = hashfunction(key);

        // Create a new entry
        struct SymbolTableEntry* new_entry = (struct SymbolTableEntry*)malloc(sizeof(struct SymbolTableEntry));

        new_entry->name = strdup(key); // Duplicate the key string
        new_entry->type = strdup(type); // Duplicate the string type
        new_entry->dataType=strdup(dataType) //Duplicate the dataType of the String
        new_entry->lineOfDeclaration=linenumber
        new_entry->scope=scope
        new_entry->dimension=dimension

        new_entry->next = Table.symTable[index];

        // new_entry->head = (struct lines *)malloc(sizeof(struct lines));
        // new_entry->head->lineno = linenumber;
        // new_entry->head->next = NULL;
        // new_entry->tail = new_entry->head;

        Table.symTable[index] = new_entry;
        locations[symTableSize++]=strdup(key);
    }

    //Function to append an entry for key-value pair that already exists in the SymbolTable
    void update(struct SymbolTableEntry* entry,int linenumber){
        // struct lines * new_node = (struct lines *)malloc(sizeof(struct lines));
        // new_node->lineno = linenumber;
        // new_node->next = NULL;
        // entry->tail->next = new_node;
        // entry->tail = new_node;
    }

    // Function to Lookup
    struct SymbolTableEntry *  lookup(char* key,int scope,bool insertion) {
        int index = hashfunction(key);
        if(insertion){
            struct SymbolTableEntry* entry = Table.symTable[index];
            while(entry != NULL){
                if(strcmp(entry->name,key) == 0 && entry->scope==scope)return entry;
                entry = entry->next;
            }
        }
        else{
            while(scope>=1){
                struct SymbolTableEntry* entry = Table.symTable[index];
                while(entry != NULL){
                    if(strcmp(entry->name,key) == 0 && entry->scope==scope)return entry;
                    entry = entry->next;
                }
                scope--;
            }
        }
        // Key not found
        return NULL;
    }
%}

%token INCLUDE PREDEF_HEADER STRING ELIF ELSE IF BREAK NOT FOR CONTINUE WHILE TYPE SWITCH CASE STRUCT UNION RETURN ID INTEGER FLOATING_NUM SL_COMMENT ML_COMMENT CHAR_CONST EQUALTO OPEN_BRACK OPEN_FLOWER OPEN_SQ CLOSE_BRACK CLOSE_FLOWER CLOSE_SQ AND UNARY_OP PLUS MINUS DIV MUL MOD OR AMPERSAND BIT_OR BIT_XOR SEMICOLON COMMA ISEQUALTO LT LTE GT GTE NE PLUS_ET MINUS_ET MUL_ET DIV_ET OR_ET AND_ET XOR_ET PRINTF SCANF MAIN FUN_START COLON DEFAULT VOID MALLOC SIZEOF TYPEDEF DOT ARROW

%right XOR_ET OR_ET AND_ET
%right PLUS_ET MINUS_ET MUL_ET DIV_ET EQUALTO
%left OR
%left AND
%left BIT_OR
%left BIT_XOR
%left AMPERSAND
%left ISEQUALTO NE
%left GT GTE
%left LT LTE
%left PLUS MINUS 
%left MUL DIV MOD
%left NOT
%left UNARY_OP
%left OPEN_BRACK CLOSE_BRACK

%%
start: header startGlobal main {printf("Syntax is Correct\n");}

startGlobal : function_defn | globalVarDec | userTypeDefination | userTypeDeclaration startGlobal | 

globalVarDec : TYPE ID optionsG DG SEMICOLON startGlobal 
               | ID optionsG DG SEMICOLON startGlobal 
DG : COMMA ID optionsG DG | 
optionsG : EQUALTO Exp | 

main: MAIN mainParameters CLOSE_BRACK OPEN_FLOWER{scope++;}  start1 CLOSE_FLOWER {remove(scope);scope--;} 
mainParameters : parameter_list |

start1: print | scanf | function_call | varDec | while | for
        | RETURN ExpF SEMICOLON start1 | CONTINUE SEMICOLON start1| BREAK SEMICOLON start1
        | SL_COMMENT start1 | ML_COMMENT start1 | arrayDeclr start1 | arrayInitial start1 
        | switch | PTR_INITIAL start1 | PTR_DECLR start1 | ifElseLadder start1
        | userTypeDeclaration start1 | userTypeInitialization start1 |


varDec : TYPE ID options D SEMICOLON start1 
         | ID options D SEMICOLON start1 
         | UNARY_OP Exp SEMICOLON start1
         | Exp UNARY_OP SEMICOLON start1
D : COMMA ID options D | 
options : EQUALTO Exp | EQUALTO ID OPEN_BRACK params CLOSE_BRACK | ID OPEN_BRACK CLOSE_BRACK | 

header: INCLUDE file newHeader 
newHeader: header | 
file : STRING | PREDEF_HEADER 

Exp: OPEN_BRACK Exp CLOSE_BRACK 
     | Exp PLUS Exp 
     | Exp MINUS Exp 
     | Exp MUL Exp 
     | Exp DIV Exp 
     | Exp MOD Exp 
     | Exp OR Exp 
     | Exp AND Exp 
     | Exp BIT_XOR Exp 
     | Exp AMPERSAND Exp 
     | Exp UNARY_OP 
     | UNARY_OP Exp 
     | NOT Exp 
     | Exp BIT_OR Exp 
     | Exp ISEQUALTO Exp
     | Exp LT Exp
     | Exp LTE Exp
     | Exp GT Exp
     | Exp GTE Exp
     | Exp NE Exp
     | Exp PLUS_ET Exp
     | Exp MINUS_ET Exp
     | Exp MUL_ET Exp
     | Exp DIV_ET Exp
     | Exp OR_ET Exp
     | Exp AND_ET Exp
     | Exp XOR_ET Exp
     | ID 
     | INTEGER 

function_defn : function_declaration OPEN_FLOWER{scope++;} start1 CLOSE_FLOWER{remove(scope);scope--;} startGlobal 
function_declaration: FUN_START parameter_list CLOSE_BRACK 
                      | FUN_START CLOSE_BRACK 
parameter_list: parameter_list COMMA TYPE ID choice
                | parameter_list COMMA pointerAsAParameter
                | pointerAsAParameter
                | TYPE ID choice
choice : arrayAsAParameter | 
function_call : ID OPEN_BRACK params CLOSE_BRACK SEMICOLON start1 
                | ID OPEN_BRACK CLOSE_BRACK SEMICOLON start1 
params : item | params COMMA item 
item : ID | INTEGER | STRING | CHAR_CONST | FLOATING_NUM 

for : FOR OPEN_BRACK varDecF ExpF SEMICOLON ExpF CLOSE_BRACK OPEN_FLOWER{scope++;} start1 CLOSE_FLOWER{remove(scope);scope--;} start1
        | FOR OPEN_BRACK varDecF ExpF SEMICOLON ExpF CLOSE_BRACK SEMICOLON start1 
        | FOR OPEN_BRACK SEMICOLON ExpF SEMICOLON ExpF CLOSE_BRACK OPEN_FLOWER{scope++;} start1 CLOSE_FLOWER{remove(scope);scope--;} start1
        | FOR OPEN_BRACK SEMICOLON ExpF SEMICOLON ExpF CLOSE_BRACK SEMICOLON start1 

while : WHILE OPEN_BRACK ExpF CLOSE_BRACK OPEN_FLOWER{scope++;} start1 CLOSE_FLOWER{remove(scope);scope--;} start1
        | WHILE OPEN_BRACK ExpF CLOSE_BRACK SEMICOLON start1

varDecF : TYPE ID options D SEMICOLON 
         | ID options D SEMICOLON 

ExpF : Exp | 

print : PRINTF OPEN_BRACK printExpr CLOSE_BRACK SEMICOLON start1 
printExpr : STRING 
       | STRING printArguments
printArguments : COMMA printContent printArguments
                | COMMA printContent
printContent : Exp | arrayElement

scanf : SCANF OPEN_BRACK scanfExpr CLOSE_BRACK SEMICOLON start1
scanfExpr : STRING scanfArguments
scanfArguments : COMMA AMPERSAND ID scanfArguments
            | COMMA AMPERSAND ID
            | COMMA scanfContent scanfArguments
            | COMMA scanfContent
scanfContent : ID | arrayElement

arrayElement : ID dimension
dimension : OPEN_SQ Exp CLOSE_SQ dimension | OPEN_SQ Exp CLOSE_SQ

arrayDeclr : TYPE ID BOX SEMICOLON
BOX : BOX OPEN_SQ INTEGER CLOSE_SQ | OPEN_SQ INTEGER CLOSE_SQ
arrayInitial : TYPE ID BOX EQUALTO OPEN_FLOWER BALANCED_BRACK CLOSE_FLOWER SEMICOLON | TYPE ID BOX EQUALTO OPEN_FLOWER CLOSE_FLOWER SEMICOLON
BALANCED_BRACK : arrayParams_unend 
            | arrayParams_unend COMMA
            | arrayParams_unend COMMA OPEN_FLOWER BALANCED_BRACK CLOSE_FLOWER COMMA BALANCED_BRACK
            | arrayParams_unend COMMA OPEN_FLOWER BALANCED_BRACK CLOSE_FLOWER COMMA
            | arrayParams_unend COMMA OPEN_FLOWER BALANCED_BRACK CLOSE_FLOWER     
            | OPEN_FLOWER BALANCED_BRACK CLOSE_FLOWER
            | OPEN_FLOWER BALANCED_BRACK CLOSE_FLOWER COMMA 
            | OPEN_FLOWER BALANCED_BRACK CLOSE_FLOWER COMMA BALANCED_BRACK
arrayParams_unend : INTEGER | arrayParams_unend COMMA INTEGER 

arrayAsAParameter : OPEN_SQ CLOSE_SQ higherDimention
higherDimention : BOX | 

pointerAsAParameter : PTR_TYPE PTR_STAR ID

PTR_DECLR : PTR_TYPE PTR_STAR ID SEMICOLON
PTR_INITIAL : PTR_TYPE PTR_STAR ID EQUALTO AMPERSAND ID SEMICOLON | PTR_TYPE PTR_STAR ID EQUALTO ID SEMICOLON | PTR_TYPE PTR_STAR ID EQUALTO PTR_EXP SEMICOLON
PTR_STAR : PTR_STAR MUL | MUL
PTR_TYPE : userDefDataType ID | TYPE | VOID 
PTR_EXP : OPEN_BRACK PTR_TYPE PTR_STAR CLOSE_BRACK MALLOC OPEN_BRACK SIZEOF OPEN_BRACK PTR_TYPE PTR_STAR CLOSE_BRACK CLOSE_BRACK 
        | OPEN_BRACK PTR_TYPE PTR_STAR CLOSE_BRACK MALLOC OPEN_BRACK SIZEOF OPEN_BRACK PTR_TYPE CLOSE_BRACK CLOSE_BRACK

switch : SWITCH OPEN_BRACK ID CLOSE_BRACK OPEN_FLOWER{scope++;} switchcase default CLOSE_FLOWER{remove(scope);scope--;} start1
switchcase : CASE comp COLON start1 switchcase | 
default : DEFAULT COLON start1 | 
comp : CHAR_CONST | INTEGER

ifElseLadder: S 
S: matched | unmatched 
matched: IF OPEN_BRACK Exp CLOSE_BRACK OPEN_FLOWER{scope++;} start1 CLOSE_FLOWER{remove(scope);scope--;} elif ELSE OPEN_FLOWER{scope++;} start1 CLOSE_FLOWER{remove(scope);scope--;} 
elif : ELIF OPEN_BRACK Exp CLOSE_BRACK OPEN_FLOWER{scope++;} start1 CLOSE_FLOWER{remove(scope);scope--;} elif | 
unmatched: IF OPEN_BRACK Exp CLOSE_BRACK OPEN_FLOWER{scope++;} start1 CLOSE_FLOWER{remove(scope);scope--;} elif

userTypeDefination : TYPEDEF userDefDataType ID OPEN_FLOWER userTypeParams CLOSE_FLOWER userTypeObj SEMICOLON startGlobal | userDefDataType ID OPEN_FLOWER userTypeParams CLOSE_FLOWER userTypeObj SEMICOLON startGlobal
userTypeParams : TYPE ID higherDimention SEMICOLON userTypeParams  
                | pointerAsAParameter SEMICOLON userTypeParams
                | userDefDataType ID ID SEMICOLON userTypeParams
                | TYPE ID higherDimention SEMICOLON
                | pointerAsAParameter SEMICOLON
                | userDefDataType ID ID SEMICOLON
userTypeObj : ID | userTypeObj COMMA ID | 
userTypeDeclaration : userDefDataType ID ID SEMICOLON | ID ID SEMICOLON
userTypeInitialization : userDefDataType ID ID EQUALTO OPEN_FLOWER params CLOSE_FLOWER SEMICOLON
                        | ID DOT ID EQUALTO item SEMICOLON
                        | ID ARROW ID EQUALTO item SEMICOLON

userDefDataType : STRUCT | UNION
%%

int yyerror(const char *s){
    extern int yylinenumber;
    printf("Error %s!! \n Line No : %d\n",s,yylinenumber);
}

int main(){
    yyin=fopen("input14.txt","r");
    yyparse();
    fclose(yyin);
}