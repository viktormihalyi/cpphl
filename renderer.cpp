#include "renderer.h"

#include "stringutils.h"

std::string Renderer::render(std::string input, std::vector<Match> const & matches) const {
    std::string result;

    // add text BEFORE the first match
    auto const & last_match = matches[matches.size() - 1];
    std::string text_before_first_tag = input.substr(last_match.to + 1);
    result += render_color(text_before_first_tag, nullptr);

    for (int i = matches.size() - 1; i >= 0; i--) {
        Match const & m = matches[i];
        // color the match itself
        result = render_color(m.match, &m) + result;

        if (i > 0) {
            // add text BETWEEN matches
            auto const & previous = matches[i - 1];
            std::string text_between = input.substr(previous.to + 1, m.from - (previous.to + 1));
            result = render_color(text_between, nullptr) + result;
        }
    }

    // add text AFTER the last match
    auto const & first_match = matches[0];
    std::string text_after_last_tag = input.substr(0, first_match.from);
    result = render_color(text_after_last_tag, nullptr) + result;

    // renderers might need to do something after
    // HtmlRenderer adds a surrounding block of html, head, body, ...
    result = render_after(result);

    return result;
}

std::string escape_lt_gt(std::string const & s) {
    std::string result = s;
    result = replace(result, "<", "&lt;");
    result = replace(result, ">", "&gt;");
    return result;
}

std::string HtmlRenderer::render_color(std::string string_to_color, Match const * match) const {
    std::string escaped_string = escape_lt_gt(string_to_color);
    if (match == nullptr) {
        return escaped_string;
    } else {
        return "<span class=\"" + match->methods.css_classes + "\">" + escaped_string + "</span>";
    }
}

std::string HtmlRenderer::render_after(std::string input) const {
    return R"(<html><head><link href="style.css" rel="stylesheet" type="text/css"></head><body><pre><code>)"
        + input
        + "</code></pre></body></html>";
}

std::string AnsiRenderer::render_color(std::string string_to_color, Match const * match) const {
    if (match == nullptr) {
        return string_to_color;
    } else {
        return match->methods.ansi_color_code + string_to_color + "\033[0m";
    }
}