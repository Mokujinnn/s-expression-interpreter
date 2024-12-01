#pragma once

#include "Expression.hpp"

class Add : public Expression
{
public:
    virtual double eval() override;
};