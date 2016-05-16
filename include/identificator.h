//
// Created by tomasz on 12.05.16.
//

#ifndef NAZKELL_IDENT_H
#define NAZKELL_IDENT_H

#include <iostream>
#include <string>

namespace nazkell
{
    class Identificator
    {
        const char* id;

    public:
        Identificator(){id = 0;}
        Identificator(std::string s): id(s.c_str()){}
        const char* getID();
    };



    inline std::ostream& operator<<(std::ostream& out, Identificator i) { return out << i.getID(); }

}

#endif //NAZKELL_IDENT_H
