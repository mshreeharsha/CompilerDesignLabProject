%{
    #include <stdio.h>
    int yylex();
    extern FILE*yyin;
    int yyerror(char const * s);
%}

%token INCLUDE NEWLINE PREDEF_HEADER STRING ELIF ELSE IF BREAK FOR CONTINUE WHILE TYPE SWITCH CASE STRUCT UNION RETURN ID INTEGER FLOATING_NUM SL_COMMENT ML_COMMENT CHAR_CONST EQUALTO OPEN_BRACK OPEN_FLOWER OPEN_SQ CLOSE_BRACK CLOSE_FLOWER CLOSE_SQ AND UNARY_OP AR_OP LOG_OP BIT_OP REL_OP SEMICOLON COMMA 

%%
start: header {printf("Syntax for Header File is Correct\n");return -1;}
header: INCLUDE file NEWLINE newHeader
newHeader: header | 
file : STRING | PREDEF_HEADER 
%%

int yyerror(char const * s){
    printf("Error in Code\n");
}

int main(){
    yyin=fopen("input.txt","r");
    yyparse();
    fclose(yyin);
}