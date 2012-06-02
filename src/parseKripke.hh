#ifndef SRC_PARSEKRIPKE_HH
# define SRC_PARSEKRIPKE_HH
#include <fstream>
#include <vector>
#include <cmath>
#include <cassert>
#include <bdd.h>

#include <kripkeparse/driver.hh>

class parseKripke
{
public:
  typedef std::vector<bdd> vbdd;
  typedef std::map<std::string, int> bddmap;

public:
  parseKripke()
    : states_(bddfalse)
    , transitions_(bddfalse)
    , pred_to_succ_(0)
    , succ_to_pred_(0)
    , succs_(bddtrue)
  {
    bdd_init(1000000, 10000);
    bdd_setvarnum(10000);
  }

  int parse_bdd(std::string str)
  {
    const unsigned size = get_size(str);
    const unsigned bits_need = get_bits_need(size);

    create_pairs(bits_need);

    vbdd source;
    vbdd destination;
    for (unsigned i = 0; i < size; ++i)
      {
        bdd new_source = bddtrue;
        unsigned decu = i;
        for (unsigned j = bits_need; j > 0; decu /= 2)
          {
            --j;
            if (decu & 1)
              new_source &= bdd_ithvar(j);
            else
              new_source &= !bdd_ithvar(j);
          }
        source.push_back(new_source);
        destination.push_back(bdd_replace(new_source, pred_to_succ_));
      }
    kripke::driver d(states_, transitions_, source, destination, id_map_, bits_need);
    return d.parse_file(str);
  }
public:
  // Get
  bdd& get_states()
  {
    return states_;
  }

  bdd& get_transitions()
  {
    return transitions_;
  }

  bddPair* get_pred_to_succ()
  {
    return pred_to_succ_;
  }

  bddPair* get_succ_to_pred()
  {
    return succ_to_pred_;
  }

  bdd get_succs()
  {
    return succs_;
  }

  bddmap& get_map()
  {
    return id_map_;
  }

private:
  void create_pairs(unsigned bits_need)
  {
    pred_to_succ_ = bdd_newpair();
    succ_to_pred_ = bdd_newpair();

    for (unsigned j = 0; j < bits_need; ++j)
      {
        if (bdd_setpair(pred_to_succ_, j, j + bits_need)
            || bdd_setpair(pred_to_succ_, j + bits_need, j))
          assert(false);
        succs_ &= bdd_ithvar(j + bits_need);
      }
  }

  unsigned get_size(std::string& str)
  {
    if (str == "-")
      assert(!"Can not read input stream");
    unsigned int size;

    std::ifstream i;
    i.open(str);
    i >> size;
    i.close();

    return size;
  }

  unsigned get_bits_need(unsigned size)
  {
    return (unsigned int) std::ceil(std::log2(size));
  }

private:
  bddmap id_map_;
  bdd states_;
  bdd transitions_;
  bddPair* pred_to_succ_;
  bddPair* succ_to_pred_;
  bdd succs_;
};

#endif // !SRC_PARSEKRIPKE_HH
