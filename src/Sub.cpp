#include "Sub.hpp"

double Sub::eval()
{
    if (expressions_.size() == 1)
    {
        return -expressions_[0]->eval();
    }

    double value = expressions_[0]->eval();

    for (auto itb = expressions_.begin() + 1, ite = expressions_.end(); itb != ite; ++itb)
    {
        const auto &expr = *itb;
        value -= expr->eval();
    }

    return value;
}