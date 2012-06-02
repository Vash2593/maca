#include <parseKripke.hh>
#include <verification/verification.hh>

int main(int argc, char** argv)
{
  using bddmap = parseKripke::bddmap;
  assert(argc == 2);
  parseKripke k;
  k.parse_bdd(std::string(argv[1]));

  verif::verif f(k.get_states(), k.get_transitions(),
                 k.get_succs(), k.get_succ_to_pred(),
                 k.get_pred_to_succ(), k.get_map());

  bddmap& map = k.get_map();
  bdd a = bdd_ithvar(map["a"]);

  std::cerr << f.bdd_eglobally(f.bdd_ap(a)) << std::endl;

  return 0;
}
