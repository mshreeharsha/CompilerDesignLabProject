%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TABLE_SIZE 100000

int locations[TABLE_SIZE];
int symTableSize=0;

struct SymbolTableEntry {
    char * name; //identifier
    int size;
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
void insert(char* key) {
    int index = hashfunction(key);

    // Create a new entry
    struct SymbolTableEntry* new_entry = (struct SymbolTableEntry*)malloc(sizeof(struct SymbolTableEntry));

    new_entry->name = strdup(key); // Duplicate the key string
    new_entry->size = strlen(key); 

    Table.symTable[index] = new_entry;
    locations[symTableSize++]=index;
}

// Function to Lookup
struct SymbolTableEntry *  lookup(char* key) {
    int index = hashfunction(key);
    struct SymbolTableEntry* entry = Table.symTable[index];
    // Search for the key in the linked list at the specified index
    if (entry!=NULL && strcmp(entry->name, key) == 0) {
        return entry; 
    }
    // Key not found
    return NULL;
}

#include <stdbool.h>

bool isKeyword(char* text) {
    char* keywords[] = {
        "auto", "break", "case", "char", "const", "continue", "default",
        "do", "double", "else", "enum", "extern", "float", "for", "goto",
        "if", "inline", "int", "long", "register", "restrict", "return",
        "short", "signed", "sizeof", "static", "struct", "switch", "typedef",
        "union", "unsigned", "void", "volatile", "while"
    };

    int n = sizeof(keywords) / sizeof(keywords[0]);

    for (int i=0;i<n;i++) {
        if (strcmp(text,keywords[i]) == 0) {
            return true; 
        }
    }
    return false; 
}


%}

%%
^"#include"[ ]*<.+\.h> {printf("Header Line\n");}

[a-zA-z_][a-zA-Z0-9_]* {
    char * buffer = (char*)malloc(strlen(yytext) + 1);
    strcpy(buffer,yytext);
    if(isKeyword(buffer)){
        printf("Keyword\n");
    }
    else{
        printf("%s\n",buffer);
        struct SymbolTableEntry* found= lookup(buffer);
        if(found==NULL){
            insert(buffer);
        }
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
    
    printf("%-20s  %s\n", "Identifier", "Size");
    printf("--------------------------------------\n");

    for (int i = 0; i < symTableSize; i++) {
        printf("%-20s  %d\n", Table.symTable[locations[i]]->name, Table.symTable[locations[i]]->size);
    }
    fclose(yyin);
    return 0;
}