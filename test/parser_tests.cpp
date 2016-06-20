//
// Created by tomasz on 01.06.16.
//
//
// Created by tomasz on 19.06.16.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE parser_test
#include <sstream>

#include <boost/test/unit_test.hpp>
#include <parser.h>
#include <expressions.h>

using namespace nazkell;
struct ParserTestsFixture
{
    void parse(const std::string &str)
    {
        std::istringstream in(str);
        Parser p(std::unique_ptr<Lexer>(new Lexer(in)));
        b.reset(p.parse());
    }

    std::string ToString() const
    {
        return b->toString();
    }

    Value evaluate(std::vector<int> arg) const
    {
        b->resetStack();
        std::vector<std::shared_ptr<Expression>> v;
        for(auto i : arg)
            v.push_back(std::shared_ptr<Expression>(new IntegerExpression(i)));
        return b->evaluate(v, "Main");
    }

    std::unique_ptr<Body> b;
};

BOOST_FIXTURE_TEST_SUITE(ExpressionTests, ParserTestsFixture)

    BOOST_AUTO_TEST_CASE(parsing_empty_input_throws)
    {
        BOOST_CHECK_THROW(parse(""), std::runtime_error);
    }


    BOOST_AUTO_TEST_CASE(parsing_declaration_returns_proper_structure)
    {
        const std::string input = "Fun::int->bool->int->int->bool\n";
        parse(input);

        BOOST_CHECK_EQUAL(ToString(), input);
    }


    BOOST_AUTO_TEST_CASE(parsing_definition_returns_proper_structure)
    {
        const std::string input = "Fun x y z = 5\n";
        parse(input);

        BOOST_CHECK_EQUAL(ToString(), input);
    }

    BOOST_AUTO_TEST_CASE(parsing_complex_expression_returns_proper_tree)
    {
        const std::string input = "Fun x y z t = if x == z & y != t\nx + y\nelse\nz + t\n";
        parse(input);


        BOOST_CHECK_EQUAL(ToString(), input);
    }

    BOOST_AUTO_TEST_CASE(uncomplete_input_throws)
    {
        BOOST_CHECK_THROW(parse("Fun x = "), std::runtime_error);
        BOOST_CHECK_THROW(parse("5"), std::runtime_error);
    }

    BOOST_AUTO_TEST_CASE(grammar_properly_bounds_expressions_from_left_to_rigth)
    {
        parse("Main::int->int->int->int->int\nMain x y z t = x ** y - z * t\n");
        std::vector<int> a({1,2,3,4});
        BOOST_CHECK_EQUAL(evaluate(a).i, 1);
    }

    BOOST_AUTO_TEST_CASE(evaluating_if_expression_depends_on_condition_value)
    {
        parse("Main::int->int\nMain x = if x > 10 \nx\nelse\nx + 10\n");
        std::vector<int> a({2});
        BOOST_CHECK_EQUAL(evaluate(a).i, 12);
        a[0] = 12;
        BOOST_CHECK_EQUAL(evaluate(a).i, 12);
    }

BOOST_AUTO_TEST_SUITE_END()