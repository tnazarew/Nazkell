//
// Created by tomasz on 03.06.16.
//

#include <vector>
#include <expressions.h>
#include <sstream>
#include <body.h>

namespace nazkell
{
    FunctionExpression::FunctionExpression(std::string id_, std::vector<std::shared_ptr<Expression> > arguments_)
            : id(id_), arguments(arguments_){}
    FunctionExpression::~FunctionExpression(){}
    Expression::ExpressionType FunctionExpression::getType() const
    {
        return ExpressionType::Fid;
    }

    Value FunctionExpression::evaluate(unsigned int stackID) const
    {
        return Body::getInstance().evaluate(arguments,id);
    }


    std::string FunctionExpression::toString() const
    {
        std::ostringstream args;
        for(auto& i: arguments)
            args << i->toString() << " ";
        return id + "(" + args.str() + ")";
    }
}