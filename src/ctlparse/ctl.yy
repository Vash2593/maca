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
  #include <sstream>
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

#define CHECK_ARITY(loc, iexp, name, size)      \
    if (size != iexp)                           \
    {                                           \
      std::string s = "Operator ";              \
      s += name;                                \
      s += " expects ";                         \
      s += #iexp;                               \
      s += " arguments, ";                      \
      s += #size;                               \
      s += " given.";                           \
      ctl::parser::error(loc, s);               \
    }

#define N_AND bdd_and
#define N_OR bdd_or
#define N_NOT bdd_not
#define N_IMPLIES bdd_implies
#define N_AX bdd_anext
#define N_EX bdd_enext
#define N_AF bdd_afuture
#define N_EF bdd_efuture
#define N_AG bdd_aglobally
#define N_EG bdd_eglobally
#define N_AU bdd_auntil
#define N_EU bdd_euntil

#define CALL_BINARY(loc, type, args, res)       \
    CHECK_ARITY(loc, 2, #type, args->size());   \
    res = v.N_##type((*args)[0], (*args)[1])

#define CALL_UNARY(loc, type, args, res)        \
    CHECK_ARITY(loc, 1, #type, args->size());   \
    res = v.N_##type((*args)[0])

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
%parse-param{ bool& res }
%parse-param{ bdd initial }

%token EOL      "eol"
       NEG      "!"
       LPAREN   "("
       RPAREN   ")"
       COMMA    ","
       TRUE     "true"
       FALSE    "false"
%token <uval> DIGIT "digit"
;

%token <uval> KEYWORD "keyword";

%token <sval> ID "id";

%type <array> args;

%type <elt> exp term fun_call;

%printer { debug_stream() << $$;  } <sval> <kval>;

%start file

%%

file:
exp {
  res = (initial & $1) != bddfalse ? true : false;
}
;

exp:
term { $$ = $1; }
| fun_call { $$ = $1; }
;

fun_call:
"keyword" "(" args ")" {
  switch ($1)
  {
    case AND: {
                CALL_BINARY(@$, AND, $3, $$);
                break;
              }

    case OR:  {
                CALL_BINARY(@$, OR, $3, $$);
                break;
              }
    case NOT: {
                CALL_UNARY(@$, NOT, $3, $$);
                break;
              }
    case IMPLIES: {
                CALL_BINARY(@$, IMPLIES, $3, $$);
                     break;
                  }
    case AX: {
                CALL_UNARY(@$, AX, $3, $$);
               break;
             }
    case EX: {
                CALL_UNARY(@$, EX, $3, $$);
               break;
             }
    case AF: {
                CALL_UNARY(@$, AF, $3, $$);
               break;
             }
    case EF: {
                CALL_UNARY(@$, EF, $3, $$);
               break;
             }
    case AG: {
                CALL_UNARY(@$, AG, $3, $$);
               break;
             }
    case EG: {
                CALL_UNARY(@$, EG, $3, $$);
               break;
             }
    case EU: {
                CALL_BINARY(@$, EU, $3, $$);
               break;
             }
    case AU: {
                CALL_BINARY(@$, AU, $3, $$);
               break;
             }
    default: assert(0);
  }; }
;

// 'exp[, exp]*'
args:
exp             { $$ = new bdd_vect; $$->push_back($1); }
| args "," exp { $$->push_back($3); }
;

term:
"id" { auto it = v.get_map().find($1);
  if (it == v.get_map().end())
    ctl::parser::error(@$, "Unknown identifier.");
  $$ = bdd_ithvar(it->second);
 }
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



  bool ctl_parse(std::string name, verif::verif& v, bdd initial)
  {
    if (ctlyyopen(name))
    {
      std::cout << ctl::location() << ": Cannot open file " + name
                << std::endl;
      return 0;
    }

    bool res = false;

    parser p(v, res, initial);
    p.set_debug_level(!!getenv("YYDEBUG"));
    p.parse();
    ctlyyclose();



    return res;
  }

} // End namespace ctl.
