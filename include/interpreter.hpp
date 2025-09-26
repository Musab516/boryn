#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "ast.hpp"
#include <map>
#include <string>

enum class ValueType { INT, DOUBLE, STRING };

struct Value {
    ValueType type;
    int intVal;
    double doubleVal;
    std::string strVal;

    Value() : type(ValueType::STRING), intVal(0), doubleVal(0.0), strVal("") {}
    Value(int v) : type(ValueType::INT), intVal(v), doubleVal(0.0) {}
    Value(double v) : type(ValueType::DOUBLE), intVal(0), doubleVal(v) {}
    Value(const std::string &v) : type(ValueType::STRING), intVal(0), doubleVal(0.0), strVal(v) {}
};

void interpret(const std::vector<std::shared_ptr<Node>> &nodes);

#endif
