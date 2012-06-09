#ifndef VERIFICATION_VERIFICATION_HH_
# define VERIFICATION_VERIFICATION_HH_

# include <bdd.h>
# include <parseKripke.hh>

namespace verif
{

  typedef parseKripke::bddmap bddmap;


  // Generic and efficient. Use To avoid duplication of code in the
  // fix point algorithm.  To use in pass as template parameters the
  // type of recursion (Incremental or Decremental structure) and a
  // lambda function. The lambda function must get one parameters of
  // type `bdd' and return a `bdd' type.
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

  // Sorry for the copy-paste
  template <typename RecurTypeL, typename RecurTypeR, class Lambda>
  bdd
  bdd_recursion(Lambda l, bdd f, bdd g, bdd support)
  {

    bdd res = bddfalse;
    while (true)
      {
        res = RecurTypeL::op(g, RecurTypeR::op(f, l(g)));
        if (res == g)
          break;
        g = res;
      }
    return bdd_exist(res, support);
  }

  // Incremental recursion for bdd formula. This struct must be pass
  // as template parameters to bdd_recursion.
  struct Incremental
  {
    static bdd op(bdd l, bdd r)
    {
      return l | r;
    }
  };

  // Decrmental recursion for bdd formula. This struct must be pass as
  // template parameters to bdd_recursion.
  struct Decremental
  {
    static bdd op(bdd l, bdd r)
    {
      return l & r;
    }
  };

  // Define the Ctl operators.
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

      const bddmap& get_map() const;
  private:
    bdd& states_;
    bdd& transitions_;
    bdd& succs_;
    bddPair* succ_to_pred_;
    bddPair* pred_to_succ_;
    bdd support_;
    bddmap& map_;
  };

} // End namespace verif.

#endif // !VERIFICATION_VERIFICATION_HH_
