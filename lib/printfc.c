#include <stdio.h>
#include <stdarg.h>
#include "type.h"
int x_printf(const char *format,...)
{
   char buf[256];
   char *fmt=format;
   char *p;
   int counter;
   int var_int;
   char *str;
   va_list va_p;
   va_start(va_p,format);
   
   for(p=buf;*fmt;fmt++)
  {
     if((*fmt)!='%')
	{
	  *p=*fmt;
	   p++;
          continue;
	}
	fmt++;
       switch(*fmt)
	{
	     case 'd': 
			var_int=va_arg(va_p,int);
			counter=printfint(var_int,p,10);
			p=p+counter;
			break;
	     case  'x':
	     case  'X': var_int=va_arg(va_p,int);
			counter=printfint(var_int,p,16);
			p=p+counter;
			break;
			
	     case  's': str=va_arg(va_p,char*);
			while(*str)
                        {
			   *p++ = *str++;
			}
			break;
	     default: break;
		
	}
	
       
  } 
  va_end(va_p);
   
  *p=0;
  
  Uart_SendString(buf);
 
  return 0;
}

int printfint(unsigned int number,char *buf,int index)
	{
	       int counter;	
		counter=myitoa(number,buf,index);
		return counter;
	}

void printfINT(int number)
	{}
void printfUINT(unsigned int number)
	{}
void printfSTRING(char *str)
	{}

void hex_byte_dump(char *buf,int size)
{
 x_printf("in the hex_byte_dump\n");
char out_buf[3];
out_buf[2]=0;
char *p=buf;
int i;
while(size>0)
{

for(i=0;i<16;i++)
{
  chartohex16(*p,out_buf);
 Uart_SendString(out_buf);
 size--;
 p++;
}
x_printf("\n");

}


}

