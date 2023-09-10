%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TABLE_SIZE 100003
#define MAX_SYMBOLS 1000000

int line_num = 1;

char * locations[MAX_SYMBOLS];
int symTableSize=0;

struct lines{
    int lineno; // stores the line-number
    struct lines*next;
};
struct SymbolTableEntry {
    char * name; //identifier
    char * type;
    int size;
    struct SymbolTableEntry * next;
    struct lines * head; //head of the linenumbers list
    struct lines *  tail; //tail of the linenumbers list
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
void insert1(char* key,char * type,int linenumber) {
    int index = hashfunction(key);

    // Create a new entry
    struct SymbolTableEntry* new_entry = (struct SymbolTableEntry*)malloc(sizeof(struct SymbolTableEntry));

    new_entry->name = strdup(key); // Duplicate the key string
    new_entry->type = strdup(type); // Duplicate the type string
    new_entry->size = strlen(key); 
    new_entry->next = Table.symTable[index];
    new_entry->head = (struct lines *)malloc(sizeof(struct lines));
    new_entry->head->lineno = linenumber;
    new_entry->head->next = NULL;
    new_entry->tail = new_entry->head;
    Table.symTable[index] = new_entry;
    locations[symTableSize++]=strdup(key);
}

//Function to append an entry for key-value pair that already exists in the SymbolTable
void insert2(struct SymbolTableEntry* entry,int linenumber){
    struct lines * new_node = (struct lines *)malloc(sizeof(struct lines));
    new_node->lineno = linenumber;
    new_node->next = NULL;
    entry->tail->next = new_node;
    entry->tail = new_node;
}

// Function to Lookup
struct SymbolTableEntry *  lookup(char* key) {
    int index = hashfunction(key);
    struct SymbolTableEntry* entry = Table.symTable[index];
    while(entry != NULL)
        {
            if(strcmp(entry->name,key) == 0)
            {
                return entry;
            } 
            entry = entry->next;
        }
        // Key not found
        return NULL;
}

void processToken(const char* token,char *category,int linenumber) {
    char* buffer = (char*)malloc(strlen(token) + 1);
    strcpy(buffer, token);
    //printf("%s : %s\n", category, buffer);
    struct SymbolTableEntry* found = lookup(buffer);
    if (found == NULL) {
        insert1(buffer, category,linenumber);
    }
    else{
        insert2(found,linenumber);
    }
    free(buffer);
}

%}

%%
^"#include"[ ]*<.+\.h> {fprintf(yyout,"%30s \t--->\tHEADER FILE \t%20d\n", yytext,line_num);}

\n {line_num++;}

auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|for|goto|if|inline|int|long|register|restrict|return|short|signed|sizeof|static|struct|switch|typedef|union|unsigned|void|volatile|while {fprintf(yyout,"%30s \t--->\tKEYWORD \t%24d\n", yytext,line_num);};

[a-zA-Z_][a-zA-Z0-9_]{0,30} {
    processToken(yytext, "Identifier", line_num);
    fprintf(yyout, "%30s \t--->\tIDENTIFIER \t%22d\n", yytext, line_num);
}

[-]?[0-9]+[_\$\#:?][0-9_\$\#:?]* {
   printf("\n\nERROR : Constant '%s' is invalid\nline no : %d", yytext, line_num);
}

[a-zA-Z_][a-zA-Z0-9_]{30,} {
    printf("\n\nERROR : Identifier '%s' is too long\nline no : %d", yytext, line_num);
}

[-]?[1-9][0-9]{0,8}|214748364[0-7]|0 {
    processToken(yytext,"Integer Constants",line_num);
    fprintf(yyout,"%30s \t--->\tINTERGER CONSTANT \t%14d\n", yytext,line_num);
}

[-]?([1-9][0-9]{9,}|[2-9][0-9]{9,}|214748364[8-9]) {
    printf("\n\nERROR : Integer Limit Exceed\nline no : %d",line_num);
}

[0-9]+[a-zA-Z_]+|[a-zA-Z0-9_\$\#:?]+[\$\#:?]*[a-zA-Z0-9_\$\#:?] {
    printf("\n\nERROR : Identifier '%s' is invalid\nline no : %d", yytext, line_num);
}

['].['] {
    fprintf(yyout,"%30s \t--->\tCHARACTER CONSTANT \t%13d\n", yytext,line_num);
}

[-]?[0-9]+\.[0-9]{1,6} {
    processToken(yytext,"Floating-Point Constants",line_num);
    fprintf(yyout,"%30s \t--->\tFLOATING-POINT CONSTANT \t%30d\n", yytext,line_num);
}

["][^\n]*["] {
    processToken(yytext,"String Literal",line_num);
    fprintf(yyout,"%30s \t--->\tSTRING LITERAL \t%18d\n", yytext,line_num);
}

\(|\)|\{|\} {fprintf(yyout,"%30s \t--->\tPARENTHESIS \t%20d\n", yytext,line_num+1);}

[;] {fprintf(yyout,"%30s \t--->\tSEMICOLON \t%22d\n", yytext,line_num+1);}

[,] {fprintf(yyout,"%30s \t--->\tCOMMA \t%28d\n", yytext,line_num+1);}

\+|\-|\*|\/|\% {fprintf(yyout,"%30s \t--->\tARITHMETIC OPERATOR \t%12d\n", yytext,line_num+1);}

\+\+|\-\- {fprintf(yyout,"%30s \t--->\tUNARY OPERATOR \t%18d\n", yytext,line_num+1);}
 
\|\||\&\& {fprintf(yyout,"%30s \t--->\tLOGICAL OPERATOR \t%16d\n", yytext,line_num+1);}

\||\&|\^|\! {fprintf(yyout,"%30s \t--->\tBIT-WISE OPERATOR \t%14d\n", yytext,line_num+1);}

==|<=|>=|!=|<|> {fprintf(yyout,"%30s \t--->\tRELATIONAL OPERATOR \t%12d\n", yytext,line_num+1);}

= {fprintf(yyout,"%30s \t--->\tASSIGNMENT OPERATOR \t%12d\n", yytext,line_num+1);}

\/\/.* {fprintf(yyout,"%30s \t--->\tSINGLELINE COMMENT \t%14d\n",yytext,line_num+1);}

(\/\*)(.|\n)+? {printf("\n\nERROR : Invalid Comment '%s' \nline no : %d", yytext, line_num);}

.|\n ;

%%

int yywrap(){
    return 1;
}

int main(){
    for (int i=0; i<TABLE_SIZE;i++) {
        Table.symTable[i] = NULL;
    }
    yyin = fopen("input.txt","r");
    yyout=fopen("ListOfTokens.txt","w");
    fprintf(yyout,"\n-------------------------------------------------------------------------------------------------------\n");
    fprintf(yyout,"%30s \t--->\t %s \t%30s", "Lexeme", "Token","Line Number");
    fprintf(yyout,"\n-------------------------------------------------------------------------------------------------------\n");
    yylex();
    printf("\n\nSYMBOL TABLE\n\n");
    printf("%-15s  %-10s  %-20s  %-20s\n", "Identifier", "Size", "Type", "Line Numbers");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < symTableSize; i++) {
        struct SymbolTableEntry * entry = lookup(locations[i]);
        printf("%-15s  %-10d  %-20s  [ ", entry->name, entry->size, entry->type);
        struct lines* h = entry->head;
        while(h){
            printf("%d ", h->lineno);
            h = h->next;
        }
        printf("]\n");
    }
    printf("---------------------------------------------------------------\n");
    printf("\n\n");
    fclose(yyin);
    return 0;
}