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
                kripke::parser::location_type* yylloc)
  namespace kripke
  {
    int lex(parser::semantic_type* yylval,
            parser::location_type* yylloc);
  } // namespace kripke
}

%token EOL "eol"
       NEG "!"
%token <uval> DIGIT "digit"
;

%token <sval> ID "id"
;

%start file

%%

file:
  DIGIT EOL states
;

states:
  state
| states state EOL
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
| ID next
;
