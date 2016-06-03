#include <lexer.h>
#include <fstream>
#include <sstream>

void readInput(nazkell::Lexer& l)
{
    do
    {
        l.readNextToken();
        std::cout << l.getToken() << std::endl;
    }while (l.getToken().getType() != nazkell::Token::Type::Eof);
}

void printTest()
{
    std::fstream fs;
    fs.open("../test/testfile.nz", std::fstream::in);
    nazkell::Lexer l(fs);
    readInput(l);
}

void tryAllTest()
{
//    std::istringstream in("<= ] 123 True Test test if");
//    nazkell::Lexer l(in);
//
//    l.readNextToken();
//    if(l.getToken().getType() != nazkell::Token::Type::Operator)
//        perror(("INVALID TYPE " + l.getToken().toString(l.getToken().getType()) + " INSTEAD OF " + l.getToken().toString(nazkell::Token::Type::Operator)).c_str());
//    l.readNextToken();
//    if(l.getToken().getType() != nazkell::Token::Type::Symbol)
//        perror(("INVALID TYPE " + l.getToken().toString(l.getToken().getType()) + " INSTEAD OF " + l.getToken().toString(nazkell::Token::Type::Symbol)).c_str());
//    l.readNextToken();
//    if(l.getToken().getType() != nazkell::Token::Type::Int)
//        perror(("INVALID TYPE " + l.getToken().toString(l.getToken().getType()) + " INSTEAD OF " + l.getToken().toString(nazkell::Token::Type::Int)).c_str());
//    l.readNextToken();
//    if(l.getToken().getType() != nazkell::Token::Type::Bool)
//        perror(("INVALID TYPE " + l.getToken().toString(l.getToken().getType()) + " INSTEAD OF " + l.getToken().toString(nazkell::Token::Type::Bool)).c_str());
//    l.readNextToken();
//    if(l.getToken().getType() != nazkell::Token::Type::FIdentificator)
//        perror(("INVALID TYPE " + l.getToken().toString(l.getToken().getType()) + " INSTEAD OF " + l.getToken().toString(nazkell::Token::Type::FIdentificator)).c_str());
//    l.readNextToken();
//    if(l.getToken().getType() != nazkell::Token::Type::Identificator)
//        perror(("INVALID TYPE " + l.getToken().toString(l.getToken().getType()) + " INSTEAD OF " + l.getToken().toString(nazkell::Token::Type::Identificator)).c_str());
//    l.readNextToken();
//    if(l.getToken().getType() != nazkell::Token::Type::ReservedID::IF)
//        perror(("INVALID TYPE " + l.getToken().toString(l.getToken().getType()) + " INSTEAD OF " + l.getToken().toString(nazkell::Token::Type::ReservedID)).c_str());
//    l.readNextToken();
//    if(l.getToken().getType() != nazkell::Token::Type::Eof)
//        perror(("INVALID TYPE " + l.getToken().toString(l.getToken().getType()) + " INSTEAD OF " + l.getToken().toString(nazkell::Token::Type::Eof)).c_str());
//
//    std::cout << "TEST COMPLETED" << std::endl;
}

int main()
{
    printTest();

    tryAllTest();
}