#include <cstring>
#include <string>
#include "driver.hh"
#include "kripke.hh"

namespace kripke
{
  driver::driver(bdd& states,
                 bdd& transitions,
                 const std::vector<bdd>& sources,
                 const std::vector<bdd>& destinations,
                 std::map<std::string, int>& id_map,
                 const unsigned nb_states)
    : states_(states)
    , transitions_(transitions)
    , sources_(sources)
    , destinations_(destinations)
    , id_map_(id_map)
    , nb_states_(nb_states)
  {}

  int
  driver::parse_file(const std::string& f)
  {
    FILE* yyin = f == "-" ? stdin : fopen(f.c_str(), "r");
    if (!yyin)
      {
        std::cerr << f << ": cannot open: " << strerror(errno) << std::endl;
        exit(1);
      }
    scan_open(yyin);
    int res = parse();
    if (f != "-")
      fclose(yyin);
    return res;
  }

  int
  driver::parse_string(const std::string& e, const location& l)
  {
    scan_open(e);
    return parse();
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
  driver::parse(const location& l)
  {
    parser p(*this, states_,
             transitions_,
             sources_,
             destinations_,
             id_map_,
             nb_states_);
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
