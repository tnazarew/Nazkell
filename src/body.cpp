//
// Created by tomasz on 01.06.16.
//

#include <body.h>
#include <sstream>


namespace nazkell
{

    Body *Body::body = 0;

    std::string Body::toString()
    {
        std::ostringstream out;
        for (auto &i: Body::definitions)
            out << i.second->toString() << std::endl;
        for (auto &i: Body::declarations)
            out << i.second->toString() << std::endl;
        return out.str();
    }

    Body::Body()
    {
        highWaterMark = 0;
    }

    Body::~Body()
    {

    }


    Body::Body(std::map<std::string, std::unique_ptr<Declaration> > dec,
               std::map<std::string, std::shared_ptr<Definition> > def) :
            definitions(def), declarations(std::move(dec))
    {
        highWaterMark = 0;
    }


    Value Body::evaluate(const std::vector<std::shared_ptr<Expression>> &args, std::string fid)
    {
        std::shared_ptr<Definition> d = getDef(fid);
        std::vector<std::pair<std::string, std::shared_ptr<Expression>>> temp_args;
        for (int i = 0; i < args.size(); i++)
        {
            temp_args.push_back(std::make_pair(d->getArgs()[i], args[i]));
        }
        unsigned new_stack_id = pushStack(temp_args, fid);
        Value res = d->evaluate(new_stack_id);
        popStack();
        return res;
    }


    Value Body::evaluate(unsigned int stackID, const std::string &argID)
    {
        for (int i = 0; i < stack[stackID].functions.size(); i++)
        {
            if (stack[stackID].functions[i].first == argID)
            {
                if(declarations.find(stack[stackID].name) != declarations.end())
                {
                    if (declarations[stack[stackID].name]->getArgType(i) == Token::Type::Bool)
                        return stack[stackID].functions[i].second->evaluate(stack[stackID].parent_stack_id).expectType(
                                Value::Type::Bool);
                    if (declarations[stack[stackID].name]->getArgType(i) == Token::Type::Int)
                        return stack[stackID].functions[i].second->evaluate(stack[stackID].parent_stack_id).expectType(
                                Value::Type::Integer);
                }
                else
                    throwFunctionNotDeclared(stack[stackID].name);
            }
        }
    }


    unsigned int Body::pushStack(const std::vector<std::pair<std::string, std::shared_ptr<Expression>>>& temp_args,
                                 const std::string& fid)
    {
        stack.push_back(StackFunction(temp_args, fid, highWaterMark));
        return (fid == "Main") ? highWaterMark : ++highWaterMark;
    }

    void Body::popStack()
    {
        Body::stack.pop_back();
        Body::highWaterMark--;
    }


    std::shared_ptr<Definition> Body::getDef(const std::string& did)
    {
        return definitions[did];
    }

    std::vector<std::string> Definition::getArgs()
    {
        return args;
    }

    Body &Body::getInstance()
    {
        if (!body)
            body = new Body();
        return *body;
    }

    Body &Body::init(std::map<std::string, std::unique_ptr<Declaration>> dec,
                     std::map<std::string, std::shared_ptr<Definition>> def)
    {
//        if(body)
//            delete body;

        body = new Body(std::move(dec), def);
        return *body;
    }

    void Body::throwFunctionNotDeclared(const std::string& s)
    {
        throw std::runtime_error("Requested declaration: " + s + "does not exist");
    }

    void Body::resetStack()
    {
        stack.clear();
        highWaterMark = 0;
    }
}