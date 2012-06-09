#ifndef SRC_PARSEKRIPKE_HH
# define SRC_PARSEKRIPKE_HH

# include <fstream>
# include <vector>
# include <cmath>
# include <cassert>
# include <bdd.h>
# include <map>

// We pass this function the buddy Garbage Collector
static void nullfct(int, bddGbcStat*)
{}

// Read the structure in a file with the `parse_bdd' function.
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
    , initial_state_(bddfalse)
  {
    bdd_init(1000000, 10000);
    bdd_setvarnum(10000);
    bdd_gbc_hook(nullfct);
  }

  int parse_bdd(std::string str);

public:
  // Getters
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

  bdd& get_succs()
  {
    return succs_;
  }

  bddmap& get_map()
  {
    return id_map_;
  }


  bdd& get_initial_state()
  {
    return initial_state_;
  }
private:
  // Create pairs with the needed bits
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

  // Get the size of the automaton
  /// We need to undo the read of an integer in the stream
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

  // Get the number of bits needed
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
  bdd initial_state_;
};

#endif // !SRC_PARSEKRIPKE_HH
