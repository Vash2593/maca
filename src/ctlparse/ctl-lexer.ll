%option noyywrap nounput

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

#define DEC_KEYWORD(QKind, Kind)                \
QKind yylval->uval = Kind; return TOK(KEYWORD)


%}

id      ([a-zA-Z0-9]+)
digit   ([0-9]+)
eol     (\n|\n\r|\r\n|\r)

%%

%{
  unsigned open_brace = 0;
  std::string *sval = 0;
  unsigned int uval = 0;
  enum keyword_kind { AND, OR, NOT, IMPLIES,
                      AX, EX, AF, EF, AG, EG, AU, EU };

  yylloc->step();
%}

"!"             return TOK(NEG);
"("             return TOK(LPAREN);
")"             return TOK(RPAREN);
","             return TOK(COMMA);
"true"          return TOK(TRUE);
"false"         return TOK(FALSE);
"AND"           yylval->uval = AND; return TOK(KEYWORD);
"OR"            yylval->uval = OR; return TOK(KEYWORD);
"NOT"           yylval->uval = NOT; return TOK(KEYWORD);
"IMPLIES"       yylval->uval = IMPLIES; return TOK(KEYWORD);
"AX"            yylval->uval = AX; return TOK(KEYWORD);
"EX"            yylval->uval = EX; return TOK(KEYWORD);
"AF"            yylval->uval = AF; return TOK(KEYWORD);
"EF"            yylval->uval = EF; return TOK(KEYWORD);
"AG"            yylval->uval = AG; return TOK(KEYWORD);
"EG"            yylval->uval = EG; return TOK(KEYWORD);
"AU"            yylval->uval = AU; return TOK(KEYWORD);
"EU"            yylval->uval = EU; return TOK(KEYWORD);


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

{id}          yylval->sval = yytext; return TOK(ID);


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
