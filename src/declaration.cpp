//
// Created by tomasz on 03.06.16.
//

#include <declaration.h>
#include <sstream>

namespace nazkell
{


        Declaration::Declaration(std::string id, std::vector<Token::Type > args_type):
                id_(id), args_type_(args_type){}
        Declaration::Declaration(std::string id): id_(id) {}
        std::string Declaration::getArgType(int)
        {

        }
        std::string Declaration::getID()
        {

        }
        std::string Declaration::getRetType()
        {

        }

        std::string Declaration::toString()
        {
            std::ostringstream s;
            for( int i = 0 ; i < args_type_.size(); i++)
            {
                if(i < args_type_.size() - 1)
                    s << toString(args_type_[i]) << "->";
                else
                    s << toString(args_type_[i]) << std::endl;
            }
            return id_ + "::" + s.str();
        }

}
