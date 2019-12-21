#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/sched.h>

asmlinkage long sys_get_nice_inc(pid_t pid){
	
	struct task_struct *Task;
	Task = find_task_by_vpid(pid);
	
	if(Task == NULL){
		return -ESRCH; 
	}else{
		printk(KERN_ALERT "func | sys_get_nice_inc: after value : %ld\n", Task->nice_inc);
		return Task->nice_inc;
	}
}
