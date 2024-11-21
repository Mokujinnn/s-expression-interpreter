#include "Div.hpp"

#include <stdexcept>

double Div::eval()
{
    double value = expressions_[0]->eval();

    for (auto itb = expressions_.begin() + 1, ite = expressions_.end(); itb != ite; ++itb)
    {
        const auto &expr = *itb;
        double v = expr->eval();
        if (v == 0.0)
        {
            throw std::runtime_error("Division by zero");
        }

        value /= v;
    }

    return value;
}