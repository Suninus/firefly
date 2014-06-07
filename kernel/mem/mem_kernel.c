#include "ktype.h"
#include "mem_kernel.h"
mem_unit kernel_mem_map[12];
/*
 *map0  4    bytes
 *map1  8    bytes
 *map2  16   bytes
 *map3  32   bytes
 *map4  64   bytes
 *map5  128  bytes
 *map6  256  bytes
 *map7  512  bytes
 *map8  1024 bytes
 *map9  2048 bytes
 *map10 4096 bytes
 */
int init_kernel_mem_map()
{
   kernel_mem_map[0].startAddr=1;
   kernel_mem_map[0].endAddr=2;
   kernel_mem_map[0].size=1;
   kernel_mem_map[1].startAddr=1;
   kernel_mem_map[1].endAddr=2;
   kernel_mem_map[1].size=1;
   kernel_mem_map[2].startAddr=1;
   kernel_mem_map[2].endAddr=2;
   kernel_mem_map[2].size=1;
   kernel_mem_map[3].startAddr=1;
   kernel_mem_map[3].endAddr=2;
   kernel_mem_map[3].size=1;
   kernel_mem_map[4].startAddr=1;
   kernel_mem_map[4].endAddr=2;
   kernel_mem_map[4].size=1;
   kernel_mem_map[5].startAddr=1;
   kernel_mem_map[5].endAddr=2;
   kernel_mem_map[5].size=1;
   kernel_mem_map[6].startAddr=1;
   kernel_mem_map[6].endAddr=2;
   kernel_mem_map[6].size=1;
   kernel_mem_map[7].startAddr=1;
   kernel_mem_map[7].endAddr=2;
   kernel_mem_map[7].size=1;
   kernel_mem_map[8].startAddr=1;
   kernel_mem_map[8].endAddr=2;
   kernel_mem_map[8].size=1;
   kernel_mem_map[9].startAddr=1;
   kernel_mem_map[9].endAddr=2;
   kernel_mem_map[9].size=1;
   kernel_mem_map[10].startAddr=1;
   kernel_mem_map[10].endAddr=2;
   kernel_mem_map[10].size=1;
   kernel_mem_map[11].startAddr=1;
   kernel_mem_map[11].endAddr=2;
   kernel_mem_map[11].size=1;
   kernel_mem_map[12].startAddr=1;
   kernel_mem_map[12].endAddr=2;
   kernel_mem_map[12].size=1;


	return ok;
}


int kernelMemAlloc(int size)
{
	case :

	return size;
}

int kmalloc(int size)
{

 return size;
}
