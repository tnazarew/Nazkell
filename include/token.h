//
// Created by tomasz on 11.05.16.
//

#ifndef NAZKELL_TOKEN_H
#define NAZKELL_TOKEN_H

#include <operator.h>
#include <reserved_id.h>
#include <symbol.h>
#include <identificator.h>
#include <findentificator.h>


namespace nazkell
{
    class Token
    {
    public:
        enum class Type
        {
            Eof,
            BracketOpen,
            BracketClose,
            SBracketOpen,
            SBracketClose,
            Comma,
            Right,
            Left,
            DoubleDot,
            Colon,
            NewLine,
            Operator1,
            Operator2,
            Operator3,
            Operator4,
            Operator5,
            Operator6,
            Not,
            Bool,
            Int,
            If,
            Then,
            Else,
            Fi,
            Boolean,
            Integer,
            Id,
            Fid,

        };
        Token();
        Token(bool);
        Token(int);
        Token(Operator o);
        Token(ReservedID);
        Token(Symbol);
        Token(std::string);

        Type getType() const { return type; }
        int getInteger() const { return value.integer; }
        bool getBoolean() const { return value.boolean; }
        Operator getOperator() const { return value.op; }
        Symbol getSymbol() const { return value.sym; }
        ReservedID getReserverdID() const { return value.rid; }
        std::string getId() const { return value.id;}

        std::string toString();
        static std::string toString(Token::Type type);
    private:
        std::string valueToString() const;

        Type type;
        struct
        {
            int integer;
            bool boolean;
            Symbol sym;
            Operator op;
            ReservedID rid;
            std::string id;
        } value;

    };

    inline std::ostream& operator<<(std::ostream& o, Token::Type type)
    {
        return o << Token::toString(type);
    }

    inline std::ostream& operator<<(std::ostream& o, Token t)
    {
        return o << t.toString();
    }
}

#endif //NAZKELL_TOKEN_H
