//
// Created by tomasz on 03.06.16.
//

#include <expressions.h>
#include <sstream>

namespace nazkell
{
    IfExpression::IfExpression(std::unique_ptr<Expression> cond_,
                               std::unique_ptr<Expression> ifexp_,
                               std::unique_ptr<Expression> elseexp_)
            :cond(std::move(cond_)), ifexp(std::move(ifexp_)), elseexp(std::move(elseexp_))
    {}
    IfExpression::~IfExpression()
    { }
    Expression::ExpressionType IfExpression::getType() const
    {
        return ExpressionType::If;
    }

    Value IfExpression::evaluate(unsigned int stackID) const
    {
        if(cond->evaluate(stackID).expectType(Value::Type::Bool).b)
        {
            return ifexp->evaluate(stackID);
        }
        else
        {
            return elseexp->evaluate(stackID);
        }
    }

    std::string IfExpression::toString() const
    {
        std::ostringstream all;
        all << "if" << " " << cond->toString() << std::endl << ifexp->toString() << std::endl << "else" << std::endl <<  elseexp->toString() ;
        return all.str();
    }
}