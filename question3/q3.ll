%option noyywrap nodefault case-insensitive
%{
#include "AST.hpp"
#include "q3_parser.hpp"
%}

%x COLUMN_NAMES
%x TABLE_NAME

UCN (\\U[0-9a-fA-F]{4}|\\U[0-9a-fA-F]{8})

%%

"select" { BEGIN(COLUMN_NAMES); return SELECT; }

<COLUMN_NAMES>"from" { BEGIN(TABLE_NAME); return FROM; }

<COLUMN_NAMES>"," {return yytext[0];}

<COLUMN_NAMES>([_a-zA-Z]|{UCN})([_a-zA-Z0-9]|{UCN})*  { yylval.id = new string(yytext); return COLUMN; }

<COLUMN_NAMES>[ \t]+  { }

<TABLE_NAME>"where" { BEGIN(INITIAL); return WHERE; }

<TABLE_NAME>([_a-zA-Z]|{UCN})([_a-zA-Z0-9]|{UCN})*  { yylval.id = new string(yytext); return TABLE; }

<TABLE_NAME>[ \t]+  { }

"=" { return yytext[0]; }

"and" { return AND; }

"or" { return OR; }

"not" { return NOT; }

[ \t]+  { }

[\n|\r|\r\n] { return EOL; }

([_a-zA-Z0-9]|{UCN})+  { yylval.id = new string(yytext); return NAME; }

. {std::cout<<"ERROR\n";}
%%
