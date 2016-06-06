//
// Created by tomasz on 03.06.16.
//

#include <definition.h>
#include <memory>
#include <sstream>

namespace nazkell
{
    Definition::Definition(){};
    Definition::Definition(std::string id, std::vector<std::string> args_, std::vector<std::unique_ptr<Expression > > expressions)
    : did(id), args(args_), expressions(std::move(expressions)){}

    Expression::ExpressionType Definition::getType() const
    {

    }
    int Definition::evaluateInt(unsigned int stack_id) const
    {
        return expressions[0]->evaluateInt(stack_id);
    }

    bool Definition::evaluateBool(unsigned int stack_id) const
    {
        return expressions[0]->evaluateBool(stack_id);
    }
    std::string Definition::toString() const
    {
        std::ostringstream arg, exp;
        for(auto& i:expressions)
            exp << i->toString() << std::endl;
        for(std::string i: args)
            arg << i << " ";
        return did + arg.str() + "=" + exp.str();

    }

    std::string Definition::getID()
    {
        return did;
    }
}