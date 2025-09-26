#include "lexer.hpp"
#include "parser.hpp"
#include "interpreter.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

int main(int argc, char* argv[]) {
    std::string filename;

    if (argc >= 2) {
        filename = argv[1];
    } else {
        filename = "main.byn";  // default file
    }

    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Could not open file: " << filename << "\n";
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source = buffer.str();

    try {
        auto tokens = tokenize(source);
        auto ast = parse(tokens);
        interpret(ast);
    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
