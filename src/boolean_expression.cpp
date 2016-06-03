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

    }
    int BooleanExpression::getValue() const
    {

    }
    std::string BooleanExpression::toString() const
    {
        return std::to_string(value);
    }
}