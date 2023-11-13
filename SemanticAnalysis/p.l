%{
    #include <stdio.h>
    #include <string.h>
    #include "y.tab.h"    
    int yylinenumber=1;
%}

%%
\+ {return PLUS;}
int|float|char|double|long|unsigned {yylval.type=strdup(yytext);return TYPE;}
\= {return EQUAL;}
[a-zA-Z_][a-zA-Z0-9_]{0,30} {yylval.value=strdup(yytext);return ID;}
-?[1-9][0-9]{0,8}|-?1[0-9]{0,9}|-?2[0-1][0-4][0-7][0-4][0-8][0-3][0-6][0-4][0-7]|0 {yylval.type=strdup("int");return INTEGER;}
\n {yylinenumber++;}
[ \t]+ ;
. {return *yytext;}
%%

int yywrap(){
    return 1;
}