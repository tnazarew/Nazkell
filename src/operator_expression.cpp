//
// Created by tomasz on 03.06.16.
//

#include <expressions.h>
#include <operator.h>

namespace nazkell
{
    OperatorExpression::OperatorExpression(std::unique_ptr<Expression> l, Operator o, std::unique_ptr<Expression> r)
                :left(std::move(l)), op(o), right(std::move(r)){}
    OperatorExpression::~OperatorExpression()
    { }
    Expression::ExpressionType OperatorExpression::getType() const
    {
        return ExpressionType::Operator;
    }

    Value OperatorExpression::power(const Value base, const  Value denominator) const
    {
        if(base.i >= 0 && denominator.i >= 0)
            throwWrongType(ExpressionType::Integer); // INVALID COMMUNICATE, CHANGE TO MORE APPROPRIATE
        Value res;
        res.i = 1;
        for(int i = 0 ; i <= denominator.i; i++)
            res.i *= base.i;
        return res;
    }


    Value OperatorExpression::evaluate(unsigned int stackID) const
    {
//        std::cout << "TEST: " << toString() << std::endl;
        switch (op)
        {
            case Operator::Plus:
                return left->evaluate(stackID).expectType(Value::Type::Integer).i + right->evaluate(stackID).expectType(Value::Type::Integer).i;
            case Operator::Minus:
                return left->evaluate(stackID).expectType(Value::Type::Integer).i - right->evaluate(stackID).expectType(Value::Type::Integer).i;
            case Operator::Power:
                return power(left->evaluate(stackID).expectType(Value::Type::Integer), right->evaluate(stackID).expectType(Value::Type::Integer));
            case Operator::Multiply:
                return left->evaluate(stackID).expectType(Value::Type::Integer).i * right->evaluate(stackID).expectType(Value::Type::Integer).i;
            case Operator::Devide:
                return left->evaluate(stackID).expectType(Value::Type::Integer).i / right->evaluate(stackID).expectType(Value::Type::Integer).i;
            case Operator::Or:
                return left->evaluate(stackID).expectType(Value::Type::Bool).b || right->evaluate(stackID).expectType(Value::Type::Bool).b;
            case Operator::And:
                return left->evaluate(stackID).expectType(Value::Type::Bool).b && right->evaluate(stackID).expectType(Value::Type::Bool).b;
            case Operator::Greater:
                return left->evaluate(stackID).expectType(Value::Type::Integer).i > right->evaluate(stackID).expectType(Value::Type::Integer).i;
            case Operator::Less:
                return left->evaluate(stackID).expectType(Value::Type::Integer).i < right->evaluate(stackID).expectType(Value::Type::Integer).i;
            case Operator::Equal:
                return Value(left->evaluate(stackID) == right->evaluate(stackID));
            case Operator::NotEqual:
                return Value(left->evaluate(stackID) != right->evaluate(stackID));
            case Operator::EqOrGreater:
                return left->evaluate(stackID).expectType(Value::Type::Integer).i >= right->evaluate(stackID).expectType(Value::Type::Integer).i ;
            case Operator::EqOrLess:
                return left->evaluate(stackID).expectType(Value::Type::Integer).i <= right->evaluate(stackID).expectType(Value::Type::Integer).i ;
        }
    }

    std::string OperatorExpression::toString() const
    {
        return left->toString() + " " + nazkell::toString(op) +  " " + right->toString();
    }
}