#ifndef IO_CTL_PUBLIC_HH_
# define IO_CTL_PUBLIC_HH_

namespace ctl
{
  // Declare the parser to be used by over people.
  bool ctl_parse(std::string name, verif::verif& v, bdd initial);
} // End namespace ctl.

#endif // !IO_CTL_PUBLIC_HH_
