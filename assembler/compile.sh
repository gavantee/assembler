#!/bin/sh

rm -rf bison.cpp bison.hpp flex.cpp a.out
bison -o bison.cpp -d parser.y
flex -o flex.cpp lexer.l
g++ -std=c++17 flex.cpp bison.cpp symtable.cpp assembler.cpp
