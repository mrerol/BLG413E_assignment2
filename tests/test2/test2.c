#include <stdio.h>
#include <sys/types.h> 
#include <unistd.h> 
#include <sys/resource.h>
#include <signal.h>

#define NR_sys_set_nice_inc 355


int main(){
	
	int process_ids[4] = {0};
	
	printf("Process 1\n");
	printf("Process 1 pid: %d\n", getpid());
	process_ids[0] = getpid();
	int which = PRIO_PROCESS;
	int ret1 = getpriority(which, getpid());
	printf("Process 1 nice value: %d\n", ret1);
	syscall(NR_sys_set_nice_inc, getpid(),10);
	ret1 = setpriority(which, getpid(), 10);
	ret1 = getpriority(which, getpid());
	printf("Process 1 nice value: %d\n", ret1);
	printf("-----------------------\n");
	
	int pid; 
    pid = fork();
    
    if(pid == 0){ // Process 2
		
		printf("Process 2\n");
		printf("Process 2 pid: %d\n", getpid());
		process_ids[1] = getpid();
		int ret2 = getpriority(which, getpid());
		printf("Process 2 nice value: %d\n", ret2);
		syscall(NR_sys_set_nice_inc, getpid(),5);
		printf("-----------------------\n");
		getchar();
		
	}
	else{ // Process 1
		
		getchar();
	}
	
	
	return 0;
}

