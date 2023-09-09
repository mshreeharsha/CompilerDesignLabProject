%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TABLE_SIZE 100000
#define MAX_SYMBOLS 100000

char * locations[MAX_SYMBOLS];
int symTableSize=0;

struct SymbolTableEntry {
    char * name; //identifier
    char * type;
    int size;
    struct SymbolTableEntry * next;
};

struct SymbolTable {
    struct SymbolTableEntry * symTable[TABLE_SIZE];
};

struct SymbolTable Table;

//Hash Function
int hashfunction(char *s) {
    int pp = 101;
    int mod = 100000;
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

// Function to insert a key-value pair into the SymbolTable
void insert(char* key,char * type) {
    int index = hashfunction(key);

    // Create a new entry
    struct SymbolTableEntry* new_entry = (struct SymbolTableEntry*)malloc(sizeof(struct SymbolTableEntry));

    new_entry->name = strdup(key); // Duplicate the key string
    new_entry->type = strdup(type); // Duplicate the type string
    new_entry->size = strlen(key); 
    new_entry->next = Table.symTable[index];

    Table.symTable[index] = new_entry;
    locations[symTableSize++]=strdup(key);
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

%}

%%
^"#include"[ ]*<.+\.h> {printf("Header Line\n");}

auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|for|goto|if|inline|int|long|register|restrict|return|short|signed|sizeof|static|struct|switch|typedef|union|unsigned|void|volatile|while {printf("Keyword\n");};

[a-zA-z_][a-zA-Z0-9_]* {
    char * buffer = (char*)malloc(strlen(yytext) + 1);
    strcpy(buffer,yytext);
    printf("Identifier : %s\n",buffer);
    struct SymbolTableEntry* found= lookup(buffer);
    if(found==NULL){
        insert(buffer,"Identifier");
    }
    free(buffer);
}

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
    yylex();
    
    printf("%-20s  %-10s  %-10s\n", "Identifier", "Size", "Type");
    printf("----------------------------------------------\n");

    for (int i = 0; i < symTableSize; i++) {
        struct SymbolTableEntry * entry = lookup(locations[i]);
        printf("%-20s  %-10d  %-10s\n", entry->name, entry->size, entry->type);
    }
    fclose(yyin);
    return 0;
}