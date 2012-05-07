// -*- mode: c++ -*-
%require "2.5"
%language "C++"

%debug
%defines
%error-verbose
%expect 0
%locations
%define namespace "kripke"
%name-prefix "kripke::"

%code requires
{
  #include <iostream>
  #include <string>
  #include "location.hh"
  #include "driver.hh"

  namespace kripke
  {
    struct sem_type
    {
      unsigned uval;
      std::string* sval;
    };
  } // namespace kripke
#define YYSTYPE kripke::sem_type
}

%code provides
{
  #define YY_DECL                                       \
    int                                                 \
    kripke::lex(kripke::parser::semantic_type* yylval,  \
                kripke::parser::location_type* yylloc,  \
                kripke::driver& driver_)
  namespace kripke
  {
    int lex(parser::semantic_type* yylval,
            parser::location_type* yylloc,
            kripke::driver& driver_);
  } // namespace kripke
}

%parse-param { driver& driver_ }
%lex-param   { driver& driver_ }

%token EOL "eol"
       NEG "!"
%token <uval> DIGIT "digit"
;

%token <sval> ID "id"
;

%start file

%%

file:
DIGIT EOL states EOL // FIXME: EOL?
;

states:
  state
| states EOL state
;

state:
DIGIT rules EOL next
;

rules:
/*  empty */
| ID rules
| "!" ID rules
;

next:
/* empty */
| next DIGIT
;

%%
namespace kripke
{
  void
  parser::error (const location_type& l, const std::string& m)
  {
    std::cerr << l << ": " << m << std::endl;
  }

} // namespace kripke
