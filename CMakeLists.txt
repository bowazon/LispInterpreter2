cmake_minimum_required(VERSION 3.5)

project(LispInterpreter2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(LispInterpreter2
    main.cpp
    Level1Parser.cpp Level1Parser.h Level1Token.h)
