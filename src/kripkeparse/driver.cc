#include <cstring>
#include <string>
#include "driver.hh"
#include "kripke.hh"

namespace kripke
{
  driver::driver()
  {}

  int
  driver::parse_file(const std::string& f, bdd states, bdd transitions)
  {
    FILE* yyin = f == "-" ? stdin : fopen(f.c_str(), "r");
    if (!yyin)
      {
        std::cerr << f << ": cannot open: " << strerror(errno) << std::endl;
        exit(1);
      }
    scan_open(yyin);
    int res = parse(states, transitions);
    if (f != "-")
      fclose(yyin);
    return res;
  }

  int
  driver::parse_string(const std::string& e, bdd states, bdd transitions, const location& l)
  {
    scan_open(e);
    return parse(states, transitions);
  }

  void
  driver::error(const location& l, const std::string& m)
  {
    std::cerr << l << ": " << m << std::endl;
  }

  void
  driver::invalid(const location& l, const std::string& s)
  {
    error(l, "invalid character: " + s);
  }

  int
  driver::parse(bdd states, bdd transitions, const location& l)
  {
    parser p(*this, states, transitions);
    p.set_debug_level(!!getenv("YYDEBUG"));
    location_ = l;
    if (p.parse())
      result_ = 0;
    scan_close();
    int res = 0;
    std::swap(result_, res);
    return res;
  }

} // namespace kripke
