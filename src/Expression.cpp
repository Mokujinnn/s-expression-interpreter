#include "Expression.hpp"

void Expression::add_operand(Expression_ptr expr)
{
    expressions_.push_back(std::move(expr));
}
