%option noyywrap nounput debug

%{
#include <string>
#include <cassert>
#include <iostream>
#include <kripkeparse/kripke.hh>
#include <boost/lexical_cast.hpp>
#include <kripkeparse/driver.hh>

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

namespace kripke
{
    void
    driver::scan_open(FILE *f)
    {
      yy_flex_debug = !!getenv("YYSCAN");
      yypush_buffer_state(YY_CURRENT_BUFFER);
      yy_switch_to_buffer(yy_create_buffer(f, YY_BUF_SIZE));
    }

    void
    driver::scan_open(const std::string& e)
    {
      yy_flex_debug = !!getenv("YYSCAN");
      yyin = 0;
      yypush_buffer_state(YY_CURRENT_BUFFER);
      yy_scan_bytes(e.c_str(), e.size());
    }

    void
    driver::scan_close()
    {
      yypop_buffer_state();
    }
} // namespace kripke


// Local Variables:
// mode: C++
// End:
