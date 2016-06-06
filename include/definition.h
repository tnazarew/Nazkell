//
// Created by tomasz on 29.05.16.
//

#ifndef NAZKELL_DEFINITION_H
#define NAZKELL_DEFINITION_H
#include <vector>
#include <expression.h>
#include <string>
namespace nazkell
{
    class Definition
    {
        std::string did;
        std::vector<std::string> args;
        std::vector<std::unique_ptr<Expression> > expressions;

    public:
        Definition();
        Definition(std::string, std::vector<std::string> args_, std::vector<std::unique_ptr<Expression > >);
        std::string toString() const;
        std::string getID();
        int evaluateInt(unsigned int) const;
        bool evaluateBool(unsigned int) const;
        std::vector<std::string > getArgs();
        Expression::ExpressionType getType() const;
    };
}
#endif //NAZKELL_DEFINITION_H
