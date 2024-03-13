# CompilerDesignLabProject

We have implemented the **Lexical Analysis Phase, Syntax Analysis Phase, and Semantic Analysis Phase** of the C Language Compiler Design.
The tools used for Lexical Analysis is "Flex" and for Syntax Analysis Phase is "Bison".

## Installation 
Flex can be installed for _Windows_ using this [link](https://gnuwin32.sourceforge.net/packages/flex.htm).\n
Bison can be installed for _Windows_ using this [link](https://gnuwin32.sourceforge.net/packages/bison.htm).

## Execution of Code
### Flex
Lex file has an extension of '.l'. Executing the flex file will generate lex.yy.c, which must be compiled using gcc.
```
flex lexicalAnalysis.l
gcc lex.yy.c
.\a.exe
```
### Bison
Yacc file has an extension of 'y'. Execution of .y file generates y.tab.c and y.tab.h
```
bison -dy semanticAnalysis.y
flex semanticAnalysis.l
gcc lex.yy.c y.tab.c
.\a.exe
```
