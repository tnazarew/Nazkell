cmake_minimum_required(VERSION 2.8)
project(Nazkell)

include_directories(include)

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
        src/value_type.cpp
        src/body.cpp
        src/operator_expression.cpp
        src/boolean_expression.cpp
        src/integer_expression.cpp
        src/variable_expression.cpp
        src/if_expression.cpp
        src/function_expression.cpp
        src/declaration.cpp
        src/definition.cpp)

add_executable(lexer_test test/lexer_test.cpp)
target_link_libraries(lexer_test ${PROJECT_NAME})

add_executable(parser_test test/parser_test.cpp)
target_link_libraries(parser_test ${PROJECT_NAME})

add_executable(nazkell main.cpp)
target_link_libraries(nazkell ${PROJECT_NAME})