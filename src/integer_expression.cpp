//
// Created by tomasz on 03.06.16.
//


#include <expressions.h>

namespace nazkell
{
    IntegerExpression::IntegerExpression(int i): value(i){}
    IntegerExpression::~IntegerExpression()
    { }
    Expression::ExpressionType IntegerExpression::getType() const
    {
        return ExpressionType::Integer;
    }
    int IntegerExpression::evaluateInt(unsigned int stackID) const
    {
        return value;
    }
    bool IntegerExpression::evaluateBool(unsigned int stackID) const
    {
        throwWrongType(ExpressionType::Integer);
    }
    std::string IntegerExpression::toString() const
    {
        return std::to_string(value);
    }
}