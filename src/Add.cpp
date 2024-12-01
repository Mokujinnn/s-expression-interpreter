#include "Add.hpp"

double Add::eval()
{
    double value = 0;

    for (const auto &expr : expressions_)
    {
        value += expr->eval();
    }

    return value;
}