#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <vector>

enum class TokenType {
    LET, SAY, PROVIDE, WHEN, NOT, END,
    IDENT, NUMBER, STRING,
    OP, ASSIGN,
    COLON,
    END_OF_FILE
};

struct Token {
    TokenType type;
    std::string value;
};

std::vector<Token> tokenize(const std::string &src);

#endif
