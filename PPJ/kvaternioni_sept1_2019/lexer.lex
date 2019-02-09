%option nounput
%option noinput
%option noyywrap

%{
#include <iostream>
#include <string>
#include "kvaternion.hpp"
#include "parser.tab.hpp"
%}

%%

def { return def_token; }
print { return print_token; }
norm { return norm_token; }
:= { return dodela_token; }
%[qsijk] { yylval.char_type = yytext[1]; return komp_print_id_token; }
[a-z] { yylval.char_type = *yytext; return id_token; }
[0-9]+(\.[0-9]+)? { yylval.float_type = atof(yytext); return broj_token; }
[-+*/()";=,:%] { return *yytext; }
[\t\n ] { }
. {
	std::cerr << "Leksicka greska: " << std::string(yytext) << std::endl;
	exit(EXIT_FAILURE);	
}

%%
