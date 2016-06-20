//
// Created by tomasz on 18.06.16.
//

#ifndef NAZKELL_VALUE_H
#define NAZKELL_VALUE_H
#include <iostream>

namespace nazkell
{
    struct Value
    {
        enum class Type
        {
            Bool,
            Integer,
        };
        Type value_type;
        union
        {
            int i;
            bool b;
        };

        Value()
        {

        }

        Value(int i)
        {
            this->i = i;
            this->value_type = Type::Integer;
        }

        Value(bool b)
        {
            this->b = b;
            this->value_type = Type::Bool;
        }

        Value expectType(Value::Type t)
        {
            if (t != value_type)
                throwValueTypeExeption(t);
            return *this;
        }

        bool operator==(const Value& v)
        {
            if(value_type == Type::Bool)
                return b == v.b;
            else
                return i == v.i;
        }
        bool operator!=(const Value& v)
        {
            return !(*this == v);
        }

        void throwValueTypeExeption(Value::Type t);
    };

    inline std::string toString(Value::Type t)
    {
        switch (t)
        {
            case Value::Type::Integer:
                return "Integer";
            case Value::Type::Bool:
                return "Bool";
        }
    }

    inline void Value::throwValueTypeExeption(Value::Type t)
    {
        const std::string msg = "Wrong type, expression expects " + toString(t) + ", got " + toString(value_type);
        throw std::runtime_error(msg);
    }
}
#endif //NAZKELL_VALUE_H
