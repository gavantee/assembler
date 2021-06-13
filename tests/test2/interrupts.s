# file: interrupts.s
.section ivt
 .word isr_reset
 .skip 2 # isr_error
 .word isr_timer
 .word isr_terminal
 .skip 8
.extern myStart, myCounter, myChar
.section isr
.equ term_out, 0xFF00
.equ term_in, 0xFF02
.equ asciiCode, 84 # ascii(’T’)
# prekidna rutina za reset
isr_reset:
 ldr r3, $12
 jmp myStart
# prekidna rutina za tajmer
isr_timer:
 push r0
 push r1
 push r2
 ldr r1, myCounter
 ldr r0, [r1 + myChar]
 str r0, term_out
 ldr r2, $2
 add r1, r2
 cmp r1, r3
 jne %skip2
 halt
 skip2:
 str r1, myCounter
 pop r2
 pop r1
 pop r0
 iret
# prekidna rutina za terminal
isr_terminal:
 push r0
 push r1
 ldr r0, term_in
 ldr r1, $113
 cmp r0, r1
 jne %skip
 halt
 skip:
 ldr r1, $0x60
 cmp r0, r1
 jne %skip3
 ldr r3, $24
 skip3:
 # str r0, term_out
 pop r1
 pop r0
 iret
.end
