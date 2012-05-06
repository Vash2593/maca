%option noyywrap nounput debug

%{
#include <string>
#include <cassert>
#include <iostream>
#include <ctlparse/ctl.hh>
#include <boost/lexical_cast.hpp>

#define LINE(Line)				\
  do{						\
    yylloc->end.column = 1;			\
    yylloc->lines(Line);                        \
 } while (false)

#define YY_USER_ACTION				\
  yylloc->columns(yyleng);

#define TOK(Token)                              \
  ctl::parser::token::Token

%}

id      ([a-zA-Z0-9]+)
digit   ([0-9]+)
eol     (\n|\n\r|\r\n|\r)

%%

%{
  unsigned open_brace = 0;
  std::string *sval = 0;
  unsigned int ival = 0;

  yylloc->step();
%}

"!"           return TOK(NEG);
"("           return TOK(LPAREN);
")"           return TOK(RPAREN);
","           return TOK(COMMA);
"true"        return TOK(TRUE);
"false"       return TOK(FALSE);

{eol}         LINE();

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


%%

namespace ctl
{
  int
  ctlyyopen(const std::string &name)
  {
    if (name == "-")
      {
        yyin = stdin;
      }
    else
      {
        yyin = fopen(name.c_str(), "r");
        if (!yyin)
	  return 1;
      }
    return 0;
  }

  void
  ctlyyclose()
  {
    fclose(yyin);
  }
}


// Local Variables:
// mode: C++
// End:
