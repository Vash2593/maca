#include <bdd.h>

#include <verification/verification.hh>

namespace verif
{
  verif::verif(bdd& states, bdd& transitions, bdd& succs, bddPair* succ_to_pred,
               bddPair* pred_to_succ, bddmap& map)
    : states_(states)
    , transitions_(transitions)
    , succs_(succs)
    , succ_to_pred_(succ_to_pred)
    , pred_to_succ_(pred_to_succ)
    , support_(bddtrue)
  {
    for (auto v : map)
      support_ &= bdd_ithvar(v.second);
    support_ &= bdd_support(succs_);
  }

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
    return bdd_exist(states_ - f, support_);
  }

  bdd
  verif::bdd_implies(bdd f, bdd g)
  {
    // FIXME: Ask Pollux
    return bdd_or(bdd_not(f), g);
  }

  bdd
  verif::bdd_ap(bdd f)
  {
    // GOOD
    return bdd_exist(states_ & f, support_);
  }

  bdd
  verif::bdd_enext(bdd f)
  {
    return transitions_ & bdd_replace(f, pred_to_succ_);
  }

  bdd
  verif::bdd_anext(bdd f)
  {
    return bdd_not(bdd_enext(bdd_not(f)));
  }

  bdd
  verif::bdd_efuture(bdd f)
  {
    auto lambda = [&] (bdd succ) {
      return bdd_enext(succ);
    };
    return bdd_recursion<Incremental>(lambda, f, support_);
  }

  bdd
  verif::bdd_afuture(bdd f)
  {
    return bdd_not(bdd_eglobally(bdd_not(f)));
  }

  bdd
  verif::bdd_eglobally(bdd f)
  {
    auto lambda = [&] (bdd succ) {
      return bdd_enext(succ);
    };
    return bdd_recursion<Decremental>(lambda, f, support_);
  }

  bdd
  verif::bdd_aglobally(bdd f)
  {
    return bdd_not(bdd_efuture(bdd_not(f)));
  }

  bdd
  verif::bdd_auntil(bdd f, bdd g)
  {
    auto lambda = [&] (bdd f, bdd g) {
      return bdd_and(f, bdd_anext(g));
    };
    return bdd_recursion<Incremental>(lambda, f, g, support_);
  }

  bdd
  verif::bdd_euntil(bdd f, bdd g)
  {
    auto lambda = [&] (bdd f, bdd g) {
      return bdd_and(f, bdd_enext(g));
    };
    return bdd_recursion<Incremental>(lambda, f, g, support_);
  }

} // End namespace verif.
