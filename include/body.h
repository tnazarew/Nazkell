//
// Created by tomasz on 01.06.16.
//

#ifndef NAZKELL_BODY_H
#define NAZKELL_BODY_H

#include <declaration.h>
#include <definition.h>
#include <stack_function.h>
#include <map>

namespace nazkell
{
    class Body
    {
        std::map<std::string, std::shared_ptr<Definition> > definitions;
        std::map<std::string, std::unique_ptr<Declaration> > declarations;
        std::vector<struct StackFunction> stack;
        unsigned int highWaterMark;

        Body();

        Body(std::map<std::string, std::unique_ptr<Declaration>>, std::map<std::string, std::shared_ptr<Definition>>);

        static Body *body;
    public:
        static Body &getInstance();

        static Body &init(std::map<std::string, std::unique_ptr<Declaration>>,
                          std::map<std::string, std::shared_ptr<Definition>>);

        ~Body();

        Value evaluate(const std::vector<std::shared_ptr<Expression>> &args, std::string fid);

        void resetStack();

        unsigned int pushStack(const std::vector<std::pair<std::string, std::shared_ptr<Expression>>>& temp_args,
                               const std::string& fid);

        void popStack();

        void throwFunctionNotDeclared(const std::string&);

        Value evaluate(unsigned int, const std::string&);

        std::shared_ptr<Definition> getDef(const std::string&);

        std::string toString();

    };
}
#endif //NAZKELL_BODY_H

