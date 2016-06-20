//
// Created by tomasz on 29.05.16.
//
#include <parser.h>
#include <sstream>
#include <expressions.h>
#include <map>

namespace nazkell
{
    Parser::Parser(std::unique_ptr<Lexer> lexer_)
            : lexer(std::move(lexer_))
    {
    }

    Parser::~Parser()
    {
    }

    Body* Parser::parse()
    {
        return readBody();
    }

    Body* Parser::readBody()
    {
        std::map<std::string, std::unique_ptr<Declaration> > declarations;
        std::map<std::string, std::shared_ptr<Definition> > definitions;
        advance();
        if(lexer->getToken().getType() == Token::Type::Eof)
            throwOnUnexpectedInput(Token::Type::Fid);
        while (lexer->getToken().getType() != Token::Type::Eof)
        {
            if (lexer->getToken().getType() != Token::Type::Fid)
                throwOnUnexpectedInput(Token::Type::Fid);
            std::string id = lexer->getToken().getId();
            advance();
            if (lexer->getToken().getType() == Token::Type::Colon)
            {
                declarations.insert(std::move(std::make_pair(id, std::move(readDeclaration(id)))));
            }
            else if (lexer->getToken().getType() == Token::Type::Id)
            {
                definitions.insert(std::move(std::make_pair(id, std::move(readDefinition(id)))));
            }

        }

        return &Body::init(std::move(declarations), definitions);
    }

    std::unique_ptr<Declaration> Parser::readDeclaration(const std::string& fid)
    {
        std::vector<Token::Type> types;

        advance();
        if (getTokenType() == Token::Type::Bool
            || getTokenType() == Token::Type::Int)
            types.push_back(lexer->getToken().getType());
        else
        {
            std::vector<Token::Type> temp;
            temp.push_back(Token::Type::Bool);
            temp.push_back(Token::Type::Integer);
            throwOnUnexpectedInput(temp);
        }
        advance();
        while (getTokenType() == Token::Type::Right)
        {
            advance();
            if (getTokenType() == Token::Type::Bool
                || getTokenType() == Token::Type::Int)
                types.push_back(lexer->getToken().getType());
            else
            {
                std::vector<Token::Type> temp;
                temp.push_back(Token::Type::Bool);
                temp.push_back(Token::Type::Integer);
                throwOnUnexpectedInput(temp);
            }
            advance();
        }
        return std::move(std::unique_ptr<Declaration>(new Declaration(fid, types)));
    }

    std::shared_ptr<Definition> Parser::readDefinition(const std::string& fid)
    {
        std::vector<std::string> tokens;
        std::unique_ptr<Expression> expression;
        while (getTokenType() != Token::Type::EqSign)
        {
            tokens.push_back(requireToken(Token::Type::Id).getId());
            advance();
        }
        advance();
        expression = (std::move(readExpression()));
        return std::shared_ptr<Definition>(new Definition(fid, tokens, std::move(expression)));
    }

    std::unique_ptr<Expression> Parser::readExpression()
    {
        std::unique_ptr<Expression> exp = readSingleExpression();

        while (isOperator())
        {
            exp = readOp1Exp(std::move(exp));
//            std::cout << exp->toString();
        }
        return std::move(exp);
    }

    std::unique_ptr<Expression> Parser::readSingleExpression()
    {
        switch (getTokenType())
        {
            case Token::Type::Boolean :
                return readBoolean();
            case Token::Type::Integer :
                return readInteger();
            case Token::Type::If :
                return readIfStatement();
            case Token::Type::Id :
                return readVariable();
            case Token::Type::Fid :
                return readFunction();
            case Token::Type::BracketOpen :
                return readParenthesesExperssion();
            default:
                std::vector<Token::Type> v({Token::Type::Boolean, Token::Type::Integer, Token::Type::If,
                                            Token::Type::Id, Token::Type::Fid, Token::Type::BracketOpen});
                throwOnUnexpectedInput(v);
        }

    }

    std::unique_ptr<Expression> Parser::readBoolean()
    {
        std::unique_ptr<Expression> exp(new BooleanExpression(lexer->getToken().getBoolean()));
        advance();
        return exp;
    }

    std::unique_ptr<Expression> Parser::readInteger()
    {
        std::unique_ptr<Expression> exp(new IntegerExpression(lexer->getToken().getInteger()));
        advance();
        return exp;
    }

    std::unique_ptr<Expression> Parser::readIfStatement()
    {
        std::unique_ptr<Expression> ifexp, elseexp, cond;
        advance();

        cond = (std::move(readExpression()));


        ifexp = (std::move(readExpression()));

        if (getTokenType() != Token::Type::Else)
            throwOnUnexpectedInput(Token::Type::Else);
        advance();
        elseexp = (std::move(readExpression()));

        return std::move(
                std::unique_ptr<Expression>(new IfExpression(std::move(cond), std::move(ifexp), std::move(elseexp))));
    }

    std::unique_ptr<Expression> Parser::readParenthesesExperssion()
    {
        advance();
        std::unique_ptr<Expression> exp(readExpression());
        if (getTokenType() != Token::Type::BracketClose)
            throwOnUnexpectedInput(Token::Type::BracketClose);
        advance();
        return exp;
    }


    std::unique_ptr<Expression> Parser::readOp1Exp(std::unique_ptr<Expression> left)
    {
        if (getTokenType() != Token::Type::Operator5)
        {
            return readOp2Exp(std::move(left));
        }
        else
        {
            Operator op = lexer->getToken().getOperator();
            advance();
            std::unique_ptr<Expression> right = readSingleExpression();

            return std::unique_ptr<Expression>(
                    new OperatorExpression(std::move(left), op, std::move(readOp2Exp(std::move(right)))));
        }
    }

    std::unique_ptr<Expression> Parser::readOp2Exp(std::unique_ptr<Expression> left)
    {
        if (getTokenType() != Token::Type::Operator4)
        {
            return readOp3Exp(std::move(left));
        }
        else
        {
            Operator op = lexer->getToken().getOperator();
            advance();
            std::unique_ptr<Expression> right = readSingleExpression();

            return std::unique_ptr<Expression>(
                    new OperatorExpression(std::move(left), op, std::move(readOp3Exp(std::move(right)))));
        }
    }

    std::unique_ptr<Expression> Parser::readOp3Exp(std::unique_ptr<Expression> left)
    {
        if (getTokenType() != Token::Type::Operator3)
        {
            return readOp4Exp(std::move(left));
        }
        else
        {
            Operator op = lexer->getToken().getOperator();
            advance();
            std::unique_ptr<Expression> right = readSingleExpression();

            return std::unique_ptr<Expression>(
                    new OperatorExpression(std::move(left), op, std::move(readOp4Exp(std::move(right)))));
        }
    }

    std::unique_ptr<Expression> Parser::readOp4Exp(std::unique_ptr<Expression> left)
    {
        if (getTokenType() != Token::Type::Operator2)
        {
            return readOp5Exp(std::move(left));
        }
        else
        {
            Operator op = lexer->getToken().getOperator();
            advance();
            std::unique_ptr<Expression> right = readSingleExpression();

            return std::unique_ptr<Expression>(
                    new OperatorExpression(std::move(left), op, std::move(readOp5Exp(std::move(right)))));
        }
    }

    std::unique_ptr<Expression> Parser::readOp5Exp(std::unique_ptr<Expression> left)
    {
        if (getTokenType() != Token::Type::Operator1)
            return left;
        else
        {
            Operator op = lexer->getToken().getOperator();
            advance();
            std::unique_ptr<Expression> right = readSingleExpression();

            return std::unique_ptr<Expression>(
                    new OperatorExpression(std::move(left), op, std::move(readOp1Exp(std::move(right)))));
        }
    }


    std::unique_ptr<Expression> Parser::readFunction()
    {

        std::string id;
        std::vector<std::unique_ptr<Expression> > temp_args;
        std::vector<std::shared_ptr<Expression> > args;
        if (getTokenType() != Token::Type::Fid)
            throwOnUnexpectedInput(Token::Type::Fid);
        id = lexer->getToken().getId();
        advance();
        if (getTokenType() != Token::Type::BracketOpen)
            throwOnUnexpectedInput(Token::Type::Fid);
        advance();
        while (getTokenType() != Token::Type::BracketClose)
            temp_args.push_back(std::move(readExpression()));
        advance();

        for (auto &i : temp_args)
            args.push_back(std::shared_ptr<Expression>(i.release()));

        return std::unique_ptr<Expression>(new FunctionExpression(id, args));
    }

    std::unique_ptr<Expression> Parser::readVariable()
    {
        std::unique_ptr<Expression> exp(new VariableExpression(requireToken(Token::Type::Id).getId()));
        advance();
        return exp;
    }


    void Parser::advance()
    {
        lexer->readNextToken();
    }

    void Parser::throwOnUnexpectedInput(Token::Type expected)
    {
        throw std::runtime_error("Unexpected token: " + lexer->getToken().toString()
                                 + ", expecting: " + Token::toString(expected));
    }

    void Parser::throwOnUnexpectedInput(std::vector<Token::Type> expected)
    {
        std::ostringstream tokens;
        for (Token::Type i : expected)
        {
            tokens << i << ", ";
        }
        throw std::runtime_error("Unexpected token: " + lexer->getToken().toString()
                                 + ", expecting: " + tokens.str());
    }

    Token::Type Parser::getTokenType()
    {
        return lexer->getToken().getType();
    }

    bool Parser::isOperator()
    {
        Token::Type t = getTokenType();
        return t == Token::Type::Operator1 || t == Token::Type::Operator2 ||
               t == Token::Type::Operator3 || t == Token::Type::Operator4 ||
               t == Token::Type::Operator5;
    }

    Token Parser::requireToken(Token::Type expected)
    {
        const auto token = lexer->getToken();
        const auto type = token.getType();
        if (type != expected)
            throwOnUnexpectedInput(expected);
        return token;
    }
}