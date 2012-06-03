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
  #include <bdd.h>
  #include <verification/verification.hh>

  typedef std::vector<bdd> bdd_vect;

  namespace ctl
  {
    enum keyword_kind { AND, OR, NOT, IMPLIES,
                        AX, EX, AF, EF, AG, EG, AU, EU };


    struct sem_type
    {
        unsigned uval;
        std::string sval;
        keyword_kind kval;
        bdd_vect* array;
        bdd elt;
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

%parse-param{ verif::verif& v }

%token EOL      "eol"
       NEG      "!"
       LPAREN   "("
       RPAREN   ")"
       COMMA    ","
       TRUE     "true"
       FALSE    "false"
%token <uval> DIGIT "digit"
;

%token <kval> KEYWORD "keyword";

%token <sval> ID "id";

%type <array> args;

%type <elt> exp term fun_call;

%printer { debug_stream() << $$;  } <sval> <kval>;

%start file

%%

file:
  exp
;

exp:
term { $$ = $1; }
| fun_call { $$ = $1; }
;

fun_call:
"keyword" "(" args ")" { std::cout << "fun_call: " << $1 << std::endl; }
;

// 'exp[, exp]*'
args:
exp             { $$ = new bdd_vect; $$->push_back($1); }
| args "," exp { $$->push_back($3); }
;

term:
"id" { $$ = bddtrue; }
| "true" { $$ = bddtrue; }
| "false" { $$ = bddfalse; }
;


%%

namespace ctl
{
  void
  parser::error (const location_type& l, const std::string& m)
  {
    std::cerr << l << ": " << m << std::endl;
  }



  void* ctl_parse(std::string name, verif::verif& v)
  {
    if (ctlyyopen(name))
    {
      std::cout << ctl::location() << ": Cannot open file " + name
                << std::endl;
      return 0;
    }

    parser p(v);
    p.set_debug_level(!!getenv("YYDEBUG"));
    p.parse();
    ctlyyclose();

    return 0;
  }

} // End namespace ctl.
