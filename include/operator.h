//
// Created by tomasz on 12.05.16.
//

#ifndef NAZKELL_OPERATOR_H
#define NAZKELL_OPERATOR_H

#include <iostream>
#include <string>
namespace nazkell
{
        enum class Operator
        {
            Plus,
            Minus,
            Power,
            Multiply,
            Devide,
            Or,
            And,
            Not,
            Greater,
            Less,
            Equal,
            NotEqual,
            EqOrGreater,
            EqOrLess,
            Assign
        };

    //std::string toString(Operator o);
    const std::string toString(Operator o);
    inline std::ostream& operator<<(std::ostream& out, Operator o) { return out << toString(o); }

}

#endif //NAZKELL_OPERATOR_H
