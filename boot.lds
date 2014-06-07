
OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)
SECTIONS
{
	. = 0x0;
	. = ALIGN(4);
	.init 0x0 : 
	{
		
	. = ALIGN(4);
               arch/head.o;
	}
	. += 0x30000800;
	. = ALIGN(4);
	.kernel.text : AT(ADDR(.init)+SIZEOF(.init))
	{
	  
        . = ALIGN(4);
	*(.text);
	}

        .kernel.rodata : {
          . = ALIGN(4);
           *(.rodata)
          *(.rodata.*)
       }
	 . = ALIGN(4);
	.kernel.data : {*(.data)}
        . = ALIGN(4);
	.kernel.bss : {*(.bss)}

}
