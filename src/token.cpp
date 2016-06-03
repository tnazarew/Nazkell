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
                type = Type::Operator4;
                break;
            case Operator::And:
                type = Type::Operator4;
                break;
            case Operator::Not:
                type = Type::Not;
                break;
            case Operator::Greater:
                type = Type::Operator5;
                break;
            case Operator::Less:
                type = Type::Operator5;
                break;
            case Operator::Equal:
                type = Type::Operator5;
                break;
            case Operator::EqOrGreater:
                type = Type::Operator5;
                break;
            case Operator::EqOrLess:
                type = Type::Operator5;
                break;
            case Operator::Assign:
                type = Type::Operator4;
                break;
            case Operator::NotEqual:
                type = Type::Operator5;
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
            case ReservedID::Then:
                type = Type::Then;
                break;
            case ReservedID::Else:
                type = Type::Else;
                break;
            case ReservedID::Fi:
                type = Type::Fi;
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
            case Symbol::SBracketOpen:
                type = Type::SBracketOpen;
                break;
            case Symbol::SBracketClose:
                type = Type::SBracketClose;
                break;
            case Symbol::Comma:
                type = Type::Comma;
                break;
            case Symbol::Right:
                type = Type::Right;
                break;
            case Symbol::Left:
                type = Type::Left;
                break;
            case Symbol::DoubleDot:
                type = Type::DoubleDot;
                break;
            case Symbol::Colon:
                type = Type::Colon;
                break;
            case Symbol::NewLine:
                type = Type::NewLine;
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
            case Token::Type::SBracketOpen:
                return "SBracketOpen";
            case Token::Type::SBracketClose:
                return "SBracketClose";
            case Token::Type::Comma:
                return "Comma";
            case Token::Type::Right:
                return "Right";
            case Token::Type::Left:
                return "Left";
            case Token::Type::DoubleDot:
                return "DoubleDot";
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
            case Token::Type::Operator6:
                return "operator6";
            case Token::Type::Boolean:
                return "boolean";
            case Token::Type::Integer:
                return "integer";
            case Token::Type::Bool:
                return "Bool";
            case Token::Type::Int:
                return "Int";
            case Token::Type::If:
                return "If";
            case Token::Type::Then:
                return "Then";
            case Token::Type::Else:
                return "Else";
            case Token::Type::Fi:
                return "Fi";
            case Token::Type::Id:
                return "Id";
            case Token::Type::Fid:
                return "Fid";

        }
    }


    std::string Token::valueToString() const
    {
        if(type == Type::BracketOpen    || type == Type::BracketClose   ||
           type == Type::SBracketOpen   || type == Type::SBracketClose  ||
           type == Type::Comma          || type == Type::Right          ||
           type == Type::Left           || type == Type::DoubleDot      ||
           type == Type::Colon          || type == Type::NewLine
        )
            return "(" + nazkell::toString(getSymbol()) + ")";
        else if(type == Type::Operator1  || type == Type::Operator2   ||
                type == Type::Operator3  || type == Type::Operator4   ||
                type == Type::Operator5  || type == Type::Operator6
                )
            return "(" + nazkell::toString(getOperator()) + ")";
        else if(type == Type::Bool || type == Type::Int || type == Type::If ||
                type == Type::Then || type == Type::Else || type == Type::Fi
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