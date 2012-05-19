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
  #include <list>

  #include <bdd.h>
  #include "location.hh"
  #include "driver.hh"

  typedef std::list<unsigned> node_list;

  namespace kripke
  {
    struct sem_type
    {
      unsigned uval;
      std::string* sval;
      node_list* unext;
    };
  } // namespace kripke
#define YYSTYPE kripke::sem_type
}

%code provides
{
#define YY_DECL                                             \
  int kripke::lex(kripke::parser::semantic_type* yylval,    \
                  kripke::parser::location_type* yylloc,    \
                  kripke::driver& driver_)
  namespace kripke
  {
    int lex(parser::semantic_type* yylval,
            parser::location_type* yylloc,
            kripke::driver& driver_);
  } // namespace kripke
}

%parse-param { driver& driver_ }
%parse-param { bdd& states_ }
%parse-param { bdd& transitions_ }
%parse-param { std::vector<bdd> sources_ }
%parse-param { std::vector<bdd> destinations_ }
%lex-param   { driver& driver_ }

%token EOL "eol"
       NEG "!"
%token <uval> DIGIT "digit"
;

%token <sval> ID "id"
;

%type <unext> next;

%start file

%%

file:
DIGIT EOL states eolf


eolf:
/* empty */
| EOL
;

states:
  state
| states EOL state
;

state:
DIGIT rules EOL next    {
  bdd& source = sources_[$1];
  for(auto n : $4)
    states_ |= source & destinations_[n];
  delete $4
}
;

rules:
/*  empty */
| ID rules
| "!" ID rules
;

next:
/* empty */             { $$ = new node_list(); }
| next DIGIT            { $$ = $1; $$->push_back($2); }
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
