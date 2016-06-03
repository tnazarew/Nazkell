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

    }
    int IfExpression::getValue() const
    {

    }
    std::string IfExpression::toString() const
    {
        std::ostringstream con, ife, ele, all;
        for(std::unique_ptr<Expression> i: cond)
            con << i->toString() << std::endl;
        for(std::unique_ptr<Expression> i: ifexp)
            ife << i->toString() << std::endl;
        for(std::unique_ptr<Expression> i: elseexp)
            ele << i->toString() << std::endl;
        all << "if" << std::endl << con << "then" << std::endl << ife << std::endl << "else" << std::endl << ele;
        return all.str();
    }
}