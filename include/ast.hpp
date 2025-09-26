#ifndef AST_HPP
#define AST_HPP

#include <string>
#include <vector>
#include <memory>

enum class NodeType {
    ASSIGN,
    SAY,
    PROVIDE,
    WHEN
};

struct Node {
    virtual ~Node() = default;
    virtual NodeType type() const = 0;
};

struct Expr {
    virtual ~Expr() = default;
};

struct LiteralExpr : Expr {
    std::string value;
    LiteralExpr(const std::string &v) : value(v) {}
};

struct VarExpr : Expr {
    std::string name;
    VarExpr(const std::string &n) : name(n) {}
};

struct BinaryExpr : Expr {
    std::shared_ptr<Expr> left;
    std::string op;
    std::shared_ptr<Expr> right;
    BinaryExpr(std::shared_ptr<Expr> l, const std::string &o, std::shared_ptr<Expr> r)
        : left(l), op(o), right(r) {}
};

struct AssignNode : Node {
    std::string name;
    std::shared_ptr<Expr> expr;
    AssignNode(const std::string &n, std::shared_ptr<Expr> e) : name(n), expr(e) {}
    NodeType type() const override { return NodeType::ASSIGN; }
};

struct SayNode : Node {
    std::shared_ptr<Expr> expr;
    SayNode(std::shared_ptr<Expr> e) : expr(e) {}
    NodeType type() const override { return NodeType::SAY; }
};

struct ProvideNode : Node {
    std::string varName;
    std::string prompt;
    ProvideNode(const std::string &vn, const std::string &p) : varName(vn), prompt(p) {}
    NodeType type() const override { return NodeType::PROVIDE; }
};

struct WhenNode : Node {
    std::shared_ptr<Expr> condition;
    std::vector<std::shared_ptr<Node>> trueBranch;
    std::vector<std::shared_ptr<Node>> falseBranch;
    WhenNode(std::shared_ptr<Expr> cond) : condition(cond) {}
    NodeType type() const override { return NodeType::WHEN; }
};

#endif
