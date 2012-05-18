#include <iostream>
#include <cassert>

#include <bdd.h>

#include <kripkeparse/driver.hh>

int main(int argc, char** argv)
{
  bdd states, transitions;
  assert(argc == 2);

  kripke::driver d;
  d.parse_file(argv[1], states, transitions);
}
