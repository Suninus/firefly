#include "ktype.h"
//enum
#define _STATUS _BOOL;

typedef struct task_struct {

	char    	_name[20];
	u32  		_size;
	u32		    _start_addr;
	_b32		_current_pc;
	_CPSR_REG 	_cpsr_reg;
	_STACK		_stack;	      /* _stack backup the r0-r15 and cpsr*/
	_STATUS		_status;     /* status show run or not*/

} _TASK;

typedef struct _task_list {
	_TASK	*cur_task;
 

}
