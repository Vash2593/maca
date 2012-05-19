#include <fstream>
#include <vector>
#include <cmath>
#include <cassert>
#include <bdd.h>

#include <kripkeparse/driver.hh>

class parse
{
  typedef std::vector<bdd> vbdd;

public:
  parse(bdd& states, bdd& transitions)
    : states_(states)
    , transitions_(transitions)
  {
    bdd_init(1000000, 10000);
    bdd_setvarnum(1000);
  }

  int parse_bdd(std::string str)
  {
    const unsigned size = get_size(str);
    const unsigned bits_need = get_bits_need(size);

    bddPair* pair = get_pair(bits_need);

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
        source[i] = new_source;
        destination[i] = bdd_replace(new_source, pair);
      }
    kripke::driver d(states_, transitions_, source, destination);
    return d.parse_file(str);
  }

private:
  bddPair* get_pair(unsigned bits_need)
  {
    bddPair* pair = bdd_newpair();
    for (unsigned j = 0; j < bits_need; ++j)
      if (!bdd_setpair(pair, j, j + bits_need))
        assert(false);
    return pair;
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
  bdd states_;
  bdd transitions_;
};

int main(int argc, char** argv)
{
  assert(argc == 2);
  bdd states;
  bdd transitions;
  parse k(states, transitions);
  k.parse_bdd(std::string(argv[1]));
}
