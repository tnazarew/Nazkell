//
// Created by tomasz on 05.06.16.
//

#ifndef NAZKELL_STACK_FUNCTION_H
#define NAZKELL_STACK_FUNCTION_H

#include <bits/stringfwd.h>
#include <bits/unique_ptr.h>
#include <bits/stl_vector.h>
#include <expression.h>

namespace nazkell
{
    struct StackFunction
    {
        std::string name;
        std::vector<std::pair<std::string, std::shared_ptr<Expression> > > functions;
        unsigned int parent_stack_id;
        StackFunction(std::vector<std::pair<std::string, std::shared_ptr<Expression>>> args_, std::string name_,
                      unsigned int parent_stack_id):
                    functions(args_), name(name_), parent_stack_id(parent_stack_id)
        {

        }

        StackFunction()
        {

        }

        ~StackFunction(){
            functions.clear();
        }
    };
}

#endif //NAZKELL_STACK_FUNCTION_H
