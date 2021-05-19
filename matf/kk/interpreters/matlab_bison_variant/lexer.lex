%option noinput
%option nounput
%option noyywrap

%{
#include <iostream>
#include <cstdlib>
#include <string>
#include "matrica.hpp"
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

"disp" { return yy::parser::make_disp_token(loc); }
"size" { return yy::parser::make_size_token(loc); }
[0-9]+ { 
	int val = strtol(yytext, NULL, 10);
	return yy::parser::make_int_token(val, loc);
}

".+" { return yy::parser::make_elwise_plus_token(loc); }
".*" { return yy::parser::make_elwise_mul_token(loc); }
"*" { return yy::parser::make_mul_token(loc); }
"'" { return yy::parser::make_transp_token(loc); }
{ID} { return yy::parser::make_id_token(yytext, loc); }
"[" { return yy::parser::make_sqr_lparen_token(loc); }
"]" { return yy::parser::make_sqr_rparen_token(loc); }
"(" { return yy::parser::make_lparen_token(loc); }
")" { return yy::parser::make_rparen_token(loc); }
"," { return yy::parser::make_comma_token(loc); }
";" { return yy::parser::make_semicol_token(loc); }
"+" { return yy::parser::make_plus_token(loc); }
"-" { return yy::parser::make_minus_token(loc); }
"<" { return yy::parser::make_lt_token(loc); }
">" { return yy::parser::make_gt_token(loc); }
"=" { return yy::parser::make_assign_token(loc); }

[ \t] { loc.step(); }
"\n"+ { loc.lines(yyleng); loc.step(); 
	return yy::parser::make_newline_token(loc);
 }

. { 
	throw yy::parser::syntax_error(loc,
		"Lexical error, invalid character: " + std::string(yytext));
}

<<EOF>>	{ return yy::parser::make_eof_token(loc); }

%%
