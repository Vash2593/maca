#include <iostream>
#include <cassert>
#include <kripkeparse/driver.hh>

int main(int argc, char** argv)
{
  assert(argc == 2);

  kripke::driver d;
  d.parse_file(argv[1]);
}
