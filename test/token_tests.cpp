//
// Created by tomasz on 19.06.16.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE token_test

#include <sstream>

#include <boost/test/unit_test.hpp>
#include <token.h>

using namespace nazkell;

BOOST_AUTO_TEST_SUITE(TokenTests)

    BOOST_AUTO_TEST_CASE(default_token_has_eof_type)
    {
        Token t;
        BOOST_CHECK_EQUAL(t.getType(), Token::Type::Eof);
    }

    BOOST_AUTO_TEST_CASE(int_constructor_creates_integer_type_token)
    {
        Token t(123);
        BOOST_CHECK_EQUAL(t.getType(), Token::Type::Integer);
    }

    BOOST_AUTO_TEST_CASE(int_constructed_token_contains_value)
    {
        const int value = 12343123;
        Token t(value);
        BOOST_CHECK_EQUAL(t.getInteger(), value);
    }

    BOOST_AUTO_TEST_CASE(eof_token_prints_properly)
    {
        Token t;
        BOOST_CHECK_EQUAL(t.toString(), "end of input (end of file)");
    }

    BOOST_AUTO_TEST_CASE(int_token_prints_properly)
    {
        Token t(42);
        BOOST_CHECK_EQUAL(t.toString(), "integer (42)");
    }

    BOOST_AUTO_TEST_CASE(bool_token_prints_properly)
    {
        Token t(true);
        BOOST_CHECK_EQUAL(t.toString(), "boolean (1)");
    }

    BOOST_AUTO_TEST_CASE(token_constructed_with_operator_returns_operator_type)
    {
        Token t(Operator::Plus);
        BOOST_CHECK_EQUAL(t.getType(), Token::Type::Operator3);
    }

    BOOST_AUTO_TEST_CASE(token_constructed_with_operator_contains_it)
    {
        const auto op = Operator::Minus;
        Token t(op);
        BOOST_CHECK_EQUAL(t.getOperator(), op);
    }

    BOOST_AUTO_TEST_CASE(token_constructed_with_operator_prints_properly)
    {
        Token t(Operator::Plus);
        BOOST_CHECK_EQUAL(t.toString(), "operator3 (+)");
    }




BOOST_AUTO_TEST_SUITE_END()