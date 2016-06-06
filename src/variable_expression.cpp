//
// Created by tomasz on 03.06.16.
//

#include <bits/stringfwd.h>
#include <expressions.h>
#include <body.h>

namespace nazkell
{
    VariableExpression::VariableExpression(std::string vid): id(vid){}
    VariableExpression::~VariableExpression(){}
    Expression::ExpressionType VariableExpression::getType() const
    {
        return ExpressionType::Id;
    }
    int VariableExpression::evaluateInt(unsigned int stackID) const
    {
        return Body::getInstance().evaluateInt(stackID, getID());
    }
    bool VariableExpression::evaluateBool(unsigned int stackID) const
    {
        return Body::getInstance().evaluateBool(stackID, getID());
    }
    std::string VariableExpression::toString() const
    {
        return id;
    }
    std::string VariableExpression::getID() const
    {
        return id;
    }
}