#include <iostream>
#include <lexer.h>
#include <fstream>


void readInput(nazkell::Lexer& l)
{
    do
    {
        l.readNextToken();
        std::cout << l.getToken() << std::endl;
    }while (l.getToken().getType() != nazkell::Token::Type::Eof);
}

int main(int argc, char** argv)
{

    if(argc > 1)
    {
        std::fstream fs;
        fs.open(argv[1], std::fstream::in);
        nazkell::Lexer l(fs);
        readInput(l);
    }
    else
    {
        nazkell::Lexer l(std::cin);
        readInput(l);
    }
}