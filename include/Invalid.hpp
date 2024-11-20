#pragma once

#include "Expression.hpp"

class Invalid : public Expression
{
public:
    virtual double eval() override;
};