#pragma once

#include "Expression.hpp"

class Div : public Expression
{
public:
    virtual double eval() override;
};