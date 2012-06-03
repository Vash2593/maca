#include <kripkeparse/driver.hh>
#include "parseKripke.hh"

int parseKripke::parse_bdd(std::string str)
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
  kripke::driver d(states_, transitions_, source,
                   destination, id_map_, bits_need);
  return d.parse_file(str);
}

