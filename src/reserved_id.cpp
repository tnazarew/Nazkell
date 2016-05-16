//
// Created by tomasz on 12.05.16.
//

#include <reserved_id.h>

std::string nazkell::toString(ReservedID rid)
{
    switch(rid)
    {
        case ReservedID::IF:
            return "if";
        case ReservedID::Then:
            return "then";
        case ReservedID::Else:
            return "else";
        case ReservedID::Bool:
            return "bool";
        case ReservedID::Int:
            return "int";

    }
}