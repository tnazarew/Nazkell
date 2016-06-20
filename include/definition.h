//
// Created by tomasz on 29.05.16.
//

#ifndef NAZKELL_DEFINITION_H
#define NAZKELL_DEFINITION_H
#include <vector>
#include <expression.h>
#include <string>
#include <value.h>
namespace nazkell
{
    class Definition
    {
        std::string did;
        std::vector<std::string> args;
        std::unique_ptr<Expression> expressions;

    public:
        Definition();
        Definition(std::string, std::vector<std::string> args_, std::unique_ptr<Expression>);
        std::string toString() const;
        std::string getID();
        Value evaluate(unsigned int) const;
        std::vector<std::string > getArgs();

    };
}
#endif //NAZKELL_DEFINITION_H
