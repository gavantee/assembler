# file: interrupts.s
.section ivt
 .word isr_reset
 .skip 2 # isr_error
 .word isr_timer
 .word isr_terminal
 .skip 8
.extern myStart, myCounter
.section isr
.equ term_out, 0xFF00
.equ term_in, 0xFF02
.equ asciiCode, 84 # ascii(âTâ)
# prekidna rutina za reset
isr_reset:
 jmp myStart                  #0x00
# prekidna rutina za tajmer
isr_timer:
 push r0											#0x05
 ldr r0, $asciiCode						#0x08
 str r0, term_out							#0x0D
 pop r0												#0x12
 iret													#0x15
# prekidna rutina za terminal
isr_terminal:
 push r0											#0x16
 push r1											#0x19
 ldr r0, term_in							#0x1C
 str r0, term_out							#0x21
 ldr r0, %myCounter # pcrel		#0x26
 ldr r1, $1										#0x2B
 add r0, r1
 str r0, myCounter # abs
 pop r1
 pop r0
 iret
.end
