#include "type.h"
#include "2440addr.h"
//typedef unsigned int UINT32;
#define NF_MECC_UnLock()    {rNFCONT&=~(1<<5);}
#define NF_MECC_Lock()      {rNFCONT|=(1<<5);}

#define NF_CMD(cmd)			{rNFCMD=cmd;}
#define NF_ADDR(addr)		{rNFADDR=addr;}	
#define NF_nFCE_L()			{rNFCONT&=~(1<<1);}
#define NF_nFCE_H()			{rNFCONT|=(1<<1);}
#define NF_RSTECC()			{rNFCONT|=(1<<4);}
#define NF_RDDATA() 		(rNFDATA)
#define NF_RDDATA8() 		((*(volatile unsigned char*)0x4E000010) )

#define NF_WRDATA(data) 	{rNFDATA=data;}

#define NF_WAITRB()    		{while(!(rNFSTAT&(1<<1)));} 
	   						 //wait tWB and check F_RNB pin.
// RnB Signal
#define NF_CLEAR_RB()    	{rNFSTAT |= (1<<2);}	// Have write '1' to clear this bit.
#define NF_DETECT_RB()    	{while(!(rNFSTAT&(1<<2)));}

#define TACLS		0	// 1-clk(0ns) 
#define TWRPH0		6	// 3-clk(25ns)
#define TWRPH1		0	// 1-clk(10ns)  //TACLS+TWRPH0+TWRPH1>=50ns

static void Nand_Reset(void)
{
    volatile int i;
   
	NF_nFCE_L();
	NF_CLEAR_RB();
	for (i=0; i<10; i++);
	NF_CMD(0xFF);	//reset command
	NF_DETECT_RB();
	NF_nFCE_H();

}


static int nand_init(void)
{
	rNFCONF = (TACLS<<12)|(TWRPH0<<8)|(TWRPH1<<4)|(0<<0);	
	rNFCONT = (0<<13)|(0<<12)|(0<<10)|(0<<9)|(0<<8)|(0<<6)|(0<<5)|(1<<4)|(1<<1)|(1<<0);
	rNFSTAT = 0;
	Nand_Reset();
	return 0; /*NF8_CheckId();*/
}


int Nand_Read_UINT(UINT32 addr, UINT32 *u_buf)
{
	x_printf("in the Nand_Read_UINT\n");
	int i;
	UINT32 page=addr>>11;
       
	char buf[4];
        Nand_Reset();
 
	NF_nFCE_L();    

	NF_CLEAR_RB();
	NF_CMD(0x00);						// Read command

	NF_ADDR(addr&0xff);
	NF_ADDR((addr>>8)&0xff);
	NF_ADDR(page&0xff);
	NF_ADDR((page>>8)&0xff);
	NF_ADDR((page>>16)&0xff);
	NF_CMD(0x30);	 
	NF_DETECT_RB();	
	
       for (i = 0; i < 512; i++)	
	{
		//buffer[i] =  NF_RDDATA8();
	}
	
	NF_CMD(0x05);
	NF_ADDR(addr&0xff);
	NF_ADDR((addr>>8)&0xff);
	NF_CMD(0xE0);
	for(i=0;i<4;i++)
	   buf[i]=NF_RDDATA8();
	for(i=0;i<4;i++)
	   *u_buf=(*u_buf<<8)|buf[i];
	NF_nFCE_H();    
	
   	return 0;
}

int Nand_Read_bytes(UINT32 addr, char *u_buf,int size)
{
	x_printf("int the Nand_Read_bytes\n");
	x_printf("addr:0x%x %d\n",addr,addr);
	x_printf("read_bytes size:%d\n",size);
	int i;      
        int  rest_size=2048-(addr&0x7ff);
	x_printf("rest_size:%d 0x%x\n",rest_size,rest_size);
	int read_size=(rest_size>size)?size:rest_size;
        x_printf("read size:0x%x   %d\n",read_size,read_size);
	UINT32 page_in_addr=addr&0x7ff;
	
        UINT32 page=addr>>11;
        x_printf("page num:0x%x\n",page);
        
        
 
	
      if(page_in_addr==0)	 
         {  

        x_printf("in the 2048 page\n");
	Nand_Reset();
        NF_nFCE_L();    
	NF_CLEAR_RB();
	NF_CMD(0x00);						// Read command
	NF_ADDR(0);
	NF_ADDR(0);
	NF_ADDR(page&0xff);
	NF_ADDR((page>>8)&0xff);
	NF_ADDR((page>>16)&0xff);
	NF_CMD(0x30);
        NF_DETECT_RB();	
	
            for (i = 0; i <  read_size; i++)	
	   {
		u_buf[i] =  NF_RDDATA8();
		
	   }
 	NF_CLEAR_RB();
	NF_nFCE_H();
        }
       else
       {
        x_printf("in the littal page\n");
        Nand_Reset();
        NF_nFCE_L();    
	NF_CLEAR_RB();
	NF_CMD(0x00);						// Read command
       	NF_ADDR(0);
	NF_ADDR(0);
	NF_ADDR(page&0xff);
	NF_ADDR((page>>8)&0xff);
	NF_ADDR((page>>16)&0xff);
	NF_CMD(0x30);
        NF_DETECT_RB();	
	NF_CMD(0x05);
	NF_ADDR(page_in_addr&0xff);
	NF_ADDR((page_in_addr>>8)&0xff);
	NF_CMD(0xE0);
	  for (i = 0; i <  read_size; i++)	
	   {
		u_buf[i] =  NF_RDDATA8();
	   }
        NF_CLEAR_RB();
	NF_nFCE_H();
       }
           
	x_printf("read bytes return :%d\n",i);
	
   	return i;
}

int nand_read(char *buf,UINT32 addr,int size)
{
     nand_init();
     x_printf("int the nand_read\n");
     x_printf("buf addr:0x%x\n",buf);
     x_printf("addr:%x\n",addr);
     x_printf("size:%d 0x%x\n",size,size);
     int total_bytes=size;
     int read_bytes;
     UINT32 current_addr;
     if(size<=0)
       {
	 x_printf("bad size\n");
         return 0;
       }
     for(current_addr=addr;size>0;)
	{
           
          read_bytes=Nand_Read_bytes(current_addr,buf,size);
	  if(read_bytes==0)
		return total_bytes-size;
	  size-=read_bytes;
	 x_printf("size is :%d 0x%x\n",size,size);
	 x_printf("read_bytes:%d\n",read_bytes);
	  current_addr=current_addr+read_bytes;
         x_printf("current_addr:0x%x\n",current_addr);
         buf+=read_bytes;
	}
     return total_bytes-size;
}






int Erase_Nand_Flash(int page)
{
	x_printf("erase page is %d\n",page);
	UINT8 state;
        Nand_Reset();
 
	NF_nFCE_L();    

	NF_CLEAR_RB();
	NF_CMD(0x60);
	
	NF_ADDR(page&0xff);
	NF_ADDR((page>>8)&0xff);
	NF_ADDR((page>>16)&0xff);
	NF_CMD(0xD0);
	
	 
	NF_DETECT_RB();	
	NF_CMD(70);
	state =  NF_RDDATA8();	
	NF_nFCE_H();    

   	return state&0x1;
  
}


int nand_write(UINT32 *buf,UINT32 addr,int size)
{
	nand_init();
	
	UINT32 page=addr>>11;
	x_printf("write page is %d\n",page);
	int i;
       int state=Erase_Nand_Flash(page);
       if(state==1)
	{
	   x_printf("error to erase the nand flash\n");
	    return 1;
	}
	nand_init();
        Nand_Reset(); 
	NF_nFCE_L();    
	NF_CLEAR_RB();

	NF_CMD(0x80);
	NF_ADDR(0x0);
	NF_ADDR(0x0);
	NF_ADDR(page&0xff);
	NF_ADDR((page>>8)&0xff);
	NF_ADDR((page>>16)&0xff);
	
	for(i=0;i<size;i++)
	{
		NF_WRDATA(buf[i]);
	}       
	
        
	NF_CMD(0x10);
	
	
	NF_DETECT_RB();	
	NF_CMD(70);
	for(i=0;i<10;i++)
         {}
	state =  NF_RDDATA8();	
       
	NF_nFCE_H();    

   	return state&0x1;
	
}
