%{
    #include<stdio.h>
    int yylex();
    int yyerror(char * s);
    extern FILE * yyin;
    extern char *yytext;
    extern int yylinenumber;

    #include <string.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #define TABLE_SIZE 100003
    #define MAX_SYMBOLS 1000000

    //Scope Number
    int scope=1; //Scope of Global Variables = 1

    //Datatypes
    char datatypesArray[][20]={"int","char","float"};
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

    struct SymbolTableEntry* insert(char* key,char * type,char * dataType,int dimension,int linenumber,int scope) {
        int index = hashfunction(key);

        // Create a new entry
        struct SymbolTableEntry* new_entry = (struct SymbolTableEntry*)malloc(sizeof(struct SymbolTableEntry));

        new_entry->name = strdup(key); // Duplicate the key string
        new_entry->type = strdup(type); // Duplicate the string type
        new_entry->dataType=strdup(dataType); //Duplicate the dataType of the String
        new_entry->lineOfDeclaration=linenumber;
        new_entry->scope=scope;
        new_entry->dimension=dimension;

        new_entry->next = Table.symTable[index];

        new_entry->head = (struct lines *)malloc(sizeof(struct lines));
        new_entry->head->lineno = linenumber;
        new_entry->head->next = NULL;
        new_entry->tail = new_entry->head;

        Table.symTable[index] = new_entry;
        locations[symTableSize++]=strdup(key);

        return new_entry;
    }

    //Function to append an entry for key-value pair that already exists in the SymbolTable
    void update(struct SymbolTableEntry* entry,int linenumber){
        
        struct lines * new_node = (struct lines *)malloc(sizeof(struct lines));
        new_node->lineno = linenumber;
        new_node->next = NULL;
        entry->tail->next = new_node;
        entry->tail = new_node;
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

    struct SymbolTableEntry * varDecArray[100];
    int index=0;

    void rem(int sc){
        
    }
    //start globalVarDec startGlobal DG optionsG main mainParameters start1 varDec D options header newHeader file Exp function_declaration function_call function_defn parameter_list choice item params for while varDecF ExpF print printExpr printArguments printContent scanf scanfArguments scanfContent scanfExpr dimension BOX BALANCED_BRACK arrayElement arrayInitial arrayDeclr arrayAsAParameter arrayParams_unend higherDimention pointerAsAParameter PTR_DECLR PTR_EXP PTR_INITIAL PTR_STAR PTR_TYPE switch switchcase default comp ifElseLadder matched S elif unmatched userDefDataType userTypeDeclaration userTypeDefination userTypeInitialization userTypeObj userTypeParams
%}

%union{
    char * value;
    char * type;
}

%type<type> E

%token<value> ID
%token<type> INTEGER TYPE  
%token PLUS EQUAL

%%
start: Dec Dec E {printf("Accepted\n");}
Dec : TYPE ID EQUAL INTEGER {
    char type[10]="variable";
    struct SymbolTableEntry* new_entry=insert($2,type,$1,1,yylinenumber,1);
}
E : E PLUS E {
    if(strcmp($1,$3)!=0){
        int res=yyerror("Not Compartible");
        return -1;
    }
}
   | ID {struct SymbolTableEntry * found=lookup($1,scope,false);
        if(found==NULL){
            char const errorMessage[100]="Variable Not Declared!!";
            int a=yyerror(errorMessage);
            return -1;
        }
        else{
            $$=malloc(strlen(found->dataType)+1);
            strcpy($$,found->dataType);
        }
    }
   | INTEGER {
        $$=malloc(strlen($1)+1);
        strcpy($$,$1);
   }
%%

int yyerror (char *s){
    printf("Error %s!! \n Line No : %d\n",s,yylinenumber);
}

int main(){
    yyin=fopen("test.c","r");
    yyparse();
    fclose(yyin);
}
