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
      enum keyword_kind { AND, OR, NOT, IMPLIES,
                          AX, EX, AF, EF, AG, EG, AU, EU };

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

%token <uval> KEYWORD "keyword"
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
"keyword" "(" args ")" { std::cout << "fun_call: " << $1 << std::endl; }
;

// 'exp[, exp]*'
args:
  exp
| args "," exp
;

term:
"id"            { std::cout << "term - id: " << *$1 << std::endl; }
| "true"        { std::cout << "term - true" << std::endl; }
| "false"       { std::cout << "term - false" << std::endl; }
| "!" "id"      { std::cout << "term - not id: " << *$2 << std::endl; }
| "!" "true"    { std::cout << "term - not true" << std::endl; }
| "!" "false"   { std::cout << "term - not false" << std::endl; }
;


%%

namespace ctl
{
  void
  parser::error (const location_type& l, const std::string& m)
  {
    std::cerr << l << ": " << m << std::endl;
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
