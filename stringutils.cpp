#include "stringutils.h"

std::string join(std::vector<std::string> const & list_of_strings, std::string separator) {
    std::string result;
    for (size_t i = 0; i < list_of_strings.size(); i++) {
        result += list_of_strings[i];
        if (i < list_of_strings.size() - 1) {
            result += separator;
        }
    }
    return result;
}


std::string replace(std::string const & source, std::string const & what, std::string const & with) {
    std::string result = source;

    size_t index = 0;
    index = result.find(what, index);

    while (index != std::string::npos) {
        result.replace(index, what.length(), with);
        index = result.find(what, index + with.length());
    }

    return result;
}