#include "highlighter.h"

#include "regexwrapper.h"
#include "stringutils.h"

#include <vector>
#include <algorithm>

template <typename CONTAINER, typename VALUE>
bool contains(CONTAINER const & c, VALUE const & v) {
    return std::find(std::begin(c), std::end(c), v) != std::end(c);
}

void sort_by_position_and_length(std::vector<Match> & matches) {
    std::sort(std::begin(matches), std::end(matches),
        [] (Match const & a, Match const & b) {
            return a.compare(b);
        }
    );
}

void remove_nested(std::vector<Match> & matches) {
    sort_by_position_and_length(matches);

    // collect matches that will be removed here
    std::vector<Match const *> to_remove;

    // for each match, check if the consecutive matches are intersecting
    for (size_t i = 0; i < matches.size(); i++) {
        // skip if the match has already been removed
        bool already_removed = contains(to_remove, &matches[i]);
        if (already_removed) {
            continue;
        }

        // check until the next match starts later than this one ends
        for (size_t j = i + 1; j < matches.size(); j++) {
            bool not_intersecting = matches[i].to < matches[j].from;
            if (not_intersecting) {
                break;
            }

            // this is not after the matches[i], this must be a nested match
            to_remove.push_back(&matches[j]);
        }
    }

    // remove collectd matches
    matches.erase(std::remove_if(std::begin(matches), std::end(matches),
        [&] (Match const & m) {
            return contains(to_remove, &m);
        }
    ), std::end(matches));
}

std::string SyntaxHighlighter::highlight(std::string const & input_code, RENDERER_TYPE renderer) const {
    std::vector<Match> all_matches;

    for (auto const & reg : brush.get_regex_list()) {
        // find all matches on a single selector
        std::vector<Match> res = RegexWrapper{reg.regex}.execute_on(input_code);

        // copy coloring methods
        for (auto & m : res) {
            m.methods = reg.methods;
        }

        all_matches.insert(std::end(all_matches), std::begin(res), std::end(res));
    }

    remove_nested(all_matches);

    if (renderer == ANSI) {
        return AnsiRenderer{}.render(input_code, all_matches);

    } else /* if (renderer == HTML) */ {
        return HtmlRenderer{}.render(input_code, all_matches);
    }
}
