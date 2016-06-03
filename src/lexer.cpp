//
// Created by tomasz on 12.05.16.
//
#include <stdexcept>
#include <lexer.h>
namespace nazkell {
    Lexer::Lexer(std::istream &in_)
            : in(in_) {
    }

    Token Lexer::getToken() const {
        return token;
    }

    void Lexer::readNextToken() {
        ignoreWhitespaces();
        if (tryEof())
            return;
        throwOnStreamError();
        if(tryNewLine())
            return;
        std::string input;
        if (tryOperatorOrSymbol())
            return;
        else if(tryInteger())
            return;
        else
        {
            input = readStringOfLetters();
            if (tryBoolean(input) || tryReservedID(input)
                || tryIdentificator(input))
                return;
        }

        throwUnknownToken();
    }

    std::string Lexer::readStringOfDigits()
    {
        std::string buf;
        while (in && std::isdigit(in.peek()))
            buf += static_cast<char>(in.get());
        return buf;
    }

    std::string Lexer::readStringOfLetters()
    {
        std::string buf;
        if(in && (std::islower(in.peek()) || std::isupper(in.peek())))
            do
                buf += static_cast<char>(in.get());
            while (in && (std::isdigit(in.peek()) || std::isupper(in.peek()) || std::islower(in.peek())));

        return buf;
    }

    bool Lexer::tryEof() {
        if (!in.eof())
            return false;
        token = Token();
        return true;
    }

    void Lexer::ignoreWhitespaces() {
        while (!in.eof() && std::isspace(in.peek()) && in.peek() != 0x0a)
            in.get();

    }

    void Lexer::throwOnStreamError() {
        if (!in)
            throw std::runtime_error("Error while reading from input");

    }

    void Lexer::throwUnknownToken() {
        const std::string msg = "Unknown token, starting with: ";
        throw std::runtime_error(msg + static_cast<char>(in.get()));
    }

    bool Lexer::tryBoolean(const std::string& in)
    {

        if(in == "True")
        {
            token = Token(true);
            return true;
        }
        else if(in == "False")
        {
            token = Token(false);
            return true;
        }
        return false;
    }

    bool Lexer::tryOperatorOrSymbol()
    {

        switch(in.peek())
        {
            case '+':
                in.get();
                token = Operator::Plus;
                return true;
            case '-':
                if(in.get() && in.peek()=='>')
                {
                    in.get();
                    token = Symbol::Right;
                }
                else
                token = Operator::Minus;
                return true;
            case '*':
                if(in.get() && in.peek()=='*')
                {
                    in.get();
                    token = Operator::Power;
                }
                else
                    token = Operator::Multiply;
                return true;
            case '/':
                in.get();
                token = Operator::Devide;
                return true;
            case '|':
                in.get();
                token = Operator::Or;
                return true;
            case '&':
                in.get();
                token = Operator::And;
                return true;
            case '!':
                if (in.get() &&  in.peek() == '=')
                {
                    in.get();
                    token = Operator::Not;
                }
                else
                    token = Operator::NotEqual;
                return true;
            case '>':
                if(in.get() && in.peek()=='=')
                {
                    in.get();
                    token = Operator::EqOrGreater;
                }
                else
                    token = Operator::Greater;
                return true;
            case '<':
                if(in.get() && in.peek() == '=')
                {
                    in.get();
                    token = Operator::EqOrLess;
                }
                else if(in.peek() == '-')
                {
                    in.get();
                    token = Symbol::Left;
                }
                else
                    token = Operator::Less;
                return true;
            case '=':
                if(in.get() && in.peek()=='=')
                {
                    in.get();
                    token = Operator::Equal;
                }
                else
                    token = Operator::Assign;
                return true;
            case '.':
                if(in.get() && in.peek()=='.')
                {
                    in.get();
                    token = Symbol::DoubleDot;
                    return true;
                }
                return false;
            case ':':
                if(in.get() && in.peek()==':')
                {
                    in.get();
                    token = Symbol::Colon;
                    return true;
                }
                return false;
            case '(':
                in.get();
                token = Symbol::BracketOpen ;
                return true;
            case ')':
                in.get();
                token = Symbol::BracketClose;
                return true;
            case '[':
                in.get();
                token = Symbol::SBracketOpen;
                return true;
            case ']':
                in.get();
                token = Symbol::SBracketClose;
                return true;
            case ',':
                in.get();
                token = Symbol::Comma;
                return true;

            default:
                return false;
        }

    }

    bool Lexer::tryIdentificator(const std::string& in)
    {
            token = Token(in);
            return true;
    }

    bool Lexer::tryReservedID(const std::string& in)
    {
        if(in == "if")
        {
            token = ReservedID::If;
            return true;
        }
        else if(in == "else")
        {
            token = ReservedID::Else;
            return true;
        }
        else if(in == "then")
        {
            token = ReservedID::Then;
            return true;
        }else if(in == "fi")
        {
            token = ReservedID::Fi;
            return true;
        }else if(in == "bool")
        {
            token = ReservedID::Bool;
            return true;
        }else if(in == "int")
        {
            token = ReservedID::Int;
            return true;
        }
        return false;
    }

    bool Lexer::tryInteger()
    {
        const auto buf = readStringOfDigits();
        if (buf.empty())
            return false;
        token = Token(std::stoi(buf));
        return true;
    }
    bool Lexer::tryNewLine()
    {
        if(in.peek() == 0x0a)
        {
            in.get();
            token = Symbol::NewLine;
            return true;
        }
        return false;
    }
}