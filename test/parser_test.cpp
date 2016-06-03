//
// Created by tomasz on 01.06.16.
//
#include <parser.h>
#include <fstream>

int main()
{
    std::fstream in;
    nazkell::Lexer l(in);
    nazkell::Parser p(l);
    p.parse();

    return 0;
}