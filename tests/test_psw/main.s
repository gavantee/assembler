# file: main.s
.equ term_out, 0xff00

.section ivt
 .word start
 .skip 2
 .word isr_timer
 .skip 2
 .skip 8

.section text
start:
 ldr r0, $0x7fff
 ldr r1, $0xff00
 cmp r0, r1
 call print_psw

 ldr r0, $0x000e
 ldr r1, $1
 shr r0, r1
 call print_psw

 ldr r0, $0xfffe
 ldr r1, $2
 shr r0, r1
 call print_psw

 ldr r0, $0x4000
 ldr r1, $1
 shl r0, r1
 call print_psw

 ldr r0, $0x4000
 ldr r1, $2
 shl r0, r1
 call print_psw

 ldr r0, $0x7fff
 ldr r1, $0x0fff
 cmp r0, r1
 call print_psw
 halt

print_psw:
 push r0
 push r1
 push r2
 push r5
 #Z
 ldr r2, $0
 ldr r5, psw
 loop:
 ldr r0, r2
 ldr r1, $2
 mul r0, r1
 ldr r0, [r0 + data]
 str r0, term_out
 ldr r0, $0x3a
 str r0, term_out
 ldr r0, $0x20
 str r0, term_out
 ldr r0, r5
 ldr r1, $0x0001
 shl r1, r2
 and r0, r1
 shr r0, r2
 ldr r1, $0x30
 add r0, r1
 str r0, term_out
 ldr r0, $0x20
 str r0, term_out

 ldr r1, $1
 add r2, r1
 ldr r0, $4
 cmp r2, r0
 jne loop

 ldr r0, $0x0a
 str r0, term_out

 ldr psw, r5
 pop r0
 pop r1
 pop r2
 pop r5
 ret

 isr_timer:
 iret

.section data
 .word 0x5a, 0x4f, 0x43, 0x4e
.end
