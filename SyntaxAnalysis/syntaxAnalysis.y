%{
    #include <stdio.h>
    int yylex();
    extern FILE*yyin;
    int yyerror(char const * s);
%}

%token INCLUDE PREDEF_HEADER STRING ELIF ELSE IF BREAK NOT FOR CONTINUE WHILE TYPE SWITCH CASE STRUCT UNION RETURN ID INTEGER FLOATING_NUM SL_COMMENT ML_COMMENT CHAR_CONST EQUALTO OPEN_BRACK OPEN_FLOWER OPEN_SQ CLOSE_BRACK CLOSE_FLOWER CLOSE_SQ AND UNARY_OP PLUS MINUS DIV MUL MOD OR AMPERSAND BIT_OR BIT_XOR SEMICOLON COMMA ISEQUALTO LT LTE GT GTE NE PLUS_ET MINUS_ET MUL_ET DIV_ET OR_ET AND_ET XOR_ET

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
start: header varDec {printf("Syntax is Correct\n");}

varDec : TYPE ID options D SEMICOLON dec | ID options D SEMICOLON dec
dec : varDec | 
D : COMMA ID options D | 
options : EQUALTO Exp | 

header: INCLUDE file newHeader
newHeader: header | 
file : STRING | PREDEF_HEADER 

Exp: OPEN_BRACK Exp CLOSE_BRACK | Exp PLUS Exp | Exp MINUS Exp | Exp MUL Exp | Exp DIV Exp | Exp MOD Exp | Exp OR Exp | Exp AND Exp | Exp BIT_XOR Exp | Exp AMPERSAND Exp | Exp UNARY_OP | UNARY_OP Exp | NOT Exp | Exp BIT_OR Exp | Exp ISEQUALTO Exp| Exp LT Exp| Exp LTE Exp| Exp GT Exp| Exp GTE Exp| Exp NE Exp| Exp PLUS_ET Exp| Exp MINUS_ET Exp| Exp MUL_ET Exp| Exp DIV_ET Exp| Exp OR_ET Exp| Exp AND_ET Exp| Exp XOR_ET Exp|ID | INTEGER 

%%

int yyerror(char const * s){
    printf("Error in Code\n");
}

int main(){
    yyin=fopen("input.txt","r");
    yyparse();
    fclose(yyin);
}