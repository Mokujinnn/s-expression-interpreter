#include "Sub.hpp"

double Sub::eval()
{
    double value = 0;

    for (auto &&expr : expressions_)
    {
        value -= expr->eval();
    }

    return value;
}