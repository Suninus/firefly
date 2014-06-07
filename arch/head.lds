
OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)
SECTIONS
{
	
	. = ALIGN(4);
	.init 0x0 : 
	{
		
	. = ALIGN(4);
               mini2440.o(.text);
	       lowlevel_init.o(.text);
               nand_read.o(.text);
	       print.o(.text);
	. = ALIGN(4);
               mini2440.o(.data);
               lowlevel_init.o(.data);
	       nand_read.o(.data);
	       print.o(.data);
	. = ALIGN(4);
               mini2440.o(.bss);
               lowlevel_init.o(.bss);
	       nand_read.o(.bss);
	       print.o(.bss);
	
        }
	

}
