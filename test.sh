rm -rf ./obj
mkdir obj
for var in "$@"
do
    ./assembler/assembler -o "obj/$var.o" "$var"
done

./linker/linker -hex -place=ivt@0 -o obj/out.hex obj/*.o
./emulator/emulator obj/out.hex
