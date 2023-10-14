%{
    #include <stdio.h>
    int yylex();
    extern FILE*yyin;
%}

%%

%%

imt main(){

    yyparse();
}