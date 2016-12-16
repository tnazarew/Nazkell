    //
// Created by tomasz on 03.06.16.
//

#include <bits/stringfwd.h>
#include <expressions.h>
#include <body.h>

namespace nazkell
{
    VariableExpression::VariableExpression(std::string vid) : id(vid)
    { }

    VariableExpression::~VariableExpression()
    { }

    Expression::ExpressionType VariableExpression::getType() const
    {
        return ExpressionType::Id;
    }


    Value VariableExpression::evaluate(unsigned int stackID) const
    {
        Value v = Body::getInstance().evaluate(stackID, id);
        return v;
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