cmake_minimum_required(VERSION 3.12)
project(Jajavava)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Release)
set(SOURCE_FILES src/Lexer.h src/Lexer.cpp src/Parser.cpp src/Parser.h)
set(SOURCE_FILES ${SOURCE_FILES} src/Interpreter.h src/Interpreter.cpp)
add_executable(main ${SOURCE_FILES} src/main.cpp)
