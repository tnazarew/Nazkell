//
// Created by tomasz on 03.06.16.
//

#include <declaration.h>
#include <sstream>

namespace nazkell
{


        Declaration::Declaration(const std::string& id, const std::vector<Token::Type >& args_type):
                id_(id), args_type_(args_type){}
        Declaration::Declaration(const std::string& id): id_(id) {}
        Token::Type Declaration::getArgType(int i)
        {
            return args_type_[i];
        }
        std::string Declaration::getID()
        {
            return id_;
        }
        Token::Type Declaration::getRetType()
        {
            return args_type_[args_type_.size()-1];

        }

        std::string Declaration::toString()
        {
            std::ostringstream s;
            for( int i = 0 ; i < args_type_.size(); i++)
            {
                if(i < args_type_.size() - 1)
                    s << Token::toString(args_type_[i]) << "->";
                else
                    s << args_type_[i];
            }
            return id_ + "::" + s.str();
        }

}
