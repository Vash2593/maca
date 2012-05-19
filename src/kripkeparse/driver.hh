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
    driver(bdd states,
           bdd transitions,
           const std::vector<bdd>& sources,
           const std::vector<bdd>& destinations);
    int parse_file(const std::string& f);
    int parse_string(const std::string& e, const location& l = location());
    int parse_stream(FILE* s, bool stdin);

    void error(const location& l, const std::string& m);
    void invalid(const location& l, const std::string& s);
    int parse(const location& l = location());

    int result_;
  private:
    location location_;
    bdd states_;
    bdd transitions_;
    const std::vector<bdd>& sources_;
    const std::vector<bdd>& destinations_;
      private:
    void scan_open(FILE* f);
    void scan_open(const std::string& e);
    void scan_close();
  };
} // namespace kripke

#endif // !MACA_KRIPKEPARSE_DRIVER_HH
