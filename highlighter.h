#ifndef HIGHLIGHTER_H_
#define HIGHLIGHTER_H_

#include "brush.h"
#include "renderer.h"

#include <string>
#include <iostream>

class SyntaxHighlighter {
    CppBrush brush;

public:
    std::string highlight(std::string input_code, RENDERER_TYPE renderer) const;
};

#endif