//
// Created by tomasz on 29.05.16.
//
#include <parser.h>
#include <sstream>
#include <expressions.h>

namespace nazkell
{
    Parser::Parser(Lexer lexer_)
    :lexer(lexer_)
    {
    }

    Parser::~Parser()
    {
    }

    std::unique_ptr<Body> Parser::parse()
    {
        return readBody();
    }

    std::unique_ptr<Body> Parser::readBody()
    {
        advance();
        std::unique_ptr<Body> body;
        while(lexer.getToken().getType() != Token::Type::Eof)
        {
            if(lexer.getToken().getType() != Token::Type::Fid)
                perror("invalid token or watever");
            std::string id = lexer.getToken().getId();
            advance();
            if(lexer.getToken().getType() == Token::Type::Colon)
            {
                body->addDeclaration(std::move(readDeclaration(id)));
            }
            else if(lexer.getToken().getType() == Token::Type::Id)
            {
                body->addDefinition(std::move(readDefinition(id)));
            }
            advance();
        }

        return body;
    }
    std::unique_ptr<Declaration> Parser::readDeclaration(std::string fid)
    {
        std::vector<Token::Type> types;

        advance();
        if(getTokenType() == Token::Type::Bool
                || getTokenType() == Token::Type::Int)
            types.push_back(lexer.getToken().getType());
        else
        {
            std::vector<Token::Type> temp;
            temp.push_back(Token::Type::Bool); temp.push_back(Token::Type::Integer);
            throwOnUnexpectedInput(temp);
        }
        advance();
        while(getTokenType() != Token::Type::NewLine)
        {
            if(getTokenType() != Token::Type::Left)
                throwOnUnexpectedInput(Token::Type::Left);
            advance();
            if(getTokenType() == Token::Type::Bool
                || getTokenType() == Token::Type::Int)
                types.push_back(lexer.getToken().getType());
            else
            {
                std::vector<Token::Type> temp;
                temp.push_back(Token::Type::Bool); temp.push_back(Token::Type::Integer);
                throwOnUnexpectedInput(temp);
            }
            advance();
        }
        return std::unique_ptr<Declaration>(new Declaration(fid, types));
    }
    std::unique_ptr<Definition> Parser::readDefinition(std::string fid)
    {
        std::vector<std::string> tokens;
        std::vector<std::unique_ptr<Expression> > expressions;
        while(getTokenType() != Token::Type::Operator6)
        {
            tokens.push_back(requireToken(Token::Type::Id).getId());
            advance();
        }
        advance();
        do
        {
            expressions.push_back(std::move(readExpression()));
            advance();
            advance();
        }while(getTokenType() != Token::Type::NewLine);
    }

    std::unique_ptr<Expression> Parser::readExpression()
    {
        std::unique_ptr<Expression> exp = readSingleExpression();
        advance();
        while(isOperator())
        {
            exp = readOp1Exp(std::move(exp));
            advance();
        }

    }

    std::unique_ptr<Expression> Parser::readSingleExpression()
    {
        switch(getTokenType())
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
            case Token::Type::SBracketOpen :
                return readList();
            case Token::Type::Not :
                return readNegation();
        }

    }

    std::unique_ptr<Expression> Parser::readBoolean()
    {
        return std::unique_ptr<Expression>(new BooleanExpression(lexer.getToken().getBoolean()));
    }

    std::unique_ptr<Expression> Parser::readInteger()
    {
        return std::unique_ptr<Expression>(new IntegerExpression(lexer.getToken().getInteger()));
    }

    std::unique_ptr<Expression> Parser::readIfStatement()
    {
        std::vector< std::unique_ptr < Expression > > ifexp, elseexp, cond;
        while(getTokenType() != Token::Type::Then)
        {
            advance();
            cond.push_back(std::move(readExpression()));
        }
        while(getTokenType() != Token::Type::Else || getTokenType()!= Token::Type::Fi)
        {
            advance(); // or not ?
            ifexp.push_back(std::move(readExpression()));
        }
        if(getTokenType() == Token::Type::Else)
            while(getTokenType()!= Token::Type::Fi)
            {
                advance();
                elseexp.push_back(std::move(readExpression()));
            }
        return std::unique_ptr<Expression> (new IfExpression(std::move(cond), std::move(ifexp), std::move(elseexp)));
    }

    std::unique_ptr<Expression> Parser::readParenthesesExperssion()
    {
        advance();
        std::unique_ptr<Expression> exp(readExpression());
        if(getTokenType() != Token::Type::BracketClose)
            throwOnUnexpectedInput(Token::Type::BracketClose);
        return exp;
    }

    std::unique_ptr<Expression> Parser::readOp1Exp(std::unique_ptr<Expression> left)
    {
        if(getTokenType() != Token::Type::Operator1)
        {
            return readOp2Exp(std::move(left));
        }
        else
        {
            if(left->getType() != Expression::ExpressionType::Id)
                throwOnUnexpectedInput(Token::Type::Id);
            Operator op = lexer.getToken().getOperator();
            advance();
            std::unique_ptr<Expression> right = readSingleExpression();
            advance();
            return std::unique_ptr<Expression>(
                    new OperatorExpression(std::move(left), op, std::move(readOp2Exp(std::move(right)))));
        }


            
    }

    std::unique_ptr<Expression> Parser::readOp2Exp(std::unique_ptr<Expression> left)
    {
        if(getTokenType() != Token::Type::Operator2)
        {
            return readOp3Exp(std::move(left));
        }
        else
        {
            Operator op = lexer.getToken().getOperator();
            advance();
            std::unique_ptr<Expression> right = readSingleExpression();
            advance();
            return std::unique_ptr<Expression>(
                    new OperatorExpression(std::move(left), op, std::move(readOp3Exp(std::move(right)))));
        }
    }

    std::unique_ptr<Expression> Parser::readOp3Exp(std::unique_ptr<Expression> left)
    {
        if(getTokenType() != Token::Type::Operator3)
        {
            return readOp4Exp(std::move(left));
        }
        else
        {
            Operator op = lexer.getToken().getOperator();
            advance();
            std::unique_ptr<Expression> right = readSingleExpression();
            advance();
            return std::unique_ptr<Expression>(
                    new OperatorExpression(std::move(left), op, std::move(readOp4Exp(std::move(right)))));
        }
    }

    std::unique_ptr<Expression> Parser::readOp4Exp(std::unique_ptr<Expression> left)
    {
        if(getTokenType() != Token::Type::Operator4)
        {
            return readOp5Exp(std::move(left));
        }
        else
        {
            Operator op = lexer.getToken().getOperator();
            advance();
            std::unique_ptr<Expression> right = readSingleExpression();
            advance();
            return std::unique_ptr<Expression>(
                    new OperatorExpression(std::move(left), op, std::move(readOp5Exp(std::move(right)))));
        }
    }

    std::unique_ptr<Expression> Parser::readOp5Exp(std::unique_ptr<Expression> left)
    {
        if(getTokenType() != Token::Type::Operator5)
        {
            return readOp6Exp(std::move(left));
        }
        else
        {
            Operator op = lexer.getToken().getOperator();
            advance();
            std::unique_ptr<Expression> right = readSingleExpression();
            advance();
            return std::unique_ptr<Expression>(
                    new OperatorExpression(std::move(left), op, std::move(readOp6Exp(std::move(right)))));
        }
    }

    std::unique_ptr<Expression> Parser::readOp6Exp(std::unique_ptr<Expression> left)
    {
        if(getTokenType() != Token::Type::Operator6)
        {
            if(isOperator())
                return readOp1Exp(std::move(left));
            else
            {
                return left;
            }
        }
        else
        {
            Operator op = lexer.getToken().getOperator();
            advance();
            std::unique_ptr<Expression> right = readSingleExpression();
            advance();
            return std::unique_ptr<Expression>(
                    new OperatorExpression(std::move(left), op, std::move(readOp1Exp(std::move(right)))));
        }
    }

    std::unique_ptr<Expression> Parser::readList()
    {

    }

    std::unique_ptr<Expression> Parser::readFunction()
    {
        std::string id;
        std::vector<std::unique_ptr<Expression> > args;
        if(getTokenType() != Token::Type::Fid)
            throwOnUnexpectedInput(Token::Type::Fid);
        id = lexer.getToken().getId();
        advance();
        if(getTokenType() != Token::Type::BracketOpen)
            throwOnUnexpectedInput(Token::Type::Fid);
        advance();
        while(getTokenType() != Token::Type::BracketClose)
            args.push_back(std::move(readExpression()));
    }
    std::unique_ptr<Expression> Parser::readVariable()
    {
        return std::unique_ptr<Expression>(new VariableExpression(requireToken(Token::Type::Id).getId()));
    }
    std::unique_ptr<Expression> Parser::readNegation()
    {

    }

    std::unique_ptr<Expression> Parser::readCondition()
    {
        switch(getTokenType())
        {
            case Token::Type::Boolean :
                return readBoolean();
            case Token::Type::Integer :
                return readInteger();
            case Token::Type::Id :
                return readVariable();
            case Token::Type::Fid :
                return readFunction();
            case Token::Type::BracketOpen :
                return readParenthesesExperssion();
            case Token::Type::SBracketOpen :
                return readList();
            case Token::Type::Not :
                return readNegation();
        }
    }

    void Parser::advance()
    {
        lexer.readNextToken();
        std::cout << lexer.getToken() << std::endl;
    }
    void Parser::throwOnUnexpectedInput(Token::Type expected)
    {
        throw std::runtime_error("Unexpected token: " + lexer.getToken().toString()
                           + ", expecting: " + Token::toString(expected));
    }
    void Parser::throwOnUnexpectedInput(std::vector<Token::Type> expected)
    {
        std::ostringstream tokens;
        for(Token::Type i : expected)
        {
            tokens << i << ", ";
        }
        throw std::runtime_error("Unexpected token: " + lexer.getToken().toString()
                           + ", expecting: " + tokens.str());
    }
    Token::Type Parser::getTokenType()
    {
        return lexer.getToken().getType();
    }
    bool Parser::isOperator()
    {
        Token::Type t = getTokenType();
        return t == Token::Type::Operator1 || t == Token::Type::Operator2 ||
               t == Token::Type::Operator3 || t == Token::Type::Operator4 ||
               t == Token::Type::Operator5 || t == Token::Type::Operator6;
    }

    Token Parser::requireToken(Token::Type expected)
    {
        const auto token = lexer.getToken();
        const auto type = token.getType();
        if (type != expected)
            throwOnUnexpectedInput(expected);
        return token;
    }
}