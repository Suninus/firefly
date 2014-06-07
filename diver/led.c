#define rGPBUP     (*(volatile unsigned *)0x56000018)
#define rGPBDAT    (*(volatile unsigned *)0x56000014)
/** lednumber 1-4,ctl 0 for off else on **/
int led_ctl(int lednumber,int ctl)
{
  
   int bits=rGPBDAT;
   if((lednumber>4)&&(lednumber<1))
      {
        Uart_SendString("bad lde number\n");
        return -1;
      }
   if(ctl!=0)
     {
	rGPBDAT=bits&(~(1<<(3+lednumber)));
     }
   else
    {
	rGPBDAT=bits|(1<<(3+lednumber));
    }

	return 0;

}


