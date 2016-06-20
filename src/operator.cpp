//
// Created by tomasz on 12.05.16.
//

#include <operator.h>

const std::string nazkell::toString(Operator o)
{
    switch(o)
    {

        case Operator::Plus:
            return "+";
        case Operator::Minus:
            return "-";
        case Operator::Power:
            return "**";
        case Operator::Multiply:
            return "*";
        case Operator::Devide:
            return "/";
        case Operator::Or:
            return "|";
        case Operator::And:
            return "&";
        case Operator::Greater:
            return ">";
        case Operator::Less:
            return "<";
        case Operator::Equal:
            return "==";
        case Operator::EqOrGreater:
            return ">=";
        case Operator::EqOrLess:
            return "<=";
        case Operator::NotEqual:
            return "!=";
    }
}
