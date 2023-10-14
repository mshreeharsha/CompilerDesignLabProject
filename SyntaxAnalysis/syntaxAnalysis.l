%{
    #include <stdio.h>
    #include "y.tab.h"
%}

%%
[a-zA-Z_][a-zA-Z0-9_]{0,30} {return ID;}
%%

int yywrap(){
    return 1;
}
