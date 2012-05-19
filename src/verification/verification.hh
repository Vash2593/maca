#ifndef VERIFICATION_VERIFICATION_HH_
# define VERIFICATION_VERIFICATION_HH_

namespace verif
{
  bdd bdd_and(bdd states, bdd transitions, bdd f, bdd g);

  bdd bdd_or(bdd states, bdd transitions, bdd f, bdd g);

  bdd bdd_not(bdd states, bdd transitions, bdd f);

  bdd bdd_implies(bdd states, bdd transitions, bdd f, bdd g);

  bdd bdd_ap(bdd states, bdd transitions, bdd f);

  bdd bdd_anext(bdd states, bdd transitions, bdd f);

  bdd bdd_enext(bdd states, bdd transitions, bdd f);

  bdd bdd_afuture(bdd states, bdd transitions, bdd f);

  bdd bdd_efuture(bdd states, bdd transitions, bdd f);

  bdd bdd_aglobally(bdd states, bdd transitions, bdd f);

  bdd bdd_eglobally(bdd states, bdd transitions, bdd f);

  bdd bdd_auntil(bdd states, bdd transitions, bdd f, bdd g);

  bdd bdd_euntil(bdd states, bdd transitions, bdd f, bdd g);

} // End namespace verification.


#endif // !VERIFICATION_VERIFICATION_HH_
