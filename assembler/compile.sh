#!/bin/sh

rm -rf bison.cpp bison.hpp flex.cpp a.out
bison -o bison.cpp -d test.y
flex -o flex.cpp test.l
g++ -std=c++17 flex.cpp bison.cpp assembler.cpp
