#include "2440addr.h"

int  timer_counter=0;
void openirq()
{
 __asm__ __volatile__(
   "mov r0,#0x53\n"        
   "msr cpsr_c, r0\n" 
   );
 x_printf("open irq \n");
    /* set fiq svc*/
}

void irqInit()
{
    /*clear the irq */
    int tmp;
    readtimer_0();

    rINTMSK = 0xffffffff;  /* mask all irq*/
  	rINTSUBMSK = 0xffffffff; /*mask all sub irq*/
  	rSRCPND = 0xffffffff;  /*清除源挂起寄存器*/
  	rINTPND = 0xffffffff;   /*清除中断挂起寄存器*/
    //rINTMOD = 0xffffffff;   /*中断模式 设置为FIQ*/
       /*outside irq init*/
    rEINTMASK= ~(1<<8|1<<11|1<<13|1<<14|1<<15|1<<19); /*the irq num 8,11,13,14,15,19*/
    rEINTPEND = 0xffffffff;

    rINTMSK  = ~(1<<10|1<<11|1<<12|1<<13|1<<14);   /*open timer0 irq service*/
	 rPRIORITY =0x0;
	rSUBSRCPND =0xffffffff;

  rEINTMASK = 0x0;
  x_printf("irq rGPGCON: %x\n",rGPGCON);
  tmp = rGPGCON;
  rGPGCON = tmp|(2)|(2<<6)|(2<<10)|(2<<12)|(2<<14)|(2<<22);
  tmp = rGPGUP;

  rGPGUP = tmp&((1|1<<3|1<<5|1<<6|1<<7|1<<11)); /*上拉无效*/
  rINTSUBMSK = 0x0;

  x_printf("irq rGPGCON: %x\n",rGPGCON);
  x_printf("irq rGPGDAT: %x\n",rGPGDAT);
  x_printf("irq rGPGUP: %x\n",rGPGUP);
  x_printf("irqInit initializing\n");
}

int irq_time0()
{
    x_printf("this is the inq :%d\n",timer_counter++);
	return 0;
}


