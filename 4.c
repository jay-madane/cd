// lex
%{
#include "y.tab.h"
%}

%%
if              { return IF; }
else            { return ELSE; }
[ \t\n]         ; // Ignore whitespace
.               ;
%%

int yywrap() {
    return 1;
}

//yacc
%{
#include <stdio.h>
#include <stdlib.h>
int yylex();
void yyerror(const char *);

%}

%token IF ELSE
%token <sval> EXPRESSION

%%
statement: IF EXPRESSION '{' statement '}' ELSE '{' statement '}'
         | IF EXPRESSION '{' statement '}'
         ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Syntax Error: %s\n", s);
}

int main() {
    yyparse();
    return 0;
}

// yacc -d calc.yacc
// lex calc.lex
// cc y.tab.c lex.yy.c
// a.out