%option noyywrap
%option nounput
%option noinput

%{
#include <iostream>
#include <algorithm>
#include "matrica.hpp"
#include "parser.tab.hpp"

std::string to_lower(std::string str) {
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}

%}

%%
disp { return disp_token; }
size { return size_token; }
[0-9]+ { yylval.int_type =  atoi(yytext); return int_token; }
[a-zA-Z]+ { yylval.string_type = new std::string(to_lower(yytext)); return id_token; }
' { return transp_token; }
\.\+ { return elwise_plus; }
\.\* { return elwise_mul; }
\* { return mul_token; }
[-<>+\[\]()*=/.;,'\n] { return *yytext; }
[ \t] { }
. { 
	std::cerr << "Leksicka greska: " << *yytext << std::endl;
	exit(EXIT_FAILURE);
}

%%
