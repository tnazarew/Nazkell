//
// Created by tomasz on 03.06.16.
//

#include <expressions.h>


namespace nazkell
{
    OperatorExpression::OperatorExpression(std::unique_ptr<Expression> l, Operator o, std::unique_ptr<Expression> r)
                :left(std::move(l)), op(o), right(std::move(r)){}
    OperatorExpression::~OperatorExpression()
    { }
    Expression::ExpressionType OperatorExpression::getType() const
    {

    }
    int OperatorExpression::getValue() const
    {

    }
    std::string OperatorExpression::toString() const
    {
        return left->toString() + " " + toString(op) +  " " + right->toString();
    }
}