%{
    #include <stdio.h>
    #include "y.tab.h"
    int yylinenumber=1;
    int intval = 0;
%}

%%
malloc {return MALLOC;}
sizeof {return SIZEOF;}
typedef {return TYPEDEF;}
else[ ]+if {return ELIF;}
NULL {return NULLT;}
if {return IF;}
else {return ELSE;}
break {return BREAK;}
continue {return CONTINUE;}
default {return DEFAULT;}
void {return VOID;}
for {return FOR;}
while {return WHILE;}
(int|void)[ ]+main[ ]*\( {return MAIN;}
(int|float|char|double|long|unsigned|void)[ ]+[a-zA-Z_][a-zA-Z0-9_]{0,30}[ ]*\( {
    yylval.value=strdup(yytext);
    return FUN_START;}
int|float|char|double|long|unsigned {yylval.type=strdup(yytext);return TYPE;}
switch {return SWITCH;}
case {return CASE;}
struct {yylval.type=strdup("struct");return STRUCT;}
union {yylval.type=strdup("union");return UNION;}
return {return RETURN;}
printf {return PRINTF;}
scanf {return SCANF;}
\#[ \t]*include {return INCLUDE;}
\<[a-zA-Z]+\.h\> {return PREDEF_HEADER;}
[a-zA-Z_][a-zA-Z0-9_]{0,30} {yylval.value=strdup(yytext);return ID;}
-?[1-9][0-9]{0,8}|-?1[0-9]{0,9}|-?2[0-1][0-4][0-7][0-4][0-8][0-3][0-6][0-4][0-7]|0 {
    int p = 1;
    intval = 0;
    for(int i =yyleng - 1;i>=0;i--)
    {
        intval += (yytext[i] - '0') * p;
        p*=10;
    }
    yylval.type=strdup("int");return INTEGER;
    }
[-]?[0-9]+\.[0-9]{1,6} {yylval.type=strdup("float");return FLOATING_NUM;}
\/\/[^\n]* {return SL_COMMENT;}
\/\*[^*/]*\*\/ {return ML_COMMENT;}
\"[^\n]*\" {yylval.type=strdup("string");return STRING;}
['].['] {yylval.type=strdup("char");return CHAR_CONST;}
\-\> {return ARROW;}
\. {return DOT;}
\= {return EQUALTO;}
\( {return OPEN_BRACK;}
\) {return CLOSE_BRACK;}
\{ {return OPEN_FLOWER;}
\} {return CLOSE_FLOWER;}
\[ {return OPEN_SQ;}
\] {return CLOSE_SQ;}
\& {return AMPERSAND;}
\+\+|\-\- {return UNARY_OP;}
\+ {return PLUS;}
\- {return MINUS;}
\* {return MUL;}
\/ {return DIV;}
\% {return MOD;}
\|\| {return OR;}
\&\& {return AND;}
\! {return NOT;}
\| {return BIT_OR;}
\^ {return BIT_XOR;}
\=\= {return ISEQUALTO;}
\<\= {return LTE;}
\>\= {return GTE;}
\!\= {return NE;}
\< {return LT;}
\> {return GT;}
\|\= {return OR_ET;}
\&\= {return AND_ET;}
\^\= {return XOR_ET;}
\+\= {return PLUS_ET;}
\-\= {return MINUS_ET;}
\*\= {return MUL_ET;}
\/\= {return DIV_ET;}
; {return SEMICOLON;}
, {return COMMA;}
: {return COLON;}
\n {++yylinenumber;};
[ \t]+ ;
. {return *yytext;}
%%

int yywrap(){
    return 1;
}
