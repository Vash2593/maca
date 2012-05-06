// -*- mode: c++ -*-
%require "2.5"
%language "C++"

%debug
%defines
%error-verbose
%expect 0
%locations
%define namespace "ctl"
%name-prefix "ctl::"

%code requires
{
  #include <iostream>
  #include <string>
  #include "location.hh"

  namespace ctl
  {
    struct sem_type
    {
      unsigned uval;
      std::string* sval;
    };
  } // namespace kripke
#define YYSTYPE ctl::sem_type
}

%code provides
{
#define YY_DECL                                         \
  int                                                   \
    ctl::lex(ctl::parser::semantic_type* yylval,        \
             ctl::parser::location_type* yylloc)

  namespace ctl
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
