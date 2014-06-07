#include <stdio.h>
#include "sched.h"
struct list_task task_run;
struct list_task task_suspend;
struct list_task task_ready;

int schedule()
{
	struct task_struct *task_select=NULL;
	if(task_run->head_task!=NULL)
		{
			task_select=task_run->head_task;
			task_ready->tail_task->next_task=task_run->head_task;
		    task_ready->tail_task = task_run->head_task;
		    task_run->head_task =  task_run->head_task->next_task;
		    task_ready->tail_task->next_task=NULL;
			
		}
   else if (task_ready->head_task!=NULL)
   	    {
   	    	task_select=task_ready->head_task;
   	    	task_run->head_task=task_ready->head_task;
   	    	task_run->tail_task  =  task_ready->tail_task;
   	    	task_ready->head_task=NULL;
   	    	task_ready->tail_task=NULL;
   	    	
   	    }
   	    
   	    if( task_select!=NULL)
   	      { 
   	      	inline void task_go_to_run( task_select	);
   	    	 return 0;
   	      }
   	   else
   	       return -1;
}

void task_go_to_run()
{}



