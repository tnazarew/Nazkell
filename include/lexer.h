//
// Created by tomasz on 11.05.16.
//

#ifndef NAZKELL_LEXER_H
#define NAZKELL_LEXER_H

#include <iostream>
#include <string>
#include <token.h>

namespace nazkell
{
    class Lexer
    {
    public:
        Lexer(std::istream& in);

        Lexer(const Lexer&) = delete;
        const Lexer& operator=(const Lexer&) = delete;

        void readNextToken();
        Token getToken() const;

    private:
        bool tryEof();
        bool tryInteger();
        bool tryBoolean(const std::string&);
        bool tryOperatorOrSymbol();
        bool tryReservedID(const std::string&);
        bool tryIdentificator(const std::string&);
        bool tryFIdentificator(const std::string&);

        void ignoreWhitespaces();
        void throwUnknownToken();
        void throwOnStreamError();

        std::string readStringOfDigits();
        std::string readStringOfLetters();
        std::istream& in;
        Token token;
    };
}
#endif //NAZKELL_LEXER_H
