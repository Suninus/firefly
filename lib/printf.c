#include "type.h"
#define rUTRSTAT0   (*(volatile unsigned *)0x50000010)	//UART 0 Tx/Rx status
#define rUTXH0 (*(volatile unsigned char *)0x50000020)	//UART 0 Transmission Hold

char *hex="0123456789abcdef";
int printfPC(unsigned int addr)
{
int i=7;
int a=0;

PrintChar('0');
PrintChar('x');

 while(i>-1)
{
    a=(addr >> (i*4))&0xf;
   
    if(a<10)
    CPrintChar(a+0x30);
     else 
    CPrintChar(a-10+0x41);
    i--;
}
return 0;
}




void Uart_SendByte(int data)
{
  
    
    
        if(data=='\n')
        {
            while(!(rUTRSTAT0 & 0x2));
            //Delay(1);                 //because the slow response of hyper_terminal 
            rUTXH0 = '\r';
        }
        while(!(rUTRSTAT0 & 0x2));   //Wait until THR is empty.
        //Delay(1);
        rUTXH0 = data;
          
}               

//====================================================================
void Uart_SendString(char *pt)
{
    while(*pt)
        Uart_SendByte(*pt++);
}

char *myitoa(int num,char *str,int radix)
{
 //printfPC(num);
/* 索引表 */
char index[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
unsigned unum; /* 中间变量 */
int i=0,j,k;
/* 确定unum的值 */
if(radix==10&&num<0) /* 十进制负数 */
{
unum=(unsigned)-num;
str[i++]='-';
}
else unum=(unsigned)num; /* 其他情况 */
/* 逆序 */
do
 
{
str[i++]=index[unum%(unsigned)radix];
unum/=radix;
}while(unum);
str[i]='\0';
/* 转换 */
if(str[0]=='-') k=1; /* 十进制负数 */
else k=0;
char temp;
for(j=k;j<=(i-k-1)/2;j++)
{
temp=str[j];
str[j]=str[i-j-1];
str[i-j-1]=temp;
}

return i;

}

int raise(int signum)
{
  return 0;
}

void chartohex16(UINT8 buf,char *out_buf)
{
  //x_printf("in the chartohex16\n");
  char index[]="0123456789ABCDEF";
  UINT8 char_index;
  out_buf[1]=index[buf&0xf];
  out_buf[0]=index[(buf>>4)&0xf];
}
