
;operand addressing errors

mov %ohno, #1
mov %ohno, %ohyes

clr #-1
clr %ohno

not #-1
not %ohno

inc #-1
inc %ohno

dec #-1
dec %ohno

jmp #-1
jmp r1,r2

bne #-1

jsr #-1

prn %ohno

rts #-1
rts someLabel47
rts %ohno
rts r1

