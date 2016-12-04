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
        case Symbol::Right:
            return "->";
        case Symbol::EqSign:
            return "=";
        case Symbol::Colon:
            return "::";
    }
}