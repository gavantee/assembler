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
 jmp myStart                  #0x00
# prekidna rutina za tajmer
isr_timer:
 push r0	                    #0x05
 push r1
 ldr r0, myChar    				#0x08
 str r0, term_out							#0x0D
 ldr r1, $1
 add r0, r1
 str r0, myChar
 pop r1
 pop r0												#0x12
 iret													#0x15
# prekidna rutina za terminal
isr_terminal:
 push r0											#0x16
 push r1											#0x19
 ldr r0, term_in							#0x1C
 ldr r1, $113
 cmp r0, r1
 jne %skip
 halt
 skip:
 str r0, term_out							#0x21
 pop r1
 pop r0
 iret
.end
