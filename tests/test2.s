.extern f1_g1

.section text
ldr r1, %f1_g1
jmp %f1_g1
local_1: .word 0xffff
.equ local_2, 0xff
pop r1
push r2
jeq %local_1
jeq local_1
jeq label

.section data
label:
.word 0xffff, 0, local_2
f2_g1:

.section bss

.global f2_g1
.end
