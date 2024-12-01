#include "Number.hpp"

Number::Number(double s = 0)
    : num_(s)
{
}

double Number::eval()
{
    return num_;
}