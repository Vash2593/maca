#ifndef VERIFICATION_VERIFICATION_HH_
# define VERIFICATION_VERIFICATION_HH_

# include <bdd.h>
# include <parseKripke.hh>

namespace verif
{

  typedef parseKripke::bddmap bddmap;

  template <class RecurType, class Lambda>
  bdd
  bdd_recursion(Lambda l, bdd prev, bdd support)
  {
    bdd res = bddfalse;
    while (true)
      {
        res = RecurType::op(prev, l(prev));
        if (res == prev)
          break;
        prev = res;
      }
    return bdd_exist(res, support);
  }

  template <typename RecurType, class Lambda>
  bdd
  bdd_recursion(Lambda l, bdd f, bdd g, bdd support)
  {
    bdd res = bddfalse;
    while (true)
      {
        res = RecurType::op(g, l(f, g));
        if (res == f)
          break;
        f = res;
      }
    return bdd_exist(res, support);
  }

  struct Incremental
  {
    // Incremental recursion for bdd formula. This struct must be pass
    // as template parameters to bdd_recursion.
    static bdd op(bdd l, bdd r)
    {
      return l | r;
    }
  };

  struct Decremental
  {
    // Decrmental recursion for bdd formula. This struct must be pass
    // as template parameters to bdd_recursion.
    static bdd op(bdd l, bdd r)
    {
      return l & r;
    }
  };

  class verif
  {
  public:
    verif(bdd& states, bdd& transition, bdd& succs,
          bddPair* succ_to_pred, bddPair* pred_to_succ, bddmap& map);
  public:
#define OP_BIN(name) bdd bdd_##name(bdd f, bdd g)
    OP_BIN(and);
    OP_BIN(or);
    OP_BIN(implies);
    OP_BIN(euntil);
    OP_BIN(auntil);
#undef OP_BIN
#define OP_UN(name) bdd bdd_##name(bdd f)
    OP_UN(not);
    OP_UN(ap);
    OP_UN(anext);
    OP_UN(enext);
    OP_UN(afuture);
    OP_UN(efuture);
    OP_UN(aglobally);
    OP_UN(eglobally);
#undef OP_UN
  private:
    bdd& states_;
    bdd& transitions_;
    bdd& succs_;
    bddPair* succ_to_pred_;
    bddPair* pred_to_succ_;
    bdd support_;
  };
} // End namespace verif.

#endif // !VERIFICATION_VERIFICATION_HH_
