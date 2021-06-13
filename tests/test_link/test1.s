.global f1_g1, f1_g2
.equ f1_g2, 0xffff
# .equ pucice, 0xfffff

.extern f2_g1, f3_g1
.section text
ldr r1, [r1 + f1_g1]
jmp f1_g1
str r1, [r2]
f1_g1: jmp %f2_g1 # Komentar
# jmp [r7 + f2_g1]
ldr r2, label
ldr r3, data1

.section data
label:
.word 0xffff, f2_g1, 0
.skip 0x10
data1: .word f1_g2

.end

.section after_end
