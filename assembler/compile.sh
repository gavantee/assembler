#!/bin/sh

rm -rf src/bison.cpp inc/bison.hpp src/flex.cpp assembler
bison -o src/bison.cpp --defines=inc/bison.hpp src/parser.y
flex -o src/flex.cpp src/lexer.l
g++ -std=c++17 -o assembler src/flex.cpp src/bison.cpp src/code.cpp src/assembler.cpp -Iinc
