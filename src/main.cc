#include <parseKripke.hh>
#include <verification/verification.hh>
#include <ctlparse/ctl-public.hh>

int main(int argc, char** argv)
{
  typedef parseKripke::bddmap bddmap;
  assert(argc == 3);
  parseKripke k;
  k.parse_bdd(std::string(argv[1]));

  verif::verif f(k.get_states(), k.get_transitions(),
                 k.get_succs(), k.get_succ_to_pred(),
                 k.get_pred_to_succ(), k.get_map());

  bool res = ctl::ctl_parse(argv[2], f, k.get_initial_state());

  std::cout << "res: " << std::boolalpha << res << std::endl;

  return !res;
}
