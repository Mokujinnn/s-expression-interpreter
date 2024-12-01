#pragma once

#include "Expression.hpp"

class Number : public Expression
{
protected:
    double num_;

public:
    Number(double s);

    virtual double eval() override;
};