#include <stdio.h>
#include <sys/types.h> 
#include <unistd.h> 
#include <sys/resource.h>

#define NR_sys_set_nice_inc 355


int main(){
	
	printf("Process 1\n");
	printf("Process 1 pid: %d\n", getpid());
	int which = PRIO_PROCESS;
	int ret = getpriority(which, getpid());
	printf("Process 1 nice value: %d\n", ret);
	syscall(NR_sys_set_nice_inc, getpid(),10);
	ret = getpriority(which, getpid());
	printf("Process 1 nice value: %d\n", ret);
	printf("-----------------------\n");
	
	int pid; 
    pid = fork();
    
    if(pid == 0){ // Process 2
		
		printf("Process 2\n");
		printf("Process 2 pid: %d\n", getpid());
		int ret = getpriority(which, getpid());
		printf("Process 2 nice value: %d\n", ret);
		syscall(NR_sys_set_nice_inc, getpid(),5);
		//ret = getpriority(which, getpid());
		//printf("Process 2 getpriority: %d with return value: %d\n", ret, err);
		printf("-----------------------\n");
		
		
		int pid; 
		pid = fork();
		
		if(pid == 0){ // Process 3
			printf("Process 3\n");
			printf("Process 3 pid: %d\n", getpid());
			int ret = getpriority(which, getpid());
			printf("Process 3 nice value: %d\n", ret);
			printf("-----------------------\n");
			return 0;

		}
		else{ // Process 2
			
			sleep(1);
			
			int pid; 
			pid = fork();
			
			if(pid == 0){ // Process 4
				
				printf("Process 4\n");
				printf("Process 4 pid: %d\n", getpid());
				int ret = getpriority(which, getpid());
				printf("Process 4 nice value: %d\n", ret);
				printf("-----------------------\n");
				return 0;
			}
			else{ // Process 2
			}

		}
		
		
	}
	else{ // Process 1
	}
	
	getchar();
	return 0;
}
