#include "interpreter.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>

static std::map<std::string, Value> variables;

static Value evalExpr(std::shared_ptr<Expr> expr);

static Value autoConvert(const std::string &s) {
    std::istringstream iss(s);
    int iv; double dv;
    if (iss >> iv && iss.eof()) return Value(iv);
    iss.clear(); iss.str(s);
    if (iss >> dv && iss.eof()) return Value(dv);
    return Value(s);
}

static std::string toString(const Value &v) {
    switch (v.type) {
        case ValueType::INT: return std::to_string(v.intVal);
        case ValueType::DOUBLE: return std::to_string(v.doubleVal);
        case ValueType::STRING: return v.strVal;
    }
    return "";
}

static Value applyOp(const Value &l, const std::string &op, const Value &r) {
    if (op == "+") {
        if (l.type == ValueType::STRING || r.type == ValueType::STRING)
            return Value(toString(l) + toString(r));
        if (l.type == ValueType::DOUBLE || r.type == ValueType::DOUBLE)
            return Value((l.type == ValueType::DOUBLE ? l.doubleVal : l.intVal) + (r.type == ValueType::DOUBLE ? r.doubleVal : r.intVal));
        return Value(l.intVal + r.intVal);
    }
    if (op == "-") return Value(l.intVal - r.intVal);
    if (op == "*") return Value(l.intVal * r.intVal);
    if (op == "/") return Value(l.intVal / r.intVal);
    if (op == "==") return Value(toString(l) == toString(r) ? 1 : 0);
    if (op == "!=") return Value(toString(l) != toString(r) ? 1 : 0);
    if (op == ">") return Value(std::stod(toString(l)) > std::stod(toString(r)) ? 1 : 0);
    if (op == "<") return Value(std::stod(toString(l)) < std::stod(toString(r)) ? 1 : 0);
    if (op == ">=") return Value(std::stod(toString(l)) >= std::stod(toString(r)) ? 1 : 0);
    if (op == "<=") return Value(std::stod(toString(l)) <= std::stod(toString(r)) ? 1 : 0);
    throw std::runtime_error("Unknown operator: " + op);
}

static Value evalExpr(std::shared_ptr<Expr> expr) {
    if (auto lit = dynamic_cast<LiteralExpr*>(expr.get())) {
        return autoConvert(lit->value);
    }
    if (auto var = dynamic_cast<VarExpr*>(expr.get())) {
        return variables[var->name];
    }
    if (auto bin = dynamic_cast<BinaryExpr*>(expr.get())) {
        Value l = evalExpr(bin->left);
        Value r = evalExpr(bin->right);
        return applyOp(l, bin->op, r);
    }
    throw std::runtime_error("Unknown expression");
}

void interpret(const std::vector<std::shared_ptr<Node>> &nodes) {
    for (auto &n : nodes) {
        if (n->type() == NodeType::ASSIGN) {
            auto a = std::dynamic_pointer_cast<AssignNode>(n);
            variables[a->name] = evalExpr(a->expr);
        }
        else if (n->type() == NodeType::SAY) {
            auto s = std::dynamic_pointer_cast<SayNode>(n);
            std::cout << toString(evalExpr(s->expr)) << std::endl;
        }
        else if (n->type() == NodeType::PROVIDE) {
            auto p = std::dynamic_pointer_cast<ProvideNode>(n);
            std::cout << p->prompt << " ";
            std::string input;
            std::getline(std::cin, input);
            variables[p->varName] = autoConvert(input);
        }
        else if (n->type() == NodeType::WHEN) {
            auto w = std::dynamic_pointer_cast<WhenNode>(n);
            Value cond = evalExpr(w->condition);
            bool condTrue = (cond.type == ValueType::INT && cond.intVal != 0);
            if (condTrue) interpret(w->trueBranch);
            else interpret(w->falseBranch);
        }
    }
}
