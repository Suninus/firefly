struct fs_struct {
	unsigned long fs_type;	
};
struct file_struct {
	unsigned long file_id;
	unsigned long seek_t;
	unsigned long wrx_t;	
};

struct signal_struct {
	unsigned long msg_t;	
	
};
struct mem_struct {
	unsigned long mem_start;
	unsigned long mem_size;
    bool   mem_ready;
    unsigned long pc;
	
	
};

struct task_struct {
	volatile long state;  	 /* -1 unrunnable, 0 runnable, >0 stopped */
	void stack;               	 /*       stack      */
	char *name;
	unsigned long policy;
	unsigned long pid; 	 /*       pid         */
	struct fs_struct *fs;   	 /*      file system information */
	struct file_struct *file;	 /*      file info   */
	struct signal_struct *signal;  /*    signal   */
	struct mem_struct *memory /*    memory info  */
	struct task_struct *next_task;
};

struct list_task {
		strcut task_struct *head_task;
		strcut task_struct *cur_task;
		strcut task_struct *tail_task;
	
};

int schedule();