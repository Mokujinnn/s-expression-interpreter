#pragma once

#include <vector>

class Expression
{
protected:
    std::vector<Expression> expressions;

public:
    Expression(/* args */);
    ~Expression() = default;
};

Expression::Expression(/* args */)
{
}