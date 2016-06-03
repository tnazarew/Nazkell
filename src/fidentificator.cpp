//
// Created by tomasz on 13.05.16.
//

#include <findentificator.h>

namespace nazkell
{
    const char* Fid::getFID()
    {
        return fid;
    }

    std::string toString(Fid fid)
    {
        return std::string(fid.getFID());
    }
}