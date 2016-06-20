#include <iostream>
#include <lexer.h>
#include <fstream>
#include <expressions.h>
#include <body.h>
#include <parser.h>


int main(int argc, char** argv)
{

    if(argc > 1)
    {
        std::fstream fs;
        fs.open(argv[1], std::fstream::in);
        std::unique_ptr<nazkell::Lexer> l(new nazkell::Lexer(fs));
        nazkell::Parser p(std::move(l));
        std::unique_ptr<nazkell::Body> body;
        body.reset(p.parse());
        std::vector<std::shared_ptr<nazkell::Expression>> v;
        for(int i = 2; i < argc; i++)
        {
            if(std::string(argv[i]) == "true" || std::string(argv[i]) == "false")
                v.push_back(std::shared_ptr<nazkell::Expression>(new nazkell::BooleanExpression(std::string(argv[i]) == "true")));
            else
                v.push_back(std::shared_ptr<nazkell::Expression>(new nazkell::IntegerExpression(atoi(argv[i]))));

        }

        std::cout << body->evaluate(v, "Main").i << std::endl;

        fs.close();
    }
    else
        std::cout << "no input, executing..." << std::endl;
}