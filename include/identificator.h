//
// Created by tomasz on 12.05.16.
//

#ifndef NAZKELL_IDENT_H
#define NAZKELL_IDENT_H

#include <iostream>
#include <string>

namespace nazkell
{
    class Id
    {
        const char* id;

    public:
        Id(){id = 0;}
        Id(std::string s): id(s.c_str()){}
        const char* getID();
    };



    inline std::ostream& operator<<(std::ostream& out, Id i) { return out << i.getID(); }

}

#endif //NAZKELL_IDENT_H
