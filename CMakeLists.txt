cmake_minimum_required(VERSION 2.8)
project(Nazkell)

include_directories(include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(${PROJECT_NAME}
        src/identificator.cpp
        src/fidentificator.cpp
        src/lexer.cpp
        src/operator.cpp
        src/reserved_id.cpp
        src/symbol.cpp
        src/token.cpp)

add_executable(lexer_test test/lexer_test.cpp)
target_link_libraries(lexer_test ${PROJECT_NAME})

add_executable(nazkell main.cpp)
target_link_libraries(nazkell ${PROJECT_NAME})