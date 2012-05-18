#include <fstream>
#include <map>
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
  {}

  int parse_bdd(std::string str)
  {
    bdd_init(1000000, 10000);
    bdd_setvarnum(1000);
    kripke::driver d;
    if (str == "-")
      {
        assert(!!false);
      }
    unsigned int size;
    {
      std::ifstream i;
      i.open(str);
      i >> size;
      i.close();
    }

    unsigned int nb_bits = (unsigned int) std::ceil(std::log2(size));

    std::map<int, bdd> m;
    for (unsigned i = 0; i < size; ++i)
      {
        bdd acu = bddtrue;
        unsigned decu = i;
        for (unsigned j = 32; j > 0; decu /= 2)
          {
            --j;
            if (decu & 1)
              acu &= bdd_ithvar(j);
            else
              acu = acu & !bdd_ithvar(j);
          }
        m[i] = acu;
        std::cout << i << '\t' << acu << std::endl;
      }
    return d.parse_file(str, states_, transition_);
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
