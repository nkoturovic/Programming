%option noinput
%option nounput
%option noyywrap

%{
#include <iostream>
#include <cstdlib>
#include <string>
#include "parser.tab.hpp"
#include "driver.hpp"
static yy::location loc;
%}

%{
/* Code run each time pattern is matched */
#define YY_USER_ACTION loc.columns(yyleng);
%}

ID [a-zA-Z][a-zA-Z_0-9]*

%%

%{
/* Code run each time yylex() is called */
loc.step();
%}

"print" { return yy::parser::make_print_token(loc); }
[0-9]+ { 
	int val = strtol(yytext, NULL, 10);
	return yy::parser::make_int_token(val, loc);
}

"(" { return yy::parser::make_lparen_token(loc); }
")" { return yy::parser::make_rparen_token(loc); }
";" { return yy::parser::make_separator_token(loc); }
"+" { return yy::parser::make_plus_token(loc); }
":=" { return yy::parser::make_assign_token(loc); }
{ID} { return yy::parser::make_id_token(yytext, loc); }


[ \t] { loc.step(); }
[\n]+ { loc.lines(yyleng); loc.step(); }
. { 
	throw yy::parser::syntax_error(loc,
	 "Lexical error, invalid character: " + std::string(yytext));
}

<<EOF>>	{ return yy::parser::make_eof_token(loc); }

%%
