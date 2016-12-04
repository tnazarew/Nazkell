cmake_minimum_required(VERSION 2.8)
project(Nazkell)

include_directories(include)
find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")

add_library(${PROJECT_NAME}
        src/identificator.cpp
        src/fidentificator.cpp
        src/lexer.cpp
        src/operator.cpp
        src/reserved_id.cpp
        src/symbol.cpp
        src/token.cpp
        src/parser.cpp
        src/expression.cpp
        src/body.cpp
        src/operator_expression.cpp
        src/boolean_expression.cpp
        src/integer_expression.cpp
        src/variable_expression.cpp
        src/if_expression.cpp
        src/function_expression.cpp
        src/declaration.cpp
        src/definition.cpp
        )

enable_testing()

add_executable(lexer_test test/lexer_test.cpp)
target_link_libraries(lexer_test
        ${PROJECT_NAME}
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        )

add_test(LexerTest lexer_test)

add_executable(token_test test/token_tests.cpp)
target_link_libraries(token_test
        ${PROJECT_NAME}
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        )

add_test(TokenTest token_test)


add_executable(parser_test test/parser_tests.cpp)
target_link_libraries(parser_test
        ${PROJECT_NAME}
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        )

add_test(ParserTest parser_test)


add_executable(nazkell main.cpp)
target_link_libraries(nazkell ${PROJECT_NAME})