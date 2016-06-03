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

    }
    int IntegerExpression::getValue() const
    {

    }
    std::string IntegerExpression::toString() const
    {
        return std::to_string(value);
    }
}