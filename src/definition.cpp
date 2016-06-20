//
// Created by tomasz on 03.06.16.
//

#include <definition.h>
#include <memory>
#include <sstream>

namespace nazkell
{
    Definition::Definition(){};
    Definition::Definition(std::string id, std::vector<std::string> args_, std::unique_ptr<Expression > expressions)
    : did(id), args(args_), expressions(std::move(expressions)){}


    Value Definition::evaluate(unsigned int stack_id) const
    {
        return expressions->evaluate(stack_id);
    }

    std::string Definition::toString() const
    {
        std::ostringstream arg;
        for(std::string i: args)
            arg << i << " ";
        return did + " " + arg.str() + "= " + expressions->toString();

    }

    std::string Definition::getID()
    {
        return did;
    }
}