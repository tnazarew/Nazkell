//
// Created by tomasz on 03.06.16.
//

#include <bits/stringfwd.h>
#include <expressions.h>
#include <sstream>

namespace nazkell
{
    FunctionExpression::FunctionExpression(std::string id_, std::vector<std::unique_ptr<Expression> > arguments_)
            : id(id_), arguments(std::move(arguments_)){}
    FunctionExpression::~FunctionExpression(){}
    Expression::ExpressionType FunctionExpression::getType() const
    {

    }
    int FunctionExpression::getValue() const
    {

    }
    std::string FunctionExpression::toString() const
    {
        std::ostringstream args;
        for(std::unique_ptr<Expression> i: arguments)
            args << i->toString() << " ";
        return id + "(" + args.str() + ")";
    }
}