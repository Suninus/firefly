#include "type.h"
#include "irq.h"
#define rGPBUP     (*(volatile unsigned *)0x56000018)
#define rGPBDAT    (*(volatile unsigned *)0x56000014)
//extern void PrintChar(unsigned int i);
int delay(int m)
{
   int i;
  for(i=0;i<m*50;i++)
   {
      i++;
   }
   return i;
}

void main()
{
   
  /*
   * run init
   */
	init_main();
  /* register irq service*/
	firefly_irq_service_add(10,irq_server);

  /*init time*/
  inittimer();

  /* init irq */
  irqInit();

  /*open irq*/
  openirq();

     int light = 0x11,i,a=0x10;
    light = light<<1;
    int counter=0;
    int test;
    int ramdata;









     rGPBDAT = (~light)&0xff0;//第一个LED被点亮
    //delay(5000);//延时一段时间
    //主程序死循环
    

    while(1)
    {
           //从一端向另一端
           for (i=0;i<3;i++)
           {
                  light = light<<1;
                  rGPBDAT = (~light)&0xff0;
                  delay(1000);
		           x_printf("led flash 1 %x\n",rGPBDAT);
           }

           //返回
           for (i=0;i<3;i++)
           {
                  light = light>>1;
                  rGPBDAT = (~light)&0xff0;
                 delay(1000);
               x_printf("led flash 2 %x\n",rGPBDAT);
           }
        counter++;
	
Uart_SendString("\n1===========================\n");	
//led_ctl(1,1);
//led_ctl(4,1);
delay(1000);
     
x_printf("hi this is xie,the counter is :%d\n",counter);
x_printf("你好\n");
x_printf("ni hao:%s\n","谢洪刚");

Uart_SendString("\n");
Uart_SendString("2===========================\n");
     
    } 


}
