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
    Value BooleanExpression::evaluate(unsigned int stackID) const
    {
        if(value.value_type == Value::Type::Integer)
            throwWrongType(ExpressionType::Boolean);
        return value;
    }

    std::string BooleanExpression::toString() const
    {
        return std::to_string(value.b);
    }
}