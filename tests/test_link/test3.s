# .word 0xffff
# .skip 0xffff

.extern f1_g1
.section text
.global f3_g1
jmp f3_g1
jmp %f1_g1
f3_g1: jmp text

.end
