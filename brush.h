#ifndef BRUSH_H_
#define BRUSH_H_

#include <vector>
#include <string>

struct ColoringMethods {
    std::string css_classes;
    std::string ansi_color_code;
    ColoringMethods(std::string css_classes = "", std::string ansi_color_code = "");
};

struct Painter {
    std::string regex;
    ColoringMethods methods;
    Painter(std::string regex, ColoringMethods methods);
};

class Brush {
public:
    virtual std::vector<Painter> get_regex_list() const = 0;
};

class CppBrush : public Brush {
public:
    std::vector<Painter> get_regex_list() const;
};

#endif