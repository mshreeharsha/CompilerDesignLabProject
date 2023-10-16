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
\#[ \t]*include {return INCLUDE;}
\<[a-zA-Z]+\.h\> {return PREDEF_HEADER;}
[a-zA-Z_][a-zA-Z0-9_]{0,30} {return ID;}
-?[1-9][0-9]{1,8}|1[0-9]{1,9}|-?2[0-1][0-4][0-7][0-4][0-8][0-3][0-6][0-4][0-7]|0 {return INTEGER;}
[-]?[0-9]+\.[0-9]{1,6} {return FLOATING_NUM;}
\/\/[^\n]* {return SL_COMMENT;}
\/\*[^*/]*\*\/ {return ML_COMMENT;}
\"[^\n]*\" {return STRING;}
['].['] {return CHAR_CONST;}
\= {return EQUALTO;}
\( {return OPEN_BRACK;}
\) {return CLOSE_BRACK;}
\{ {return OPEN_FLOWER;}
\} {return CLOSE_FLOWER;}
\[ {return OPEN_SQ;}
\] {return CLOSE_SQ;}
\& {return AND;}
\+\+|\-\- {return UNARY_OP;}
\+|\-|\*|\/|\% {return AR_OP;}
\|\||\&\& {return LOG_OP;}
\||\^|\! {return BIT_OP;}
\=\=|\<\=|\>\=|\!\=|\<|\> {return REL_OP;}
; {return SEMICOLON;}
, {return COMMA;}
[\n]+ {return NEWLINE;}
[ \t]+ ;
. {return *yytext;}
%%

int yywrap(){
    return 1;
}
