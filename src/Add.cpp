#include "Add.hpp"

#include <iostream>

double Add::eval()
{
    double value = 0;

    std::cout << expressions_.size() << '\n';

    for (const auto &expr : expressions_)
    {
        value += expr->eval();
    }

    return value;
}