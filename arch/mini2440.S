#include "s3c2440.h"
.global _start
@_start:
.align 4
    
@ 0x00: Reset
	b	Reset

@ 0x04: Undefined instruction exception
UndefEntryPoint:
	b	HandleUndef

@ 0x08: Software interrupt exception
SWIEntryPoint:
	b	HandleSWI

@ 0x0c: Prefetch Abort (Instruction Fetch Memory Abort)
PrefetchAbortEnteryPoint:
	b	HandlePrefetchAbort

@ 0x10: Data Access Memory Abort
DataAbortEntryPoint:
	b	HandleDataAbort

@ 0x14: Not used
NotUsedEntryPoint:
	b	HandleNotUsed

@ 0x18: IRQ(Interrupt Request) exception
IRQEntryPoint:
	b	HandleIRQ

@ 0x1c: FIQ(Fast Interrupt Request) exception
FIQEntryPoint:
	b	HandleFIQ
data_aera:

UART_BRD:   .long ((50000000/(115200*16))-1)

Reset:
	mov 	r0,pc
	cmp	r0,#0xff
	bgt	_on_the_ram
	@; disable watch dog timer
	mov	r1, #0x53000000
	mov	r2, #0x0
	str	r2, [r1]
	msr cpsr_c,#0xd3 @;svc
	ldr sp,=0x33d00000
    
      @;  @ �����ж�ģʽ
  msr cpsr_c,#0xd2   @irq stack
  ldr sp,=0x33600000
  msr cpsr_c,#0xd3 @;svc
  
  
  @;�����ж�
  ldr r0,=0x4A000008 @;INTMSK
  ldr r1,=0xffffffff   @;����
  str r1,[r0]   
  
  ldr r0,=0x4A00001C @;INTSUBMSK
  str r1,[r0]
  ldr r0,=0x4A000018 @;SUBSRCPND
  str r1,[r0]
  ldr r0,=0x4A000000 @;SRCPND
  str r1,[r0]
  ldr r0,=0x4A000010 @;INTPND
  str r1,[r0]  
  
  
  @@;initialise system clocks
	mov	r1, #0x4C000000
	mvn	r2, #0xff000000
	str	r2, [r1, #0x00]
	
	mov	r1, #0x4C000000
	ldr	r2, =0x5
	str	r2, [r1, #0x14]

	mrc	p15, 0, r1, c1, c0, 0		@;@ read ctrl register 
	orr	r1, r1, #0xc0000000		@;@ Asynchronous  
	mcr	p15, 0, r1, c1, c0, 0		@;@ write ctrl register

	mov	r1, #0x4C000000
	                 		@;@ clock default
	ldr 	r2, =0x7f021	                     @;@mpll_value_USER 		@ clock user set
	str	r2, [r1, #0x04]
	

		

	                     
  
   mov r0, #0
   mcr p15, 0, r0, c7, c7, 0 @; /* flush v3/v4 cache */
   mcr p15, 0, r0, c8, c7, 0  @;/* flush v4 TLB */

   @;disable MMU stuff and caches
  
  
    mrc p15, 0, r0, c1, c0, 0
    bic r0, r0, #0x00002300  @;@ clear bits 13, 9:8 (--V- --RS)
    bic r0, r0, #0x00000087  @;@ clear bits 7, 2:0 (B--- -CAM)
    orr r0, r0, #0x00000002  @;@ set bit 2 (A) Align
    orr r0, r0, #0x00001000  @;@ set bit 12 (I) I-Cache
    mcr p15, 0, r0, c1, c0, 0
 
  ldr r0,=0x560000a4   @;EINTMASK
  ldr r1,=0x0
  str r1,[r0]
  
  ldr r0,=0x56000060  @;GPGCON
  ldr r1,=0xaaaaaaaa
  str r1,[r0]
  ldr r0,=0x4A00000C @;PRIORITY
  ldr r1,=0x0   @;����ת���ȼ�
   str r1,[r0]
  
  ldr r0,=0x4A000008 @;INTMSK
  ldr r0,=0x0  @;������
  str r1,[r0]   
  
  ldr r0,=0x4A00001C @;INTSUBMSK
  ldr r1,=0x0
  str r1,[r0]



	@;@ set GPIO for UART

	mov	r1, #0x56000000
	add	r1, r1, #0x70
	ldr	r2, =0x0016faaa   @;GPIO_H����ΪnCTS0��nRTS0, RXD0,TXD0, RXD1��

                                                                           @;TXD1��nCTS1��nRTS1, 
	str	r2, [r1, #0x0]
	ldr	r2, =0x000007ff
	str	r2, [r1, #0x8]	
	nop
	mov r0,#'b'

	bl PrintChar
	nop
	bl	InitUART   
	nop
	nop
	mov r0,#'u'

	bl PrintChar
	mov r0,#'a'

	bl PrintChar

	nop
        bl      LED_ON
	nop
  @this init the ram 
        bl lowlevel_init
  @end of init ram
	mov r0,#'R'

	bl PrintChar

init_nand_flash:
	
	ldr     r1,=0x56000060   @GPGCON	
	ldr	r2,[r1]
	ldr     r3,=0x03ffffff
	and     r2,r2,r3
	str	r2,[r1]
	
	
wait_nand:
	ldr r0,=0x100000
	sub r0,r0,#0x1
	cmp  r0,#0x1
	blt  wait_nand	
	ldr	sp,=0x33d00000
	mov	r0,#0x0
	ldr		r1, =0x3000   @     10_0000_0000_0000
	mov	r1, r1, LSR #11
	add		r1, r1, #1
	
	ldr		r2, =0x30000800
	
	bl		nand_read_ll
	nop
	mov       r0,#'N'
	bl        PrintChar
	mov       r1,#0x20
	nop
	bl		check_ram
        @ jump to ram
	
	nop
	
	@ldr     r2, =0x30000800
	@mov	pc, r2
	mov     r0,#'n'
	bl 	PrintChar
	
	
.global _on_the_ram
_on_the_ram:

	@ get read to call C functions
	ldr	sp, =0x33d00000	@ setup stack pointer
	mov	fp, #0			@ no previous frame, so fp=0
	mov	a2, #0			@ set argv to NULL 

	
	mov     r0,#'Z'
	bl	PrintChar
on_ram:
	bl	main			@ call main 


             
      @;Initialize UART
      @; r0 = number of UART port
 
@;@ PrintChar : prints the character in R0
@;@   r0 contains the character
.global PrintChar
PrintChar:
TXBusy:
  ldr	r1, =0x50000000
	ldr	r2, [r1, #0x10]
	and	r2, r2, #0x4
	tst	r2, #0x4
	beq	TXBusy	
	strb	r0, [r1, #0x20]
	mov	pc, lr    
	
getchar:
Rxempty:
  ldr	r1, =0x50000000
  ldr r2,[r1,#0x10]
  and r2,r2,#0x1
  tst r2,#0x1
  beq Rxempty  
  ldr r3,[r1,#0x24]
  mov pc,lr
  

@ copy vivi to RAM
check_ram:
	 @ verify
	mov     r10,lr
	mov	r4, #0x0
	ldr	r5, =0x30000800
	mov	r6, #0xf	@ 4 bytes * 1024 = 4K-bytes
go_next:
	
	ldr	r7, [r4], #4
	ldr	r8, [r5], #4
	teq	r7, r8
	bne	notmatch
	sub	r6, r6, #1
	cmp	r6,#0x1
	b       good_read	

	
	bne	go_next
notmatch:
	mov     r0,#'B'
	bl	PrintChar
	b       done_nand_read
good_read:
	mov     r0,#'G'
	bl	PrintChar
done_nand_read:

	mov	pc, r10

.global InitUART
InitUART:
	ldr	r1, =0x50000000 @;ulcon/clcon0
	mov	r2, #0x51
	str	r2, [r1, #0x08] @;fifo diable
	str	r2, [r1, #0x0C]  @;��ʹ���Զ�������
	mov	r2, #0x3
	str	r2, [r1, #0x0] @;8λ��ݣ�һλֹͣλ ��У��
	ldr	r2, =0x245
	str	r2, [r1, #0x04]  @;�жϻ��ѯ��ʽ������������״̬�жϣ��жϷ�ʽ Rx���� Tx ��ƽ ѡ��PCLK  ��Ч������

	mov	r2, #26
	str	r2, [r1, #0x28]

	mov	r3, #100        @;timedelay ʱ���ӳ�
	mov	r2, #0x1
FIN:	sub	r3, r3, #0x1
	cmp	r2, r3
	bne	FIN
  mov	pc, lr   @;���ص��ô�

@;@ All LED on
.global LED_ON
LED_ON:
	ldr r1,=0x56000010
        ldr r2,=0x55555
        str r2,[r1]
        ldr r1,=0x56000018
        ldr r2,=0xfff
        str r2,[r1]
        ldr r1,=0x56000014
        ldr r0,=0x001
        str r0,[r1]
	mov pc,lr
        
theend:
        nop 
  .align	2



@ 0x04: Undefined instruction exception

HandleUndef:
	        mov pc,lr 

@ 0x08: Software interrupt exception
HandleSWI:
			mov pc,lr 
@ 0x0c: Prefetch Abort (Instruction Fetch Memory Abort)
HandlePrefetchAbort:
			mov pc,lr 
@ 0x10: Data Access Memory Abort
HandleDataAbort:
			mov pc,lr 
@ 0x14: Not used
HandleNotUsed:
			mov pc,lr 
@ 0x18: IRQ(Interrupt Request) exception
HandleIRQ:
			 msr cpsr_c, #0xd2   @ close irq
			 sub lr, lr, #4 
             stmdb   sp!, { r0-r12,lr } 


	        mov     r0,#'\n'
	        bl 	   PrintChar
	        mov     r0,#'\r'
	        bl 	   PrintChar
	        mov     r0,#'I'
	        bl 	   PrintChar
	        mov     r0,#'R'
	        bl 	   PrintChar
	        mov     r0,#'Q'
	        bl 	   PrintChar
	        mov     r0,#'\n'
	        bl 	   PrintChar
	        mov     r0,#'\r'
	        bl 	   PrintChar
            @mov r0,lr
           @ bl irq_server

	         bl     firefly_irq_service_entry
			ldmia   sp!,    { r0-r12,pc }^

@ 0x1c: FIQ(Fast Interrupt Request) exception
HandleFIQ:
			mov r10,r14
			mov     r0,#'\n'
	        bl 	   PrintChar
	        mov     r0,#'\r'
	        bl 	   PrintChar
	        mov     r0,#'F'
	        bl 	   PrintChar
	        mov     r0,#'I'
	        bl 	   PrintChar
	        mov     r0,#'Q'
	        bl 	   PrintChar
	        mov     r0,#'\n'
	        bl 	   PrintChar
	        mov     r0,#'\r'
	        bl 	   PrintChar

			subs   PC,r10,#4

        
