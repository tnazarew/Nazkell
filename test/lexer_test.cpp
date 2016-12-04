#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE lexer_test
#include <sstream>

#include <boost/test/unit_test.hpp>
#include <lexer.h>

using namespace nazkell;

BOOST_AUTO_TEST_SUITE(lexerTests)

    BOOST_AUTO_TEST_CASE(reading_token_before_first_advance_returns_eof)
    {
        std::istringstream in;
        Lexer s(in);
        BOOST_CHECK_EQUAL(s.getToken().getType(), Token::Type::Eof);
    }

    BOOST_AUTO_TEST_CASE(scanning_empty_input_returns_eof_token)
    {
        std::istringstream in;
        Lexer s(in);
        s.readNextToken();

        BOOST_CHECK_EQUAL(s.getToken().getType(), Token::Type::Eof);
    }

    BOOST_AUTO_TEST_CASE(lexer_read_int_token)
    {
        std::istringstream in("123");
        Lexer s(in);

        s.readNextToken();
        const auto t = s.getToken();

        BOOST_CHECK_EQUAL(t.getType(), Token::Type::Integer);
        BOOST_CHECK_EQUAL(t.getInteger(), 123);
    }

    BOOST_AUTO_TEST_CASE(lexer_returns_eof_after_last_token)
    {
        std::istringstream in("123");
        Lexer s(in);

        s.readNextToken();
        s.readNextToken();

        BOOST_CHECK_EQUAL(s.getToken().getType(), Token::Type::Eof);
    }

    BOOST_AUTO_TEST_CASE(lexer_ignores_whitespaces)
    {
        std::istringstream in("  \t\n   123");
        Lexer s(in);

        s.readNextToken();
        const auto t = s.getToken();

        BOOST_CHECK_EQUAL(t.getType(), Token::Type::Integer);
        BOOST_CHECK_EQUAL(t.getInteger(), 123);
    }

    BOOST_AUTO_TEST_CASE(lexer_throws_on_unknown_token)
    {
        std::istringstream in(";");
        Lexer s(in);

        BOOST_CHECK_THROW(s.readNextToken(), std::runtime_error);
    }

    BOOST_AUTO_TEST_CASE(lexer_reads_subsequent_tokens)
    {
        std::istringstream in("12 100");
        Lexer s(in);

        s.readNextToken();
        const auto t1 = s.getToken();

        s.readNextToken();
        const auto t2 = s.getToken();

        s.readNextToken();
        const auto t3 = s.getToken();

        BOOST_CHECK_EQUAL(t1.getType(), Token::Type::Integer);
        BOOST_CHECK_EQUAL(t2.getType(), Token::Type::Integer);
        BOOST_CHECK_EQUAL(t3.getType(), Token::Type::Eof);

        BOOST_CHECK_EQUAL(t1.getInteger(), 12);
        BOOST_CHECK_EQUAL(t2.getInteger(), 100);
    }

    BOOST_AUTO_TEST_CASE(lexer_throws_on_stream_error)
    {
        std::istringstream in("123");
        in.setstate(std::ios_base::badbit);
        Lexer s(in);

        BOOST_CHECK_THROW(s.readNextToken(), std::runtime_error);
    }


    BOOST_AUTO_TEST_CASE(lexer_scans_minus_operator_properly)
    {
        std::istringstream in("-");
        Lexer s(in);
        s.readNextToken();

        BOOST_CHECK_EQUAL(s.getToken().getType(), Token::Type::Operator3);
        BOOST_CHECK_EQUAL(s.getToken().getOperator(), Operator::Minus);
    }
    BOOST_AUTO_TEST_CASE(lexer_scans_bracket_open_properly)
    {
        std::istringstream in("(");
        Lexer s(in);
        s.readNextToken();

        BOOST_CHECK_EQUAL(s.getToken().getType(), Token::Type::BracketOpen);
        BOOST_CHECK_EQUAL(s.getToken().getSymbol(), Symbol::BracketOpen);
    }
    BOOST_AUTO_TEST_CASE(lexer_scans_brackket_close_properly)
    {
        std::istringstream in(")");
        Lexer s(in);
        s.readNextToken();

        BOOST_CHECK_EQUAL(s.getToken().getType(), Token::Type::BracketClose);
        BOOST_CHECK_EQUAL(s.getToken().getSymbol(), Symbol::BracketClose);
    }


    BOOST_AUTO_TEST_CASE(lexer_scans_right_properly)
    {
        std::istringstream in("->");
        Lexer s(in);
        s.readNextToken();

        BOOST_CHECK_EQUAL(s.getToken().getType(), Token::Type::Right);
        BOOST_CHECK_EQUAL(s.getToken().getSymbol(), Symbol::Right);
    }


    BOOST_AUTO_TEST_CASE(lexer_scans_colon_properly)
    {
        std::istringstream in("::");
        Lexer s(in);
        s.readNextToken();

        BOOST_CHECK_EQUAL(s.getToken().getType(), Token::Type::Colon);
        BOOST_CHECK_EQUAL(s.getToken().getSymbol(), Symbol::Colon);
    }

    BOOST_AUTO_TEST_CASE(lexer_scans_bool_properly)
    {
        std::istringstream in("Bool");
        Lexer s(in);
        s.readNextToken();

        BOOST_CHECK_EQUAL(s.getToken().getType(), Token::Type::Bool);

    }

    BOOST_AUTO_TEST_CASE(lexer_scans_int_properly)
    {
        std::istringstream in("Int");
        Lexer s(in);
        s.readNextToken();

        BOOST_CHECK_EQUAL(s.getToken().getType(), Token::Type::Int);
\
    }

    BOOST_AUTO_TEST_CASE(lexer_scans_if_properly)
    {
        std::istringstream in("if");
        Lexer s(in);
        s.readNextToken();

        BOOST_CHECK_EQUAL(s.getToken().getType(), Token::Type::If);

    }

    BOOST_AUTO_TEST_CASE(lexer_scans_else_properly)
    {
        std::istringstream in("else");
        Lexer s(in);
        s.readNextToken();

        BOOST_CHECK_EQUAL(s.getToken().getType(), Token::Type::Else);

    }
    BOOST_AUTO_TEST_CASE(lexer_scans_id_properly)
    {
        std::istringstream in("x");
        Lexer s(in);
        s.readNextToken();

        BOOST_CHECK_EQUAL(s.getToken().getType(), Token::Type::Id);
        BOOST_CHECK_EQUAL(s.getToken().getId(), "x");
    }
    BOOST_AUTO_TEST_CASE(lexer_scans_fid_properly)
    {
        std::istringstream in("M");
        Lexer s(in);
        s.readNextToken();

        BOOST_CHECK_EQUAL(s.getToken().getType(), Token::Type::Fid);
        BOOST_CHECK_EQUAL(s.getToken().getId(), "M");
    }
    BOOST_AUTO_TEST_CASE(lexer_scans_power_operator_properly)
    {
        std::istringstream in("**");
        Lexer s(in);
        s.readNextToken();

        BOOST_CHECK_EQUAL(s.getToken().getType(), Token::Type::Operator1);
        BOOST_CHECK_EQUAL(s.getToken().getOperator(), Operator::Power);
    }
    BOOST_AUTO_TEST_CASE(lexer_scans_greater_operator_properly)
    {
        std::istringstream in(">");
        Lexer s(in);
        s.readNextToken();

        BOOST_CHECK_EQUAL(s.getToken().getType(), Token::Type::Operator4);
        BOOST_CHECK_EQUAL(s.getToken().getOperator(), Operator::Greater);
    }

    BOOST_AUTO_TEST_CASE(lexer_scans_or_operator_properly)
    {
        std::istringstream in("|");
        Lexer s(in);
        s.readNextToken();

        BOOST_CHECK_EQUAL(s.getToken().getType(), Token::Type::Operator5);
        BOOST_CHECK_EQUAL(s.getToken().getOperator(), Operator::Or);
    }

    BOOST_AUTO_TEST_CASE(lexer_scans_multiply_operator_properly)
    {
        std::istringstream in("*");
        Lexer s(in);
        s.readNextToken();

        BOOST_CHECK_EQUAL(s.getToken().getType(), Token::Type::Operator2);
        BOOST_CHECK_EQUAL(s.getToken().getOperator(), Operator::Multiply);
    }


BOOST_AUTO_TEST_SUITE_END()