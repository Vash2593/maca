#include <parseKripke.hh>

int main(int argc, char** argv)
{
  assert(argc == 2);
  parseKripke k;
  k.parse_bdd(std::string(argv[1]));

  return 0;
}
