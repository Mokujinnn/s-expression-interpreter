#pragma once

#include "Expression.hpp"

class Mul : public Expression
{
public:
    virtual double eval() override;
};