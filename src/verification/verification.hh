#ifndef VERIFICATION_VERIFICATION_HH_
# define VERIFICATION_VERIFICATION_HH_

# include <bdd.h>

namespace verif
{

  template <class RecurType, class Lambda>
  bdd
  bdd_recursion(Lambda l, bdd prev)
  {
    bdd res;
    while (true)
      {
        res = RecurType::op(prev, l(prev));
        if (res != prev)
          break;
        prev = res;
      }
    return res;
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
    verif(bdd states, bdd transition, bdd succs, bddPair* succ_to_pred);
  public:
    bdd bdd_and(bdd f, bdd g);
    bdd bdd_or(bdd f, bdd g);
    bdd bdd_not(bdd f);
    bdd bdd_implies(bdd f, bdd g);
    bdd bdd_ap(bdd f);
    bdd bdd_anext(bdd f);
    bdd bdd_enext(bdd f);
    bdd bdd_afuture(bdd f);
    bdd bdd_efuture(bdd f);
    bdd bdd_aglobally(bdd f);
    bdd bdd_eglobally(bdd f);
    bdd bdd_auntil(bdd f, bdd g);
    bdd bdd_euntil(bdd f, bdd g);
  private:
    bdd& states_;
    bdd& transitions_;
    bdd& succs_;
    bddPair* succ_to_pred_;
  };
} // End namespace verif.

#endif // !VERIFICATION_VERIFICATION_HH_
