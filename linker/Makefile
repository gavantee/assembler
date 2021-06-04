all: linker

clean:
	rm -rf ./linker ./*.o ./*.hex

linker: src/*.c inc/*.h
	gcc -o linker src/*.c -Iinc

test: linker
	./linker -place=ivt@0 -hex -o tests/out.hex tests/interrupts.o tests/main.o
	./linker -linkable -o tests/out.o tests/interrupts.o tests/main.o
