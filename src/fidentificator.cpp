//
// Created by tomasz on 13.05.16.
//

#include <findentificator.h>

namespace nazkell
{
    const char* FIdentificator::getFID()
    {
        return fid;
    }

    std::string toString(FIdentificator fid)
    {
        return std::string(fid.getFID());
    }
}