//
// Created by tomasz on 02.06.16.
//

#ifndef NAZKELL_EXPRESSIONS_H
#define NAZKELL_EXPRESSIONS_H


#include <memory>
#include <operator.h>
#include <vector>
#include <expression.h>
namespace nazkell
{
    class BooleanExpression : public Expression
    {
        ExpressionType getType() const override;

        Value evaluate(unsigned int) const override;

        std::string toString() const override;
        Value value;
    public:
        BooleanExpression(bool);
        ~BooleanExpression();
    };
    class IntegerExpression : public Expression
    {
        ExpressionType getType() const override;

        Value evaluate(unsigned int) const override;
        std::string toString() const override;
        Value value;
    public:
        IntegerExpression(int);
        ~IntegerExpression();
    };
    class ListExpression : public Expression
    {

    };
    class IfExpression : public Expression
    {
        std::unique_ptr<Expression> cond, ifexp, elseexp;
        ExpressionType getType() const override;

        Value evaluate(unsigned int) const override;
        std::string toString() const override;
    public:
        IfExpression(std::unique_ptr<Expression> cond_,
                     std::unique_ptr<Expression> ifexp_,
                     std::unique_ptr<Expression> elseexp_);
        ~IfExpression();
    };
    class VariableExpression : public Expression
    {
        std::string id;
        ExpressionType getType() const override;

        Value evaluate(unsigned int) const override;
        std::string toString() const override;
    public:
        std::string getID() const ;
        VariableExpression(std::string id_);
        ~VariableExpression();
    };
    class FunctionExpression : public Expression
    {
        std::string id;
        std::vector<std::shared_ptr<Expression> > arguments;
        ExpressionType getType() const override;

        Value evaluate(unsigned int) const override;
        std::string toString() const override;
    public:
        FunctionExpression(std::string id_, std::vector<std::shared_ptr<Expression> > arguments_);
        ~FunctionExpression();
    };
    class OperatorExpression : public Expression
    {
        Operator op;
        std::unique_ptr<Expression> left, right;
        ExpressionType getType() const override;

        Value evaluate(unsigned int) const override;
        std::string toString() const override;
        Value power(const Value, const Value) const;
    public:
        OperatorExpression(std::unique_ptr<Expression> l, Operator o, std::unique_ptr<Expression> r);
        ~OperatorExpression();
    };
    class SimpleList: public Expression
    {

        ExpressionType getType() const override;

        Value evaluate(unsigned int) const override;
        std::string toString() const override;
    public:
        SimpleList();
        ~SimpleList();
    };

    class ComprehensionList:public Expression
    {

        ExpressionType getType() const override;

        Value evaluate(unsigned int) const override;
        std::string toString() const override;

    public:
        ComprehensionList();
        ~ComprehensionList();
    };

    class RangeList:public Expression
    {

        ExpressionType getType() const override;

        Value evaluate(unsigned int) const override;
        std::string toString() const override;

    public:
        RangeList();
        ~RangeList();

    };

}
#endif //NAZKELL_EXPRESSIONS_H
