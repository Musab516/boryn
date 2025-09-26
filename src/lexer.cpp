#include "lexer.hpp"
#include <cctype>
#include <sstream>

static bool isIdentifierChar(char c) {
    return std::isalnum(c) || c == '_';
}

std::vector<Token> tokenize(const std::string &src) {
    std::vector<Token> tokens;
    size_t i = 0;

    while (i < src.size()) {
        if (std::isspace(src[i])) { i++; continue; }

        if (std::isalpha(src[i])) {
            std::string word;
            while (i < src.size() && isIdentifierChar(src[i])) {
                word.push_back(src[i]);
                i++;
            }
            if (word == "let") tokens.push_back({TokenType::LET, word});
            else if (word == "say") tokens.push_back({TokenType::SAY, word});
            else if (word == "provide") tokens.push_back({TokenType::PROVIDE, word});
            else if (word == "when") tokens.push_back({TokenType::WHEN, word});
            else if (word == "not") tokens.push_back({TokenType::NOT, word});
            else if (word == "end") tokens.push_back({TokenType::END, word});
            else tokens.push_back({TokenType::IDENT, word});
        }
        else if (std::isdigit(src[i])) {
            std::string num;
            while (i < src.size() && (std::isdigit(src[i]) || src[i] == '.')) {
                num.push_back(src[i]);
                i++;
            }
            tokens.push_back({TokenType::NUMBER, num});
        }
        else if (src[i] == '"') {
            i++;
            std::string str;
            while (i < src.size() && src[i] != '"') {
                str.push_back(src[i]);
                i++;
            }
            i++;
            tokens.push_back({TokenType::STRING, str});
        }
        else if (src[i] == '=') {
            i++;
            tokens.push_back({TokenType::ASSIGN, "="});
        }
        else if (src[i] == ':' ) {
            i++;
            tokens.push_back({TokenType::COLON, ":"});
        }
        else {
            std::string op(1, src[i]);
            tokens.push_back({TokenType::OP, op});
            i++;
        }
    }

    tokens.push_back({TokenType::END_OF_FILE, ""});
    return tokens;
}
