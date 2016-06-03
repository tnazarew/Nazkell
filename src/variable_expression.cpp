//
// Created by tomasz on 03.06.16.
//

#include <bits/stringfwd.h>
#include <expressions.h>

namespace nazkell
{
    VariableExpression::VariableExpression(std::string){}
    VariableExpression::~VariableExpression(){}
    Expression::ExpressionType VariableExpression::getType() const
    {

    }
    int VariableExpression::getValue() const
    {

    }
    std::string VariableExpression::toString() const
    {
        return id;
    }
}