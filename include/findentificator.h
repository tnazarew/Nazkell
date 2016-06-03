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
    class Fid
    {
        const char* fid;
    public:
        Fid(){fid = 0;}
        Fid(std::string s): fid(s.c_str()){}
        const char* getFID();
    };

//    std::string toString(const  i);
    inline std::ostream& operator<<(std::ostream& out, Fid i) { return out << i.getFID(); }

}


#endif //NAZKELL_FINDENTIFICATOR_H
