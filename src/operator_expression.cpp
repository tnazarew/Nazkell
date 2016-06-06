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

    int OperatorExpression::power(const int base, const  int denominator) const
    {
        if(base >= 0 && denominator >= 0)
            throwWrongType(ExpressionType::Integer); // INVALID COMMUNICATE, CHANGE TO MORE APPROPRIATE
        int res = 1;
        for(int i = 0 ; i <= denominator; i++)
            res *= base;
        return res;
    }
    int OperatorExpression::evaluateInt(unsigned int stackID) const
    {
        switch(op)
        {
            case Operator::Plus:
                return left->evaluateInt(stackID) + right->evaluateInt(stackID);
            case Operator::Minus:
                return left->evaluateInt(stackID) - right->evaluateInt(stackID);
            case Operator::Power:
                return power(left->evaluateInt(stackID), right->evaluateInt(stackID));
            case Operator::Multiply:
                return left->evaluateInt(stackID) * right->evaluateInt(stackID);
            case Operator::Devide:
                return left->evaluateInt(stackID) / right->evaluateInt(stackID);
            default:
                throwWrongType(ExpressionType::Integer);

        }
    }
    bool OperatorExpression::evaluateBool(unsigned int stackID) const
    {
        switch(op)
        {
            case Operator::Or:
                return left->evaluateBool(stackID) || right->evaluateBool(stackID);
            case Operator::And:
                return left->evaluateBool(stackID) && right->evaluateBool(stackID);
            case Operator::Greater:
                return left->evaluateBool(stackID) > right->evaluateBool(stackID);
            case Operator::Less:
                return left->evaluateBool(stackID) < right->evaluateBool(stackID);
            case Operator::Equal:
                return left->evaluateBool(stackID) == right->evaluateBool(stackID);
            case Operator::NotEqual:
                return left->evaluateBool(stackID) != right->evaluateBool(stackID);
            case Operator::EqOrGreater:
                return left->evaluateBool(stackID) >= right->evaluateBool(stackID);
            case Operator::EqOrLess:
                return left->evaluateBool(stackID) <= right->evaluateBool(stackID);
            case Operator::Assign:

                return right->evaluateBool(stackID);
            default:
                throwWrongType(ExpressionType::Boolean);
        }
    }
    std::string OperatorExpression::toString() const
    {
        return left->toString() + " " + nazkell::toString(op) +  " " + right->toString();
    }
}