//
// Created by tomasz on 12.05.16.
//

#include <identificator.h>
namespace nazkell
{
    std::string toString(Id id) {
        return std::string(id.getID());
    }

    const char* Id::getID()
    {
        return id;
    }
}