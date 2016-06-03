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
        Definition(std::string, std::vector<std::unique_ptr<Expression > >);
    };
}
#endif //NAZKELL_DEFINITION_H
