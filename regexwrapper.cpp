#include "regexwrapper.h"

#include "stringutils.h"

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <cassert>

Match::Match(int from, int to, std::string match)
    : from(from), to(to), length(to-from), match(match) {
}

bool Match::compare(Match const & other) const {
    // try to compare by starting position
    if (from != other.from)
        return from < other.from;

    // same starting position, compare by length
    else
        return length > other.length;
}

std::string regex_repair(std::string regex) {
    const std::string NEWLINE_CHARS = "\n|\r\n";

    // make . (dot) match newline characters
    const std::string DOT_NEWLINE = "(?:.|" + NEWLINE_CHARS + ")";
    regex = replace(regex, ".", DOT_NEWLINE);
    // but not for escaped dots
    regex = replace(regex, "\\"+DOT_NEWLINE, "\\.");

    // by default ^ only matches the start of the string, not each line start
    // and it should match new lines as well
    if (regex[0] == '^')
        regex = replace(regex, "^", "(?:^|" + NEWLINE_CHARS + ")");

    // same as ^, $ should match line endings as well
    if (regex[regex.length() - 1] == '$')
        regex = replace(regex, "$", "(?:$|" + NEWLINE_CHARS + ")");

    return regex;
}

RegexWrapper::RegexWrapper(std::string exp) {
    regex = std::regex{regex_repair(exp)};
}

std::vector<Match> RegexWrapper::execute_on(std::string input) {
    std::vector<Match> result;

    // this is the current starting position in the original string
    int at = 0;

    std::smatch match;
    while (std::regex_search(input, match, regex)) {

        // try to get the first group, otherwise save the match itself
        int saved_match_group_index = (match.size() == 2) ? 1 : 0;
        int match_pos = match.position(saved_match_group_index);
        std::string matched_string = match[saved_match_group_index];

        // add match to results
        int from = at + match_pos;
        int to = from + matched_string.size() - 1;
        result.emplace_back(Match{from, to, matched_string});

        // get the whole match
        int full_match_pos = match.position(0);
        std::string full_match = match[0];

        // move the string forward to the end of this match
        at += full_match_pos + full_match.size();
        input = match.suffix();
    }

    return result;
}

