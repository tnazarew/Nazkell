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
    : type(Type::Boolean)
    {
        value.boolean = b;
    }
    Token::Token(int i)
    : type(Type::Integer)
    {
        value.integer = i;
    }
    Token::Token(nazkell::Operator o)
    {
        value.op = o;
        switch(o)
        {
            case Operator::Plus:
                type = Type::Operator3;
                break;
            case Operator::Minus:
                type = Type::Operator3;
                break;
            case Operator::Power:
                type = Type::Operator1;
                break;
            case Operator::Multiply:
                type = Type::Operator2;
                break;
            case Operator::Devide:
                type = Type::Operator2;
                break;
            case Operator::Or:
                type = Type::Operator5;
                break;
            case Operator::And:
                type = Type::Operator5;
                break;
            case Operator::Greater:
                type = Type::Operator4;
                break;
            case Operator::Less:
                type = Type::Operator4;
                break;
            case Operator::Equal:
                type = Type::Operator4;
                break;
            case Operator::EqOrGreater:
                type = Type::Operator4;
                break;
            case Operator::EqOrLess:
                type = Type::Operator4;
                break;
            case Operator::NotEqual:
                type = Type::Operator4;
                break;
        }
    }
    Token::Token(nazkell::ReservedID rid)
    {
        value.rid = rid;
        switch(rid)
        {
            case ReservedID::If:
                type = Type::If;
                break;
            case ReservedID::Else:
                type = Type::Else;
                break;
            case ReservedID::Bool:
                type = Type::Bool;
                break;
            case ReservedID::Int:
                type = Type::Int;
                break;
        }
    }
    Token::Token(nazkell::Symbol s)
    {
        value.sym = s;
        switch(s)
        {
            case Symbol::BracketOpen:
                type = Type::BracketOpen;
                break;
            case Symbol::BracketClose:
                type = Type::BracketClose;
                break;
            case Symbol::Right:
                type = Type::Right;
                break;
            case Symbol::Colon:
                type = Type::Colon;
                break;
            case Symbol::EqSign:
                type = Type::EqSign;
                break;
        }
    }

    Token::Token(std::string id)
    {
        value.id = id;
        if(std::islower(id[0]))
        {
            type = Type::Id;
        }
        else
        {
            type = Type::Fid;
        }
    }



    std::string Token::toString(Token::Type type)
    {
        switch(type)
        {
            case Token::Type::Eof:
                return "end of input";
            case Token::Type::BracketOpen:
                return "BracketOpen";
            case Token::Type::BracketClose:
                return "BracketClose";
            case Token::Type::Right:
                return "Right";
            case Token::Type::Colon:
                return "Colon";
            case Token::Type::NewLine:
                return "NewLine";
            case Token::Type::Operator1:
                return "operator1";
            case Token::Type::Operator2:
                return "operator2";
            case Token::Type::Operator3:
                return "operator3";
            case Token::Type::Operator4:
                return "operator4";
            case Token::Type::Operator5:
                return "operator5";
            case Token::Type::EqSign:
                return "=";
            case Token::Type::Boolean:
                return "boolean";
            case Token::Type::Integer:
                return "integer";
            case Token::Type::Bool:
                return "bool";
            case Token::Type::Int:
                return "int";
            case Token::Type::If:
                return "If";
            case Token::Type::Else:
                return "Else";
            case Token::Type::Id:
                return "Id";
            case Token::Type::Fid:
                return "Fid";

        }
    }


    std::string Token::valueToString() const
    {
        if(type == Type::BracketOpen    || type == Type::BracketClose   ||
           type == Type::Right          || type == Type::Colon          ||
           type == Type::NewLine        || type == Type::EqSign
        )
            return "(" + nazkell::toString(getSymbol()) + ")";
        else if(type == Type::Operator1  || type == Type::Operator2   ||
                type == Type::Operator3  || type == Type::Operator4   ||
                type == Type::Operator5
                )
            return "(" + nazkell::toString(getOperator()) + ")";
        else if(type == Type::Bool || type == Type::Int || type == Type::If ||
                type == Type::Else
                )
            return "(" + nazkell::toString(getReserverdID()) + ")";
        else if(type == Type::Integer)
            return "(" + std::to_string(getInteger()) + ")";
        else if(type == Type::Boolean)
            return "(" + std::to_string(getBoolean()) + ")";
        else if(type == Type::Id || type == Type::Fid)
            return "(" + std::string(getId()) + ")";
        else if(type == Type::Eof)
            return "(end of file)";

    }

    std::string Token::toString()
    {
        return toString(type) + " " + valueToString();
    }


}