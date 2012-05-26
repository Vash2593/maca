#include <bdd.h>

#include <verification/verification.hh>

namespace verif
{

  verif::verif(bdd states, bdd transitions, bdd succs, bddPair* succ_to_pred)
    : states_(states)
    , transitions_(transitions)
    , succs_(succs)
    , succ_to_pred_(succ_to_pred)
  {}

  bdd
  verif::bdd_and(bdd f, bdd g)
  {
    return Decremental::op(f, g);
  }

  bdd
  verif::bdd_or(bdd f, bdd g)
  {
    return Incremental::op(f, g);
  }

  bdd
  verif::bdd_not(bdd f)
  {
    return states_ - f;
  }

  // bdd
  // verif::bdd_implies(bdd f, bdd g)
  // {}

  bdd
  verif::bdd_ap(bdd f)
  {
    return states_ & f;
  }

  // bdd
  // verif::bdd_anext(bdd f)
  // {
  //   // return bdd_not(bdd_enext(bdd_not(f)));
  // }

  // bdd
  // verif::bdd_enext(bdd f)
  // {}

  bdd
  verif::bdd_afuture(bdd f)
  {
    auto lambda = [&] (bdd succ) {
      return bdd_exist(states_ & bdd_replace(succ, succ_to_pred_), succs_);
    };
    return bdd_recursion<Incremental>(lambda, f);
  }

  // bdd
  // verif::bdd_efuture(bdd f)
  // {
  //   //return bdd_or(f, bdd_enext(bdd_efuture(f)));
  // }

  // bdd
  // verif::bdd_aglobally(bdd f)
  // {}

  // bdd
  // verif::bdd_eglobally(bdd f)
  // {
  //   //return bdd_and(f, bdd_enext(bdd_eglobally(f)));
  // }

  // bdd
  // verif::bdd_auntil(bdd f, bdd g)
  // {}

  // bdd
  // verif::bdd_euntil(bdd f, bdd g)
  // {}

} // End namespace verif.
