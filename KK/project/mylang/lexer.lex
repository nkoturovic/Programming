%option noinput
%option nounput
%option noyywrap

%{
#include <iostream>
#include <cstdlib>
#include <string>
#include "structs.hpp"
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
{ID} { return yy::parser::make_id_token(yytext, loc); }
"{" { return yy::parser::make_crl_lparen_token(loc); }
"}" { return yy::parser::make_crl_rparen_token(loc); }
"[" { return yy::parser::make_sqr_lparen_token(loc); }
"]" { return yy::parser::make_sqr_rparen_token(loc); }
"(" { return yy::parser::make_lparen_token(loc); }
")" { return yy::parser::make_rparen_token(loc); }
"," { return yy::parser::make_comma_token(loc); }
";" { return yy::parser::make_separator_token(loc); }
"+" { return yy::parser::make_plus_token(loc); }
"*" { return yy::parser::make_mul_token(loc); }
"-" { return yy::parser::make_minus_token(loc); }
"==" { return yy::parser::make_eq_token(loc); }
"<=" { return yy::parser::make_leq_token(loc); }
">=" { return yy::parser::make_geq_token(loc); }
"<" { return yy::parser::make_lt_token(loc); }
">" { return yy::parser::make_gt_token(loc); }
"=" { return yy::parser::make_assign_token(loc); }

[1-9][0-9]* { 
	int val = strtol(yytext, NULL, 10);
	return yy::parser::make_int_token(val, loc);
}

"0"[0-9]+ { 
	long val = strtol(yytext, NULL, 8);
	return yy::parser::make_int_token(val, loc);
}

"0x"[0-9]+ { 
	int val = strtol(yytext, NULL, 16);
	return yy::parser::make_int_token(val, loc);
}

[\t ] { 
    loc.step(); 
}

"\n" { 
    loc.lines(yyleng); loc.step(); 
 }

. { 
	throw yy::parser::syntax_error(loc,
		"Lexical error, invalid character: " + std::string(yytext));
}

<<EOF>>	{ return yy::parser::make_eof_token(loc); }

%%
