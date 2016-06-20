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

    Value IntegerExpression::evaluate(unsigned int stackID) const
    {
        if (value.value_type == Value::Type::Bool)
        {
            throwWrongType(ExpressionType::Integer);
        }
        return value;
    }




    std::string IntegerExpression::toString() const
    {
        return std::to_string(value.i);
    }
}