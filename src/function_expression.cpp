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
            : id(id_), arguments(std::move(arguments_)){}
    FunctionExpression::~FunctionExpression(){}
    Expression::ExpressionType FunctionExpression::getType() const
    {
        return ExpressionType::Fid;
    }
    int FunctionExpression::evaluateInt(unsigned int stackID) const
    {
        if(Body::getInstance().checkType(id, ExpressionType::Integer))
        {
            throwWrongType(ExpressionType::Integer);
            return 0;
        }
        else
        {
            std::vector<std::unique_ptr<Expression> > s;
//            std::unique_ptr<Expression> e = std::move(arguments[0]);
//            for(int i = 0; i < arguments.size(); i++)
//            {
//                arguments[i]->evaluateInt(stackID);
//                s.push_back(std::move(arguments[i]));
//            }
//
//
//            s = std::move(arguments);
            return Body::getInstance().evaluateInt(arguments,id, stackID);
            return 0;
        }
    }
    bool FunctionExpression::evaluateBool(unsigned int stackID) const
    {
        if(Body::getInstance().checkType(id, ExpressionType::Integer))
        {
            throwWrongType(ExpressionType::Integer);
            return false;
        }
        else
        {
//            return Body::getInstance().evaluateBool(std::move(arguments),id, stackID);
            return false;
        }

    }
    std::string FunctionExpression::toString() const
    {
        std::ostringstream args;
        for(auto& i: arguments)
            args << i->toString() << " ";
        return id + "(" + args.str() + ")";
    }
}