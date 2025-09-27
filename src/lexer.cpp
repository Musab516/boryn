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

        // Identifiers or keywords
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
        // Numbers
        else if (std::isdigit(src[i])) {
            std::string num;
            while (i < src.size() && (std::isdigit(src[i]) || src[i] == '.')) {
                num.push_back(src[i]);
                i++;
            }
            tokens.push_back({TokenType::NUMBER, num});
        }
        // Strings
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
        // Assignment
        else if (src[i] == '=') {
            if (i + 1 < src.size() && src[i+1] == '=') {
                tokens.push_back({TokenType::OP, "=="});
                i += 2;
            } else {
                tokens.push_back({TokenType::ASSIGN, "="});
                i++;
            }
        }
        // Not equal
        else if (src[i] == '!' && i + 1 < src.size() && src[i+1] == '=') {
            tokens.push_back({TokenType::OP, "!="});
            i += 2;
        }
        // Greater / Less
        else if (src[i] == '>' && i + 1 < src.size() && src[i+1] == '=') {
            tokens.push_back({TokenType::OP, ">="});
            i += 2;
        }
        else if (src[i] == '<' && i + 1 < src.size() && src[i+1] == '=') {
            tokens.push_back({TokenType::OP, "<="});
            i += 2;
        }
        else if (src[i] == '>' || src[i] == '<') {
            tokens.push_back({TokenType::OP, std::string(1, src[i])});
            i++;
        }
        // Colon
        else if (src[i] == ':' ) {
            tokens.push_back({TokenType::COLON, ":"});
            i++;
        }
        // Other operators: + - * /
        else if (src[i] == '+' || src[i] == '-' || src[i] == '*' || src[i] == '/') {
            tokens.push_back({TokenType::OP, std::string(1, src[i])});
            i++;
        }
        else {
            // Unknown character
            tokens.push_back({TokenType::OP, std::string(1, src[i])});
            i++;
        }
    }

    tokens.push_back({TokenType::END_OF_FILE, ""});
    return tokens;
}
