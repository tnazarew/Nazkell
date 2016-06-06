//
// Created by tomasz on 01.06.16.
//

#include <body.h>
#include <sstream>
#include <stack_function.h>


namespace nazkell
{

    Body* Body::body = 0;

    std::string Body::toString()
    {
        std::ostringstream out;
        for (auto &i: Body::definitions)
            out << i->toString() << std::endl;
        for (auto &i: Body::declarations)
            out << i->toString() << std::endl;
        return out.str();
    }

    Body::Body(){}


    Body::Body(std::vector<std::unique_ptr<Declaration> > dec, std::vector<std::unique_ptr<Definition> > def):
        definitions(std::move(def)), declarations(std::move(dec)), highWaterMark(0), stack() {  }

    int Body::evaluateInt(std::vector<std::shared_ptr<Expression> > args, std::string fid, const unsigned int parent_stack_id)
    {
        std::unique_ptr<Definition> d = std::move(getDef(fid));
        std::vector<std::pair<std::string, std::shared_ptr<Expression> > > temp_args;
        for(int i = 0 ; i < args.size(); i++)
        {
            temp_args.push_back(std::make_pair(d->getArgs()[i], args[i]));
        }
        unsigned new_stack_id = pushStack(temp_args, fid);
        int res = d->evaluateInt(new_stack_id);
        popStack();
        return res;
    }



    bool Body::evaluateBool(std::vector<std::shared_ptr<Expression> > args, std::string fid, const unsigned int parent_stack_id)
    {
        std::unique_ptr<Definition> d = std::move(getDef(fid));
        std::vector<std::pair<std::string, std::shared_ptr<Expression> > > temp_args;
        for(int i = 0 ; i < args.size(); i++)
        {
            temp_args.push_back(std::move(std::make_pair(d->getArgs()[i], std::move(args[i]))));
        }
        unsigned new_stack_id = pushStack(temp_args, fid);
        bool res = d->evaluateBool(new_stack_id);
        popStack();
        return res;
    }

    int Body::evaluateInt(unsigned int stackID, std::string argID)
    {
        for(int i = 0; i < stack[stackID].args.size(); i++)
        {
            if(stack[stackID].args[i].first == argID)
                return stack[stackID].args[i].second->evaluateInt(stack[stackID].parent_stack_id);
        }
    }

    bool Body::evaluateBool(unsigned int stackID, std::string argID)
    {
        for(int i = 0; i < stack[stackID].args.size(); i++)
        {
            if(stack[stackID].args[i].first == argID)
                return stack[stackID].args[i].second->evaluateBool(stack[stackID].parent_stack_id);
        }
    }

    bool Body::checkType(std::string id, const Expression::ExpressionType given)
    {
        int i = 0;
        for(; i < declarations.size(); i++)
        {
            if(declarations[i]->getID() == id)
                break;
        }
        return (given == Expression::ExpressionType::Integer && declarations[i]->getArgType(i) == Token::Type::Integer ||
        given == Expression::ExpressionType::Boolean && declarations[i]->getArgType(i) == Token::Type::Boolean);

    }

    unsigned int Body::pushStack(std::vector<std::pair<std::string, std::shared_ptr<Expression> > > temp_args, std::string fid)
    {
        stack.push_back(std::move(StackFunction(temp_args, fid, ++highWaterMark)));
        return highWaterMark;
    }

    void Body::popStack()
    {
        Body::stack.pop_back();
        Body::highWaterMark--;
    }

    unsigned int Body::getHWM()
    {
        return Body::highWaterMark;
    }


    std::unique_ptr<Definition> Body::getDef(std::string did)
    {
        for(int i=0; i < definitions.size(); i++)
        {
            if(definitions[i]->getID() == did)
                return std::move(definitions[i]);
        }
    }

    std::vector<std::string > Definition::getArgs()
    {
        return args;
    }

    Body& Body::getInstance()
    {
        if(!body)
            body = new Body();
        return *body;
    }

    Body& Body::init(std::vector<std::unique_ptr<Declaration>> dec, std::vector<std::unique_ptr<Definition>> def)
    {
        if(body)
            delete body;

        body = new Body(std::move(dec), std::move(def));
        return *body;
    }
}