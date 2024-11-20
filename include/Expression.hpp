#pragma once

#include <memory>
#include <vector>

class Expression;

using Expression_ptr = std::unique_ptr<Expression>;
using Expressions_t = std::vector<Expression_ptr>;

class Expression
{
protected:
    Expressions_t expressions_;

public:
    ~Expression() = default;

    virtual double eval() = 0;
    void add_operand(Expression_ptr expr);
};