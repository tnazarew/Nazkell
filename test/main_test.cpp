//
// Created by tomasz on 16.06.16.
//

#include <iostream>
#include <parser.h>
#include <fstream>
#include <expressions.h>

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
        v.push_back(std::shared_ptr<nazkell::Expression>(new nazkell::IntegerExpression(atoi(argv[2]))));
        std::cout << body->evaluate(v, "Main").i << std::endl;

        fs.close();
    }
}