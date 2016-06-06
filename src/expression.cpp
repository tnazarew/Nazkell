//
// Created by tomasz on 30.05.16.
//

#include <stdexcept>
#include <expression.h>
namespace nazkell
{
    std::string toString(Expression::ExpressionType t)
    {
        switch(t)
        {
            case Expression::ExpressionType::Boolean:
                return "Boolean";
            case Expression::ExpressionType::Integer:
                return "Integer";
            case Expression::ExpressionType::SimpleList:
                return "";
            case Expression::ExpressionType::ComprehensionList:
                return "";
            case Expression::ExpressionType::RangeList:
                return "";
            case Expression::ExpressionType::If:
                return "If";
            case Expression::ExpressionType::Operator:
                return "Operator";
            case Expression::ExpressionType::Id:
                return "Id";
            case Expression::ExpressionType::Fid:
                return "Fid";
        }
    }

    void Expression::throwWrongType(Expression::ExpressionType et) const
    {
        throw std::runtime_error("Wrong type:" + nazkell::toString(getType()) +
                                                 " required: " + nazkell::toString(et));
    }
}
