#ifndef STRNGUTILS_H_
#define STRNGUTILS_H_

#include <string>
#include <vector>

std::string join(std::vector<std::string> const & list_of_strings, std::string separator);
std::string replace(std::string const & source, std::string const & what, std::string const & with);

#endif