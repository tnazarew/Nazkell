//
// Created by tomasz on 13.05.16.
//

#ifndef NAZKELL_FINDENTIFICATOR_H
#define NAZKELL_FINDENTIFICATOR_H

#include <iostream>
#include <string>
#include <identificator.h>
namespace nazkell
{
    class FIdentificator
    {
        const char* fid;
    public:
        FIdentificator(){fid = 0;}
        FIdentificator(std::string s): fid(s.c_str()){}
        const char* getFID();
    };

//    std::string toString(const  i);
    inline std::ostream& operator<<(std::ostream& out, FIdentificator i) { return out << i.getFID(); }

}


#endif //NAZKELL_FINDENTIFICATOR_H
