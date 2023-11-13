%{
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
%}

%union{
    char * value;
    char * type;
}

%token<type> TYPE INTEGER
%token<value> ID

%token INCLUDE PREDEF_HEADER STRING ELIF ELSE IF BREAK NOT FOR CONTINUE WHILE SWITCH CASE STRUCT UNION RETURN FLOATING_NUM SL_COMMENT ML_COMMENT CHAR_CONST EQUALTO OPEN_BRACK OPEN_FLOWER OPEN_SQ CLOSE_BRACK CLOSE_FLOWER CLOSE_SQ AND UNARY_OP PLUS MINUS DIV MUL MOD OR AMPERSAND BIT_OR BIT_XOR SEMICOLON COMMA ISEQUALTO LT LTE GT GTE NE PLUS_ET MINUS_ET MUL_ET DIV_ET OR_ET AND_ET XOR_ET PRINTF SCANF MAIN FUN_START COLON DEFAULT VOID MALLOC SIZEOF TYPEDEF DOT ARROW

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
start: header startGlobal main {printf("Syntax is Correct\n");return;}
header: INCLUDE file newHeader 
newHeader: header | 
file : STRING | PREDEF_HEADER 

startGlobal : function_defn | globalVarDec | userTypeDefination | userTypeDeclaration startGlobal | 

globalVarDec : type ID optionsG DG SEMICOLON startGlobal 
               | ID optionsG DG SEMICOLON startGlobal 
DG : COMMA ID optionsG DG | 
optionsG : EQUALTO Exp | 

main: MAIN mainParameters CLOSE_BRACK open_flower  start1 close_flower 
mainParameters : parameter_list |

start1: varDec |print | scanf | function_call |  while | for
        | RETURN ExpF SEMICOLON start1 | CONTINUE SEMICOLON start1| BREAK SEMICOLON start1
        | SL_COMMENT start1 | ML_COMMENT start1 | arrayDeclr start1 | arrayInitial start1 
        | switch | PTR_INITIAL start1 | PTR_DECLR start1 | ifElseLadder start1
        | userTypeDeclaration start1 | userTypeInitialization start1 |

type : TYPE {
            strcpy(typeBuffer,$1);
        }
varDec : type id options D SEMICOLON start1 
         | ID{
            struct SymbolTableEntry * search=lookup($1,scope,false);
            if(search==NULL){
                char message[30]="Variable Not Declared";
                int res=yyerror(message);
                return -1;
            }
            else{
                update(search,yylinenumber);
            }
         } options D SEMICOLON start1 

D : COMMA id options D | 
options : EQUALTO Exp | EQUALTO ID{
    struct SymbolTableEntry * search=lookup($2,scope,false);
    if(search==NULL){
        char message[30]="Function Not Declared";
        int res=yyerror(message);
        return -1;
    }
    else{
        update(search,yylinenumber);
    }
} OPEN_BRACK params CLOSE_BRACK | ID{
    struct SymbolTableEntry * search=lookup($1,scope,false);
    if(search==NULL){
        char message[30]="Function Not Declared";
        int res=yyerror(message);
        return -1;
    }
    else{
        update(search,yylinenumber);
    }
} OPEN_BRACK CLOSE_BRACK | 

id: ID {
    struct SymbolTableEntry * search=lookup($1,scope,true);
    if(search!=NULL){
        char message[30]="Variable Already Declared";
        int res=yyerror(message);
        return -1;
    }
    else{
        struct SymbolTableEntry*new_entry=insertIdentifier($1,CLASS[0],typeBuffer,1,yylinenumber,scope);
    }
}

open_flower : OPEN_FLOWER {scope++;}
close_flower : CLOSE_FLOWER {deleteDMT(scope);scope--;}

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
     | ID {
        struct SymbolTableEntry * found=lookup($1,scope,false);
        if(found==NULL){
            char const errorMessage[100]="Variable Not Declared!!";
            int a=yyerror(errorMessage);
            return -1;
        }
        else{
            update(found,yylinenumber);
        }
     }
     | INTEGER | CHAR_CONST

function_defn : function_declaration open_flower start1 close_flower startGlobal 
function_declaration: FUN_START parameter_list CLOSE_BRACK 
                      | FUN_START CLOSE_BRACK 
parameter_list: parameter_list COMMA type ID choice
                | parameter_list COMMA pointerAsAParameter
                | pointerAsAParameter
                | type ID choice
choice : arrayAsAParameter | 
function_call : ID OPEN_BRACK params CLOSE_BRACK SEMICOLON start1 
                | ID OPEN_BRACK CLOSE_BRACK SEMICOLON start1 
params : item | params COMMA item 
item : ID | INTEGER | STRING | CHAR_CONST | FLOATING_NUM 

for : FOR OPEN_BRACK varDecF ExpF SEMICOLON ExpF CLOSE_BRACK open_flower start1 close_flower start1
        | FOR OPEN_BRACK varDecF ExpF SEMICOLON ExpF CLOSE_BRACK SEMICOLON start1 
        | FOR OPEN_BRACK SEMICOLON ExpF SEMICOLON ExpF CLOSE_BRACK open_flower start1 close_flower start1
        | FOR OPEN_BRACK SEMICOLON ExpF SEMICOLON ExpF CLOSE_BRACK SEMICOLON start1 

while : WHILE OPEN_BRACK ExpF CLOSE_BRACK open_flower start1 close_flower start1
        | WHILE OPEN_BRACK ExpF CLOSE_BRACK SEMICOLON start1

varDecF : type ID options D SEMICOLON 
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

arrayDeclr : type ID BOX SEMICOLON
BOX : BOX OPEN_SQ INTEGER CLOSE_SQ | OPEN_SQ INTEGER CLOSE_SQ
arrayInitial : type ID BOX EQUALTO open_flower BALANCED_BRACK close_flower SEMICOLON | type ID BOX EQUALTO open_flower close_flower SEMICOLON
BALANCED_BRACK : arrayParams_unend 
            | arrayParams_unend COMMA
            | arrayParams_unend COMMA open_flower BALANCED_BRACK close_flower COMMA BALANCED_BRACK
            | arrayParams_unend COMMA open_flower BALANCED_BRACK close_flower COMMA
            | arrayParams_unend COMMA open_flower BALANCED_BRACK close_flower     
            | open_flower BALANCED_BRACK close_flower
            | open_flower BALANCED_BRACK close_flower COMMA 
            | open_flower BALANCED_BRACK close_flower COMMA BALANCED_BRACK
arrayParams_unend : INTEGER | arrayParams_unend COMMA INTEGER 

arrayAsAParameter : OPEN_SQ CLOSE_SQ higherDimention
higherDimention : BOX | 

pointerAsAParameter : PTR_TYPE PTR_STAR ID

PTR_DECLR : PTR_TYPE PTR_STAR ID SEMICOLON
PTR_INITIAL : PTR_TYPE PTR_STAR ID EQUALTO AMPERSAND ID SEMICOLON | PTR_TYPE PTR_STAR ID EQUALTO ID SEMICOLON | PTR_TYPE PTR_STAR ID EQUALTO PTR_EXP SEMICOLON
PTR_STAR : PTR_STAR MUL | MUL
PTR_TYPE : userDefDataType ID | type | VOID 
PTR_EXP : OPEN_BRACK PTR_TYPE PTR_STAR CLOSE_BRACK MALLOC OPEN_BRACK SIZEOF OPEN_BRACK PTR_TYPE PTR_STAR CLOSE_BRACK CLOSE_BRACK 
        | OPEN_BRACK PTR_TYPE PTR_STAR CLOSE_BRACK MALLOC OPEN_BRACK SIZEOF OPEN_BRACK PTR_TYPE CLOSE_BRACK CLOSE_BRACK

switch : SWITCH OPEN_BRACK ID CLOSE_BRACK open_flower switchcase default close_flower start1
switchcase : CASE comp COLON start1 switchcase | 
default : DEFAULT COLON start1 | 
comp : CHAR_CONST | INTEGER

ifElseLadder: S 
S: matched | unmatched 
matched: IF OPEN_BRACK Exp CLOSE_BRACK open_flower start1 close_flower elif ELSE open_flower start1 close_flower 
elif : ELIF OPEN_BRACK Exp CLOSE_BRACK open_flower start1 close_flower elif | 
unmatched: IF OPEN_BRACK Exp CLOSE_BRACK open_flower start1 close_flower elif

userTypeDefination : TYPEDEF userDefDataType ID open_flower userTypeParams close_flower userTypeObj SEMICOLON startGlobal | userDefDataType ID open_flower userTypeParams close_flower userTypeObj SEMICOLON startGlobal
userTypeParams : type ID higherDimention SEMICOLON userTypeParams  
                | pointerAsAParameter SEMICOLON userTypeParams
                | userDefDataType ID ID SEMICOLON userTypeParams
                | type ID higherDimention SEMICOLON
                | pointerAsAParameter SEMICOLON
                | userDefDataType ID ID SEMICOLON
userTypeObj : ID | userTypeObj COMMA ID | 
userTypeDeclaration : userDefDataType ID ID SEMICOLON | ID ID SEMICOLON
userTypeInitialization : userDefDataType ID ID EQUALTO open_flower params close_flower SEMICOLON
                        | ID DOT ID EQUALTO item SEMICOLON
                        | ID ARROW ID EQUALTO item SEMICOLON

userDefDataType : STRUCT | UNION

%%

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