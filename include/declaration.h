//
// Created by tomasz on 29.05.16.
//

#ifndef NAZKELL_DECLARATION_H
#define NAZKELL_DECLARATION_H
#include <vector>
#include <token.h>
namespace nazkell
{
    class Declaration
    {
        std::string id_;
        std::vector <Token::Type> args_type_;
    public:
        Declaration(const std::string &id, const std::vector<Token::Type >& args_type);
        Declaration(const std::string &id);
        Token::Type getArgType(int);
        std::string getID();
        Token::Type getRetType();
        std::string toString();

    };
}
#endif //NAZKELL_DECLARATION_H
