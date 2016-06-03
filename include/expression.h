//
// Created by tomasz on 30.05.16.
//

#ifndef NAZKELL_EXPRESSION_H
#define NAZKELL_EXPRESSION_H
#include <bits/stringfwd.h>
namespace nazkell
{
    class Expression
    {
    public:
        enum class ExpressionType
        {
            Boolean,
            Integer,
            List,
            If,
            Operator,
            Id,
            Fid
        };

        virtual ~Expression()
        {

        }
        virtual ExpressionType getType() const = 0;
        virtual int getValue() const = 0;
        virtual std::string toString() const = 0;
    };
}
#endif //NAZKELL_EXPRESSION_H
