//
// Created by tomasz on 12.05.16.
//

#ifndef NAZKELL_RESERVED_ID_H
#define NAZKELL_RESERVED_ID_H

#include <string>
#include <iostream>

namespace nazkell
{
    enum class ReservedID
    {
        If,
        Else,
        Bool,
        Int,
    };


    std::string toString(ReservedID o);
    inline std::ostream& operator<<(std::ostream& out, ReservedID o) { return out << toString(o); }

}

#endif //NAZKELL_RESERVED_ID_H
