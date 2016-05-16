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
            Symbol,
            Operator,
            Bool,
            Int,
            ReservedID,
            Identificator,
            FIdentificator,

        };
        Token();
        Token(bool);
        Token(int);
        Token(Operator o);
        Token(ReservedID);
        Token(Symbol);
        Token(Identificator);
        Token(FIdentificator);

        Type getType() const { return type; }
        int getInteger() const { return value.integer; }
        bool getBoolean() const { return value.boolean; }
        Operator getOperator() const { return value.op; }
        Symbol getSymbol() const { return value.sym; }
        ReservedID getReserverdID() const { return value.rid; }
        const char* getIdentificator() const { return value.id;}
        const char* getFIdentificator() const { return value.fid;}

        std::string toString();
        static std::string toString(Token::Type type);
    private:
        std::string valueToString() const;

        Type type;
        union
        {
            int integer;
            bool boolean;
            Symbol sym;
            Operator op;
            ReservedID rid;
            const char* id;
            const char* fid;
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
