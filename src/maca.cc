#include <fstream>
#include <vector>
#include <cmath>
#include <cassert>
#include <bdd.h>

#include <kripkeparse/driver.hh>

class parse
{
public:
  parse()
    : states_(bddfalse)
    , transition_(bddfalse)
  {
    bdd_init(1000000, 10000);
    bdd_setvarnum(1000);
  }

  int parse_bdd(std::string str)
  {
    kripke::driver d;

    const unsigned size = get_size(str);
    const unsigned bits_need = get_bits_need(size);

    bddPair* pair = get_pair(bits_need);

    std::vector<bdd> source;
    std::vector<bdd> destination;
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
    return d.parse_file(str, states_, transition_);
  }
private:
  bddPair* get_pair(unsigned bits_need)
  {
    // Create the pair
    bddPair* pair = bdd_newpair();
    for (unsigned j = 0; j < bits_need; ++j)
      if (!bdd_setpair(pair, j, j + bits_need))
        assert(false);
    return pair;
  }
  unsigned get_size(std::string& str)
  {
    if (str == "-")
      assert(!!false);
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
  bdd transition_;
};

int main(int argc, char** argv)
{
  assert(argc == 2);
  parse k;
  k.parse_bdd(std::string(argv[1]));
}
