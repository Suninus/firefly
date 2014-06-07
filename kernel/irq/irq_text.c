#include "2440addr.h"
int counter_irq=1;
void irq_server(int pc)
{
  readtimer_0();
  x_printf("1 irq rEINTPEND: %x\n",rEINTPEND);
   x_printf("1 irq rSRCPND: %x\n",rSRCPND);
    x_printf("1 irq rINTPND: %x\n",rINTPND);

  rEINTPEND = 0xffffffff; /*清楚外部中断挂起寄存器*/
  rSRCPND = 0xffffffff;  /*清除源挂起寄存器*/
  rINTPND = 0xffffffff;   
x_printf("2 irq rEINTPEND: %x\n",rEINTPEND);
   x_printf("2 irq rSRCPND: %x\n",rSRCPND);
    x_printf("2 irq rINTPND: %x\n",rINTPND);
  //x_printf("\n");
  //printfPC(pc);
 // x_printf("\n"); 
  //x_printf("this is in irq:%d\n",counter_irq);
  //delay(100);
  x_printf("irq rGPBDAT: %x\n",rGPBDAT);
  x_printf("irq rGPGCON: %x\n",rGPGCON);
  x_printf("irq rGPGDAT: %x\n",rGPGDAT);
  x_printf("irq rGPGUP: %x\n",rGPGUP);
  
  counter_irq++;
}
