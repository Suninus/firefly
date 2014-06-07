#include "type.h"
struct memPages {
 u32 pageAddr;
 u32 pageSize;
};
struct _stack_entry {
       /*stack address*/
	u32 usrsys_stack_bottom;	/*user & system*/
	u32 undefined_stack_bottom;	/*Undefined instruction exception*/
	u32 supervisor_stack_bottom;	/*serpervisor*/
	u32 abort_stack_bottom;		/*Prefetch Abort (Instruction Fetch Memory Abort)*/
	u32 irq_stack_bottom;		/*IRQ(Interrupt Request) exception*/
	u32 fiq_stack_bottom;		/*FIQ(Fast Interrupt Request) exception*/

};
struct _service_entry {
 	/*irq entrys*/
	u32 irq_entry;
	u32 fiq_entry;
	u32 reset_entry;
	u32 abort_entry;
	u32 undefined_entry;

};

struct kernel_entry_map {

    u32 kernel_start_addr;
	u32 kernel_mem_size;
	struct _stack_entry kernel_stack;
	struct _service_entry kernel_service;

};
struct user_entry_map {
       u32 user_start_addr;
       u32 user_mem_size;

};

struct globle_mem_struct {
      
     
	/*kernel space*/
	struct kernel_entry_map kernel_mem_map;
	/*system space */
	struct user_entry_map user_mem_map;
};
struct mem_table_struct {
	u32 page_pointer;
	
};









struct task_mem_struct {
unsigned long size;
unsigned int used;
unsigned int free;
struct mem_table_struct *mem_table;
struct memPages* (*allocatePages)(unsigned long size);
bool (*retrievePages)(struct memPages *pages);
};
