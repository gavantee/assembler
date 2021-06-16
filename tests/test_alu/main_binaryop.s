# file: main.s
.equ term_out, 0xff00

.section ivt
 .word start
 .skip 6 # isr_error, isr_timer, isr_terminal
 .skip 8

.section text
start:
 ldr r0, $0x3
 ldr r1, $0x7
 add r0,r1
 call print_res

 ldr r0, $0x50
 ldr r1, $0x33
 sub r0,r1
 call print_res

 ldr r0, $0x5
 ldr r1, $0x3
 mul r0,r1
 call print_res

 ldr r0, $0x10
 ldr r1, $0x5
 div r0, r1
 call print_res

 ldr r0, $2
 ldr r1, $6
 or r0, r1
 call print_res

 ldr r0, $0x7
 ldr r1, $0x7
 xor r0, r1
 call print_res


 ldr r0, $0x3
 ldr r1, $0x1
 shl r0, r1
 call print_res


 ldr r0, $0x3
 ldr r1, $0x1
 shr r0, r1
 call print_res

 halt


print_res:
    push r0
    push r1
    push r2
    push r3
    ldr r2,r0
loop:
    ldr r0,r2
    ldr r3,$1
    and r0,r3
    ldr r3,$0
    cmp r0,r3
    jeq print_nula
    ldr r3,$49
    str r3,term_out
    jmp dalje
print_nula:
    ldr r3,$48
    str r3,term_out
dalje: 
    ldr r3,$1
    shr r2,r3
    jne loop
    ldr r0, $0x0a
    str r0, term_out
kraj:
    pop r3
    pop r2
    pop r1 
    pop r0
    ret

