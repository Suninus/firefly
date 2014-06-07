#include "ktype.h"
#include "mem.h"
struct globle_mem_struct  memory_map;

void firefly_mem_map_init()
{

 memory_map.kernel_mem_map.kernel_mem_size=0x1000000;
 memory_map.kernel_mem_map.kernel_start_addr=0x30000000;
 memory_map.kernel_mem_map.kernel_stack.usrsys_stack_bottom=0x340000000-0x10;
 memory_map.kernel_mem_map.kernel_stack.abort_stack_bottom=0x31000000-0x2000;
 memory_map.kernel_mem_map.kernel_stack.fiq_stack_bottom=0x31000000-0x4000;
 memory_map.kernel_mem_map.kernel_stack.irq_stack_bottom=0x31000000-0x3000;
 memory_map.kernel_mem_map.kernel_stack.supervisor_stack_bottom=0x31000000-0x1000;
 memory_map.kernel_mem_map.kernel_stack.undefined_stack_bottom=0x31000000;

 memory_map.user_mem_map.user_mem_size=0x3000000;
 memory_map.user_mem_map.user_start_addr=0x31000000;
}

void firefly_irqservice_init()
{
   memory_map.kernel_mem_map.kernel_service.abort_entry=NULL;
   /*
    * 剩下的暂时不初始化
    */
   memory_map.kernel_mem_map.kernel_service.irq_entry=0x31000000-0x4000-0x4;
}
