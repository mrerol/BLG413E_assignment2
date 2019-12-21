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
	int ret = getpriority(which, getpid());
	printf("Process 1 nice value: %d\n", ret);
	syscall(NR_sys_set_nice_inc, getpid(),5);
	ret = setpriority(which, getpid(), 5);
	ret = getpriority(which, getpid());
	printf("Process 1 after setting nice value: %d\n", ret);
	printf("-----------------------\n");
	
	int pid; 
    pid = fork();
    
    if(pid == 0){ // Process 2
		
		printf("Process 2\n");
		printf("Process 2 pid: %d\n", getpid());
		process_ids[1] = getpid();
		int ret = getpriority(which, getpid());
		printf("Process 2 nice value: %d\n", ret);
		syscall(NR_sys_set_nice_inc, getpid(),5);
		printf("-----------------------\n");
		
		
		pid = fork();
		
		if(pid == 0){ // Process 3
			printf("Process 3\n");
			printf("Process 3 pid: %d\n", getpid());
			process_ids[2] = getpid();
			int ret = getpriority(which, getpid());
			printf("Process 3 nice value: %d\n", ret);
			printf("-----------------------\n");


		}
		else{ // Process 2
			
			sleep(1);
			
			pid = fork();
			
			if(pid == 0){ // Process 4
				
				printf("Process 4\n");
				printf("Process 4 pid: %d\n", getpid());
				process_ids[3] = getpid();
				int ret = getpriority(which, getpid());
				printf("Process 4 nice value: %d\n", ret);
				printf("-----------------------\n");
				
				
				kill(process_ids[0], SIGKILL);
				sleep(1);
				printf("After killing Process 1 with pid %d\n",process_ids[0]);
				int i;
				for(i = 1 ; i<4 ; i++){
					printf("Process %d\n",i+1);
					printf("Process %d pid: %d\n", i+1 ,process_ids[i]);
					int ret = getpriority(which,process_ids[i]);
					printf("Process %d nice value: %d\n", i+1, ret);
					printf("-----------------------\n");
					sleep(1);
				}
			}
			else{ // Process 2
				getchar();
			}

		}
		// Process 2
		getchar();
		
	}
	else{ // Process 1
		getchar();
	}
	
	
	return 0;
}
