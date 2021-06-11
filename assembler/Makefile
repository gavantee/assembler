all: assembler

clean:
	rm -rf src/bison.cpp inc/bison.hpp src/flex.cpp assembler *.o
bison inc/bison.hpp src/bison.cpp: src/parser.y
	bison -o src/bison.cpp --defines=inc/bison.hpp src/parser.y
flex src/flex.cpp: src/lexer.l inc/bison.hpp
	flex -o src/flex.cpp src/lexer.l
assembler: src/*.cpp inc/*.h bison
	g++ -std=c++17 -o assembler src/flex.cpp src/bison.cpp src/code.cpp src/assembler.cpp -Iinc

test: assembler
	./assembler -o tests/interrupts.o tests/interrupts.s
	./assembler -o tests/main.o tests/main.s
