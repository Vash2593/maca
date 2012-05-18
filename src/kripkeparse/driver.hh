#ifndef MACA_KRIPKEPARSE_DRIVER_HH
# define MACA_KRIPKEPARSE_DRIVER_HH

# include <sstream>
# include <string>
# include <istream>
# include <bdd.h>
# include "location.hh"

namespace kripke
{
  class driver
  {
  public:
    driver();
    int parse_file(const std::string& f, bdd states, bdd transitions);
    int parse_string(const std::string& e,
                     bdd states,
                     bdd transitions,
                     const location& l = location());
    int parse_stream(FILE* s, bool stdin, bdd states, bdd transitions);

    void error(const location& l, const std::string& m);
    void invalid(const location& l, const std::string& s);
    int parse(bdd states, bdd transition, const location& l = location());

    int result_;
  private:
    location location_;
  private:
    void scan_open(FILE* f);
    void scan_open(const std::string& e);
    void scan_close();
  };
} // namespace kripke

#endif // !MACA_KRIPKEPARSE_DRIVER_HH
