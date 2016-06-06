//
// Created by tomasz on 03.06.16.
//

#include <expressions.h>

namespace nazkell
{
    BooleanExpression::BooleanExpression(bool b): value(b){}
    BooleanExpression::~BooleanExpression()
    { }
    Expression::ExpressionType BooleanExpression::getType() const
    {
        return ExpressionType::Boolean;
    }
    int BooleanExpression::evaluateInt(unsigned int stackID) const
    {
        throwWrongType(ExpressionType::Boolean);
    }
    bool BooleanExpression::evaluateBool(unsigned int stackID) const
    {
        return value;
    }
    std::string BooleanExpression::toString() const
    {
        return std::to_string(value);
    }
}