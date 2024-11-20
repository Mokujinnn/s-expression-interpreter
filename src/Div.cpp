#include "Div.hpp"

double Div::eval()
{
    double value = expressions_[0]->eval();

    for (auto itb = expressions_.begin() + 1, ite = expressions_.end(); itb != ite; ++ite)
    {
        const auto &expr = *itb;
        value /= expr->eval();
    }

    return value;
}