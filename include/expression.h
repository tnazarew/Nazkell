//
// Created by tomasz on 30.05.16.
//

#ifndef NAZKELL_EXPRESSION_H
#define NAZKELL_EXPRESSION_H
#include <bits/stringfwd.h>
#include <memory>
namespace nazkell
{
    class Expression
    {
    public:
        enum class ExpressionType
        {
            Boolean,
            Integer,
            SimpleList,
            ComprehensionList,
            RangeList,
            If,
            Operator,
            Id,
            Fid
        };

        virtual ~Expression()
        {

        }
        void throwWrongType(ExpressionType) const;
        virtual ExpressionType getType() const = 0;
        virtual int evaluateInt(unsigned int) const = 0;
        virtual bool evaluateBool(unsigned int) const = 0;
        virtual std::string toString() const = 0;
    };
}
#endif //NAZKELL_EXPRESSION_H
