#include "2440addr.h"
int inittimer()
{
	int tmp;
  	rTCFG0 = 0x20f0f;
	rTCFG1 = 0x01;
	rTCNTB0 = 0xffff;
	rTCMPB0 = 0xf;
	rTCON =0x0e;  /*load reg*/
	tmp= rTCON;
	rTCON   = 0x0d; /*start timer*/
	x_printf("timer 0 initializing\n");
	return 0;

}

int readtimer_0()
{
	x_printf("\n rTCNTO0 : %x\n",rTCNTO0);
   return rTCNTO0;

}
