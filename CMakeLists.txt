cmake_minimum_required(VERSION 3.21)
project(stack)

set(CMAKE_CXX_STANDARD 20)

add_executable(stack main.cpp stack_a.cpp stack_a.h stack_a_tools.cpp stack_a_tools.h string_tools.cpp string_tools.h codeTimer.h stack_tools.cpp stack_tools.h aides.h stack_l.cpp stack_l.h parenthesis.cpp parenthesis.h graphs.cpp graphs.h)
