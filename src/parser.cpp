// #include "parser.hpp"
// #include <stdexcept>

// static size_t pos;
// static std::vector<Token> toks;

// static Token peek() { return toks[pos]; }
// static Token advance() { return toks[pos++]; }

// static std::shared_ptr<Expr> parseExpr();

// static std::shared_ptr<Expr> parsePrimary() {
//     Token t = advance();
//     if (t.type == TokenType::NUMBER || t.type == TokenType::STRING)
//         return std::make_shared<LiteralExpr>(t.value);
//     if (t.type == TokenType::IDENT)
//         return std::make_shared<VarExpr>(t.value);
//     throw std::runtime_error("Unexpected token in expression: " + t.value);
// }

// static std::shared_ptr<Expr> parseExpr() {
//     auto left = parsePrimary();
//     while (peek().type == TokenType::OP) {
//         std::string op = advance().value;
//         auto right = parsePrimary();
//         left = std::make_shared<BinaryExpr>(left, op, right);
//     }
//     return left;
// }

// static std::shared_ptr<Node> parseStatement() {
//     Token t = advance();
//     if (t.type == TokenType::LET) {
//         Token name = advance();
//         if (advance().type != TokenType::ASSIGN) throw std::runtime_error("Expected =");
//         if (peek().type == TokenType::PROVIDE) {
//             advance();
//             Token prompt = advance();
//             if (prompt.type != TokenType::STRING) throw std::runtime_error("Expected string after provide");
//             return std::make_shared<ProvideNode>(name.value, prompt.value);
//         }
//         auto expr = parseExpr();
//         return std::make_shared<AssignNode>(name.value, expr);
//     }
//     if (t.type == TokenType::SAY) {
//         auto expr = parseExpr();
//         return std::make_shared<SayNode>(expr);
//     }
//     if (t.type == TokenType::WHEN) {
//         auto cond = parseExpr();
//         if (advance().type != TokenType::COLON) throw std::runtime_error("Expected : after condition");
//         auto whenNode = std::make_shared<WhenNode>(cond);

//         while (peek().type != TokenType::NOT && peek().type != TokenType::END && peek().type != TokenType::END_OF_FILE) {
//             whenNode->trueBranch.push_back(parseStatement());
//         }
//         if (peek().type == TokenType::NOT) {
//             advance();
//             if (advance().type != TokenType::COLON) throw std::runtime_error("Expected : after not");
//             while (peek().type != TokenType::END && peek().type != TokenType::END_OF_FILE) {
//                 whenNode->falseBranch.push_back(parseStatement());
//             }
//         }
//         if (peek().type == TokenType::END) advance();
//         return whenNode;
//     }
//     throw std::runtime_error("Unknown statement: " + t.value);
// }

// std::vector<std::shared_ptr<Node>> parse(const std::vector<Token> &tokens) {
//     toks = tokens;
//     pos = 0;
//     std::vector<std::shared_ptr<Node>> nodes;
//     while (peek().type != TokenType::END_OF_FILE) {
//         nodes.push_back(parseStatement());
//     }
//     return nodes;
// }

#include "parser.hpp"
#include <stdexcept>

static size_t pos;
static std::vector<Token> toks;

static Token peek() { return toks[pos]; }
static Token advance() { return toks[pos++]; }

static std::shared_ptr<Expr> parseExpr();

// Parse a literal (number or string) or variable
static std::shared_ptr<Expr> parsePrimary() {
    Token t = advance();
    if (t.type == TokenType::NUMBER || t.type == TokenType::STRING)
        return std::make_shared<LiteralExpr>(t.value, t.type);
    if (t.type == TokenType::IDENT)
        return std::make_shared<VarExpr>(t.value);
    throw std::runtime_error("Unexpected token in expression: " + t.value);
}

// Parse binary expressions (supports +, -, *, /, ==, !=)
static std::shared_ptr<Expr> parseExpr() {
    auto left = parsePrimary();
    while (peek().type == TokenType::OP) {
        std::string op = advance().value;
        auto right = parsePrimary();
        left = std::make_shared<BinaryExpr>(left, op, right);
    }
    return left;
}

// Parse statements like let, say, when/not
static std::shared_ptr<Node> parseStatement() {
    Token t = advance();

    // Variable declaration
    if (t.type == TokenType::LET) {
        Token name = advance();
        if (advance().type != TokenType::ASSIGN) throw std::runtime_error("Expected =");

        // Handle provide input
        if (peek().type == TokenType::PROVIDE) {
            advance();
            Token prompt = advance();
            if (prompt.type != TokenType::STRING) throw std::runtime_error("Expected string after provide");
            return std::make_shared<ProvideNode>(name.value, prompt.value);
        }

        auto expr = parseExpr();
        return std::make_shared<AssignNode>(name.value, expr);
    }

    // Print statement
    if (t.type == TokenType::SAY) {
        auto expr = parseExpr();
        return std::make_shared<SayNode>(expr);
    }

    // Conditional statement
    if (t.type == TokenType::WHEN) {
        auto cond = parseExpr();  // supports == and !=
        if (advance().type != TokenType::COLON) throw std::runtime_error("Expected : after condition");

        auto whenNode = std::make_shared<WhenNode>(cond);

        // True branch
        while (peek().type != TokenType::NOT && peek().type != TokenType::END && peek().type != TokenType::END_OF_FILE) {
            whenNode->trueBranch.push_back(parseStatement());
        }

        // False branch
        if (peek().type == TokenType::NOT) {
            advance();
            if (advance().type != TokenType::COLON) throw std::runtime_error("Expected : after not");
            while (peek().type != TokenType::END && peek().type != TokenType::END_OF_FILE) {
                whenNode->falseBranch.push_back(parseStatement());
            }
        }

        if (peek().type == TokenType::END) advance();
        return whenNode;
    }

    throw std::runtime_error("Unknown statement: " + t.value);
}

// Main parser function
std::vector<std::shared_ptr<Node>> parse(const std::vector<Token> &tokens) {
    toks = tokens;
    pos = 0;
    std::vector<std::shared_ptr<Node>> nodes;
    while (peek().type != TokenType::END_OF_FILE) {
        nodes.push_back(parseStatement());
    }
    return nodes;
}
