//
// Created by tomasz on 29.05.16.
//

#ifndef NAZKELL_PARSER_H
#define NAZKELL_PARSER_H

#include <bits/unique_ptr.h>
#include <lexer.h>
#include <declaration.h>
#include <definition.h>
#include <expression.h>
#include <value_type.h>
#include <literal.h>
#include <body.h>

namespace nazkell
{
    class Parser
    {

    public:
        Parser(Lexer lexer);
        ~Parser();

        std::unique_ptr<Body> parse();

    private:
        std::unique_ptr<Body> readBody();
        std::unique_ptr<Declaration> readDeclaration(std::string);
        std::unique_ptr<Definition> readDefinition(std::string);
        std::unique_ptr<Expression> readExpression();
        std::unique_ptr<Expression> readSingleExpression();
        std::unique_ptr<Expression> readBinaryExpression(std::unique_ptr<Expression>& left);
        std::unique_ptr<ValueType> readValueType();
        std::unique_ptr<Expression> readInteger();
        std::unique_ptr<Expression> readBoolean();
        std::unique_ptr<Expression> readIfStatement();
        std::unique_ptr<Expression> readParenthesesExperssion();
        std::unique_ptr<Expression> readOp1Exp(std::unique_ptr<Expression>);
        std::unique_ptr<Expression> readOp2Exp(std::unique_ptr<Expression>);
        std::unique_ptr<Expression> readOp3Exp(std::unique_ptr<Expression>);
        std::unique_ptr<Expression> readOp4Exp(std::unique_ptr<Expression>);
        std::unique_ptr<Expression> readOp5Exp(std::unique_ptr<Expression>);
        std::unique_ptr<Expression> readOp6Exp(std::unique_ptr<Expression>);
        std::unique_ptr<Expression> readList();
        std::unique_ptr<Expression> readFunction();
        std::unique_ptr<Expression> readVariable();
        std::unique_ptr<Expression> readNegation();
        std::unique_ptr<Expression> readCondition();


        std::unique_ptr<Expression> readBinaryExpression(std::unique_ptr<Expression> leftOper);

        Operator readOperator();

        void throwOnUnexpectedInput(Token::Type expected);
        void throwOnUnexpectedInput(std::vector<Token::Type> expected);
        Token requireToken(Token::Type expected);
        bool checkTokenType(Token::Type expected) const;

        void advance();
        Token::Type getTokenType();
        bool isOperator();
        Lexer lexer;
    };
}
#endif //NAZKELL_PARSER_H
