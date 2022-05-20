cmake_minimum_required(VERSION 3.5)

project(LispInterpreter2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(LispInterpreter2
    main.cpp
        src/Level1Parser/Level1Parser.cpp
        src/Level1Parser/Level1Parser.h
        src/Level1Parser/Level1Token.h src/Eval/LispValue.h src/Level2Parser/Level2Parser.h src/Level2Parser/Level2Parser.cpp src/Level2Parser/Level2Token.h src/Eval/Eval.h src/Eval/Eval.cpp src/Helper.h src/Helper.cpp src/Eval/Reserved.h src/Eval/Reserved.cpp src/Eval/Defined.h)
