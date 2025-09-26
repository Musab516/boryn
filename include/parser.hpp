#ifndef PARSER_HPP
#define PARSER_HPP

#include "lexer.hpp"
#include "ast.hpp"

std::vector<std::shared_ptr<Node>> parse(const std::vector<Token> &tokens);

#endif
