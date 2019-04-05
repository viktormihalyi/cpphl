#ifndef RENDERER_H_
#define RENDERER_H_

#include "regexwrapper.h"

#include <string>
#include <vector>


class Renderer {
    virtual std::string render_color(std::string string_to_color, Match const * match) const = 0;
    virtual std::string render_after(std::string input) const { return input; };

public:
    std::string render(std::string input, std::vector<Match> const & matches) const;
};

enum RENDERER_TYPE {
    HTML, ANSI
};

class HtmlRenderer : public Renderer {
    std::string render_color(std::string string_to_color, Match const * match) const;
    std::string render_after(std::string input) const;
};

class AnsiRenderer : public Renderer {
    std::string render_color(std::string string_to_color, Match const * match) const;
};

#endif