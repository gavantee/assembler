all: emulator

clean:
	rm -rf ./emulator

emulator: src/*.c inc/*.h
	gcc -o emulator src/*.c -Iinc

#test: emulator
