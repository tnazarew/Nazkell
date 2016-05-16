//
// Created by tomasz on 12.05.16.
//


#include <string>
#include <token.h>


namespace nazkell
{


    Token::Token()
    : type(Type::Eof)
    {

    }
    Token::Token(bool b)
    : type(Type::Bool)
    {
        value.boolean = b;
    }
    Token::Token(int i)
    : type(Type::Int)
    {
        value.integer = i;
    }
    Token::Token(nazkell::Operator o)
    : type(Type::Operator)
    {
        value.op = o;
    }
    Token::Token(nazkell::ReservedID rid)
    : type(Type::ReservedID)
    {
        value.rid = rid;
    }
    Token::Token(nazkell::Symbol s)
    : type(Type::Symbol)
    {
        value.sym = s;
    }

    Token::Token(nazkell::Identificator id)
    : type(Type::Identificator)
    {
        value.id = id.getID();
    }
    Token::Token(nazkell::FIdentificator fid)
    : type(Type::FIdentificator)
    {
        value.fid = fid.getFID();
    }


    std::string Token::toString(Token::Type type)
    {
        switch(type)
        {
            case Token::Type::Eof:
                return "end of input";
            case Token::Type::Symbol:
                return "symbol";
            case Token::Type::Operator:
                return "operator";
            case Token::Type::Bool:
                return "boolean";
            case Token::Type::Int:
                return "integer";
            case Token::Type::ReservedID:
                return "reserved id";
            case Token::Type::Identificator:
                return "identificator";
            case Token::Type::FIdentificator:
                return "fidentificator";

        }
    }


    std::string Token::valueToString() const
    {
        switch(type)
        {
            case Token::Type::Symbol:
                return "(" + nazkell::toString(getSymbol()) + ")";
            case Token::Type::Operator:
                return "(" + nazkell::toString(getOperator()) + ")";
            case Token::Type::Bool:
                return "(" + std::to_string(getBoolean()) + ")";
            case Token::Type::Int:
                return "(" + std::to_string(getInteger()) + ")";
            case Token::Type::ReservedID:
                return "(" + nazkell::toString(getReserverdID()) + ")";
            case Token::Type::Identificator:
                return "(" + std::string(getIdentificator()) + ")";
            case Token::Type::FIdentificator:
                return "(" + std::string(getFIdentificator()) + ")";
            default:
                return std::string();
        }
    }

    std::string Token::toString()
    {
        return toString(type) + " " + valueToString();
    }


}