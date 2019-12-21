#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/sched.h>

asmlinkage long sys_set_nice_inc(pid_t pid, int value){

	struct task_struct *Task;
	Task = find_task_by_vpid(pid);
	
	if(value < 0){
		return -EINVAL;
	}
	
	if(Task == NULL){
		return -ESRCH; 
	}else{
		Task->nice_inc = value;
		printk(KERN_ALERT "func | sys_set_nice_inc: after value : %ld\n", Task->nice_inc);
		return 0;
	}
}
