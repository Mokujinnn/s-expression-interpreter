#pragma once

#include "Expression.hpp"

class Sub : public Expression
{
public:
    virtual double eval() override;
};