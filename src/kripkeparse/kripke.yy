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
  #include <map>

  #include <bdd.h>

  #include "location.hh"
  #include "driver.hh"

  typedef std::vector<unsigned> node_list;
  typedef std::vector<std::pair<bool, unsigned> > rules_list;

  namespace kripke
  {
    struct sem_type
    {
      unsigned uval;
      std::string* sval;
      node_list* unext;
      rules_list* urules;
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
%parse-param { std::map<std::string, int> id_map_ }
%parse-param { unsigned int nb_bits_ }
%lex-param   { driver& driver_ }

%token EOL "eol"
       NEG "!"
%token <uval> DIGIT "digit";

%token <sval> ID "id";

%type <unext> next;

%type <urules> rules;

%start file

%%

file:
DIGIT EOL states eolf   {}


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
  bdd new_state = sources_[$1];
  for (auto cond : *$2)
      new_state &= cond.first ?
        bdd_ithvar(cond.second) :
        !bdd_ithvar(cond.second);
  states_ |= new_state;
  delete $2;

  bdd& source = sources_[$1];
  for(auto n : *$4)
    transitions_ |= (source & destinations_[n]);
  delete $4;
}
;

rules:
/*  empty */            { $$ = new rules_list; }
| ID rules              {
  $$ = $2;
  if (id_map_.find(*$1) == id_map_.end())
    {
      unsigned size = id_map_.size() + nb_bits_ * 2;
      id_map_[*$1] = size;
    }
  $$->push_back(std::make_pair(true, id_map_[*$1]));
}
| "!" ID rules          {
  $$ = $3;
  if (id_map_.find(*$2) == id_map_.end())
    {
      unsigned size = id_map_.size() + nb_bits_ * 2;
      id_map_[*$2] = size;
    }
  $$->push_back(std::make_pair(false, id_map_[*$2]));
}
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
