.align	1
HEX_TO_ASCII_TABLE:
	.ascii	"0123456789ABCDEF"
.global CPrintChar
CPrintChar:      

        push {r0,r1,r2,r3,r4,fp,lr}

	mov     r3,r0
	
txBusy:
	
	
        ldr	r1, =0x50000000
	ldr	r2, [r1, #0x10]
	and	r2, r2, #0x4
	tst	r2, #0x4
	beq	txBusy	
	strb	r3, [r1, #0x20]
	


        pop {r0,r1,r2,r3,r4,fp,lr}
	mov pc,lr


.global CPrintstr
CPrintstr:      

        push {r0,r1,r2,r3,r4,fp,lr}
	ldr 	r1, =0x30000800
	add  	r0,r0,r1
	@ bl	printfPC
	ldr	r1, =0x50000000
	ldr	r2, [r1, #0x10]
	and	r2, r2, #0x4
outstart:	
	ldrb    r3,[r0],#1
	and     r3,r3,#0xff
	cmp     r3,#'\0'
	bne     outend
	
Busy:

	tst	r2, #0x4
	beq	Busy
	strb	r3, [r1, #0x20]
	
	b       outstart
outend:

	
        pop {r0,r1,r2,r3,r4,fp,lr}
	mov pc,lr




