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
  } // namespace ctl
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

    int ctlyyopen(const std::string &name);
    void ctlyyclose();


  } // namespace ctl


}

%token EOL      "eol"
       NEG      "!"
       LPAREN   "("
       RPAREN   ")"
       COMMA    ","
       TRUE     "true"
       FALSE    "false"
%token <uval> DIGIT "digit"
;

%token <sval> ID "id"
;

%start file

%%

file:
  exp
;

exp:
  term
| fun_call
;

fun_call:
"id" "(" args ")" { std::cout << "fun_call: " << *$1 << std::endl; }
;

// One or more 'exp, ...'
args:
  exp
| args "," exp
;

term:
"id"            { std::cout << "term - id: " << *$1 << std::endl; }
| "true"        { std::cout << "term - true" << std::endl; }
| "false"       { std::cout << "term - false" << std::endl; }
;


%%

namespace ctl
{
  void
  parser::error (const location_type& l, const std::string& m)
  {
  }



  void* ctl_parse(std::string name)
  {
    if (ctlyyopen(name))
    {
      std::cout << ctl::location() << ": Cannot open file " + name
                << std::endl;
      return 0;
    }

    parser p;
    p.set_debug_level(false);
    p.parse();
    ctlyyclose();

    return 0;
  }

} // End namespace ctl.
