//
// Created by tomasz on 12.05.16.
//

#ifndef NAZKELL_SYMBOL_H
#define NAZKELL_SYMBOL_H

#include <iostream>
#include <string>

namespace nazkell
{
    enum class Symbol
    {
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
    };

    std::string toString(Symbol o);
    inline std::ostream& operator<<(std::ostream& out, Symbol o) { return out << toString(o); }

}

#endif //NAZKELL_SYMBOL_H
