#ifndef MACA_IO_DRIVER_HH
# define MACA_IO_DRIVER_HH

# include <sstream>
# include <string>
# include "location.hh"

namespace kripke
{
  class driver
  {
  public:
    driver();
    int parse_file(const std::string& f);
    int parse_string(const std::string& e, const location& l = location());

    void error(const location& l, const std::string& m);
    void invalid(const location& l, const std::string& s);
    int parse(const location& l = location());

    int result_;
  private:
    location location_;
  private:
    void scan_open(FILE* f);
    void scan_open(const std::string& e);
    void scan_close();
  };
} // namespace kripke

#endif // !MACA_IO_DRIVER_HH
