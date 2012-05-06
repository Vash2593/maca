%option noyywrap nounput debug

%{
#include <string>
#include <cassert>
#include <iostream>
#include "kripke.hh"
#include <boost/lexical_cast.hpp>

#define LINE(Line)				\
  do{						\
    yylloc->end.column = 1;			\
    yylloc->lines(Line);                        \
 } while (false)

#define YY_USER_ACTION				\
  yylloc->columns(yyleng);

#define TOK(Token)                              \
  kripke::parser::token::Token

%}

id      ([a-zA-Z0-9]*)
digit   ([0-9]*)
eol     (\n|\n\r|\r\n)

%%

%{
  unsigned open_brace = 0;
  std::string *sval = 0;
  unsigned int ival = 0;

  yylloc->step();
%}

<INITIAL>{

  "!"           return TOK(NEG);

  {eol}         return TOK(EOL);

  {digit}       {
    try
      {
        yylval->uval = boost::lexical_cast<unsigned int>(yytext);
      }
    catch (std::bad_cast& e)
      {
        assert(false);
        yylval->uval = 0;
      }
    return TOK(DIGIT);
  }

  {id}          yylval->sval = new std::string(yytext); return TOK(ID);

}


%%

// Local Variables:
// mode: C++
// End:
