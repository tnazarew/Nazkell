//
// Created by tomasz on 12.05.16.
//

#include <symbol.h>

std::string nazkell::toString(Symbol s)
{
    switch(s)
    {
        case Symbol::BracketOpen:
            return "(";
        case Symbol::BracketClose:
            return ")";
        case Symbol::SBracketOpen:
            return "[";
        case Symbol::SBracketClose:
            return "]";
        case Symbol::Comma:
            return ",";
        case Symbol::Right:
            return "->";
        case Symbol::Left:
            return "<-";
        case Symbol::DoubleDot:
            return "..";
        case Symbol::Colon:
            return "::";
        case Symbol::NewLine:
            return "newline";

    }
}