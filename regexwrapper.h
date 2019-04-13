#ifndef REGEXWRAPPER_H_
#define REGEXWRAPPER_H_

#include "brush.h"

#include <string>
#include <vector>
#include <regex>

struct Match {
    int from;
    int to;
    int length;
    std::string match;
    ColoringMethods methods;

    Match(int from, int to, std::string match);
    bool compare(Match const & other) const;
};

class RegexWrapper {
    std::regex regex;

public:
    RegexWrapper(std::string expression);
    std::vector<Match> execute_on(std::string input);
};

#endif