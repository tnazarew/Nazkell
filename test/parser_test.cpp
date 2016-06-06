//
// Created by tomasz on 01.06.16.
//
#include <parser.h>
#include <fstream>

int main()
{
    std::fstream fs;
    fs.open("/home/tomasz/ClionProjects/Nazkell/test/testfile.nz", std::fstream::in);
    std::unique_ptr<nazkell::Lexer> l(new nazkell::Lexer(fs));
    nazkell::Parser p(std::move(l));
    auto body (p.parse());
    std::cout << "PARSED STRUCTURES" << std::endl;
    std::cout << body->toString();
//    fs.close();
    return 0;
}