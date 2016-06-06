//
// Created by tomasz on 01.06.16.
//

#ifndef NAZKELL_BODY_H
#define NAZKELL_BODY_H

#include <declaration.h>
#include <definition.h>
#include <stack_function.h>
namespace nazkell
{
    class Body
    {
        std::vector< std::unique_ptr<Definition> > definitions;
        std::vector< std::unique_ptr<Declaration> > declarations;
        std::vector<struct StackFunction> stack;
        unsigned int highWaterMark;
        Body();
        Body(std::vector< std::unique_ptr<Declaration> >, std::vector< std::unique_ptr<Definition> >);
        static Body* body;
    public:
        static Body& getInstance();
        static Body& init(std::vector< std::unique_ptr<Declaration> >, std::vector< std::unique_ptr<Definition> >);
        int evaluateInt(std::vector<std::shared_ptr<Expression> > args, std::string fid, const unsigned int parent_stock_id);
        bool evaluateBool(std::vector<std::shared_ptr<Expression> > args, std::string fid, const unsigned int parent_stock_id);
        bool checkType(std::string, const Expression::ExpressionType);
        unsigned int pushStack(std::vector<std::pair<std::string, std::shared_ptr<Expression> > > temp_args, std::string fid);
        void popStack();
        unsigned getHWM();
        int evaluateInt(unsigned int, std::string);
        bool evaluateBool(unsigned int, std::string);
        std::unique_ptr<Definition> getDef(std::string);
        std::string toString();

    };
}
#endif //NAZKELL_BODY_H

