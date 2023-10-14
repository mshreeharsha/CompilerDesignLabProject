%{
    #include <stdio.h>
    #include "y.tab.h"
%}

%%
if[ \t]+else {return ELIF;}
if {return IF;}
else {return ELSE;}
break {return BREAK;}
continue {return CONTINUE;}
for {return FOR;}
while {return WHILE;}
int|float|char|double|long|unsigned {return TYPE;}
switch {return SWITCH;}
case {return CASE;}
struct {return STRUCT;}
union {return UNION;}
return {return RETURN;}
\#include {return INCLUDE;}
[a-zA-Z_][a-zA-Z0-9_]{0,30} {return ID;}
-?[1-9][0-9]{1,8}|1[0-9]{1,9}|-?2[0-1][0-4][0-7][0-4][0-8][0-3][0-6][0-4][0-7]|0 {return INTEGER;}
\/\/[^\n]* {return SL_COMMENT}
['].['] {return CHAR_CONST}
\= {return EQUALTO;}
\< {return LT;}
\> {return GT;}
\( {return OPEN_BRACK;}
\) {return CLOSE_BRACK;}
\{ {return OPEN_FLOWER;}
\} {return CLOSE_FLOWER;}
\[ {return OPEN_SQ;}
\] {return CLOSE_SQ;}
\+\+|\-\- {return UNARY_OP;}
\+|\-|\*|\/|\% {return AR_OP}
; {return SEMICOLON;}
, {return COMMA;}
\"[^\n]*\" {return STRING;}
%%

int yywrap(){
    return 1;
}
