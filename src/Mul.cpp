#include "Mul.hpp"

double Mul::eval()
{
    double value = 1;

    for (auto &&expr : expressions_)
    {
        value *= expr->eval();
    }

    return value;
}