//
// Created by tomasz on 01.06.16.
//

#ifndef NAZKELL_BODY_H
#define NAZKELL_BODY_H

#include <declaration.h>
#include <definition.h>
namespace nazkell
{
    class Body
    {
        std::vector< std::unique_ptr<Definition> > definitions;
        std::vector< std::unique_ptr<Declaration> > declarations;
    public:
        void addDeclaration(std::unique_ptr<Declaration> ptr){declarations.push_back(std::move(ptr));}
        void addDefinition(std::unique_ptr<Definition> ptr){definitions.push_back(std::move(ptr));}


    };
}
#endif //NAZKELL_BODY_H
