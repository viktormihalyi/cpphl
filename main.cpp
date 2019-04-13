#include "highlighter.h"
#include "renderer.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

std::string read_file_content(std::string file_path) {
    std::ifstream f(file_path);

    if (!f.is_open()) {
        throw std::runtime_error{"no file named \"" + file_path + "\""};
    }

    std::stringstream file_text;
    std::string line;
    while (std::getline(f, line)) {
        file_text << line << std::endl;
    }

    return file_text.str();
}


int main(int argc, char* argv[]) {
    if (argc == 1) {
        std::cerr << "too few arguments" << std::endl;
        return EXIT_FAILURE;
    }

    if (argc > 3) {
        std::cerr << "too many arguments" << std::endl;
        return EXIT_FAILURE;
    }

    std::string source_code = "";
    RENDERER_TYPE renderer = ANSI;

    // parse arguments
    for (int i = 1; i < argc; i++) {
        std::string arg{argv[i]};

        if (arg == "--html" || arg == "-h") {
            renderer = HTML;

        } else {
            if (!source_code.empty()) {
                std::cerr << "bad arguments" << std::endl;
                return EXIT_FAILURE;
            }

            try {
                source_code = read_file_content(arg);
            } catch (std::runtime_error & e) {
                std::cerr << e.what() << std::endl;
                return EXIT_FAILURE;
            }
        }
    }

    if (source_code.empty()) {
        std::cerr << "no source code file defined" << std::endl;
        return EXIT_FAILURE;
    }

    SyntaxHighlighter sh;
    std::string highlighted_source = sh.highlight(source_code, renderer);
    std::cout << highlighted_source << std::endl;

    return EXIT_SUCCESS;
}