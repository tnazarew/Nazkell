//
// Created by tomasz on 03.06.16.
//

#include <expressions.h>
#include <sstream>

namespace nazkell
{
    IfExpression::IfExpression(std::vector<std::unique_ptr<Expression> > cond_,
                               std::vector<std::unique_ptr<Expression> > ifexp_,
                               std::vector<std::unique_ptr<Expression> > elseexp_)
            :cond(std::move(cond_)), ifexp(std::move(ifexp_)), elseexp(std::move(elseexp_))
    {}
    IfExpression::~IfExpression()
    { }
    Expression::ExpressionType IfExpression::getType() const
    {
        return ExpressionType::If;
    }
    int IfExpression::evaluateInt(unsigned int stackID) const
    {
        if(cond[0]->evaluateBool(stackID))
        {
            return ifexp[0]->evaluateInt(stackID);
        }
        else
        {
            return elseexp[0]->evaluateInt(stackID);
        }
    }
    bool IfExpression::evaluateBool(unsigned int stackID) const
    {
        if(cond[0]->evaluateBool(stackID))
        {
            return ifexp[0]->evaluateBool(stackID);
        }
        else
        {
            return elseexp[0]->evaluateBool(stackID);
        }
    }
    std::string IfExpression::toString() const
    {
        std::ostringstream con, ife, ele, all;
        for(auto& i: cond)
            con << i->toString() << std::endl;
        for(auto& i: ifexp)
            ife << i->toString() << std::endl;
        for(auto& i: elseexp)
            ele << i->toString() << std::endl;
        all << "if" << std::endl << con.str() << "then" << std::endl << ife.str() << std::endl << "else" << std::endl << ele.str();
        return all.str();
    }
}