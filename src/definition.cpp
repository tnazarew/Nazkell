//
// Created by tomasz on 03.06.16.
//

#include <definition.h>
#include <memory>
namespace nazkell
{
    Definition::Definition(){};
    Definition::Definition(std::string id, std::vector<std::unique_ptr<Expression > > expressions)
    : id_(id), expressions_(std::move(expressions)){}

    Expression::ExpressionType Definition::getType() const
    {

    }
    int Definition::getValue() const
    {

    }
    std::string Definition::toString() const
    {

    }
}