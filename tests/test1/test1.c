#include <stdio.h>
#include <sys/types.h> 
#include <unistd.h> 
#include <sys/resource.h>
#include <signal.h>
#include <sys/wait.h> 
#include <stdlib.h>

#define NR_sys_set_nice_inc 355
#define NR_sys_get_nice_inc 356

int main(){
	

	int which = PRIO_PROCESS;
	
	printf("Process 1\n");
	printf("Process 1: pid %d\n", getpid());
	int ret = getpriority(which, getpid());
	printf("Process 1: nice value: %d\n", ret);
	printf("Process 1: nice_inc value: %ld\n", syscall(NR_sys_get_nice_inc, getpid()));
	//syscall(NR_sys_set_nice_inc, getpid(),5);
	//ret = setpriority(which, getpid(), 5);
	//ret = getpriority(which, getpid());
	//printf("Process 1: after setting nice value: %d\n", ret);
	printf("-----------------------\n");
	
	int pid; 
    pid = fork();
    
    if(pid == 0){ // Process 2
		
		printf("Process 2\n");
		printf("Process 2: pid %d\n", getpid());
		ret = setpriority(which, getpid(), -10);
		if (ret == -1){
			printf("Permission denied!\nRun this code as root!\n");
			getchar();
			exit(0);
		}
		ret = getpriority(which, getpid());
		printf("Process 2: nice value: %d\n", ret);
		syscall(NR_sys_set_nice_inc, getpid(),5);
		printf("Process 2: nice_inc value: %ld\n", syscall(NR_sys_get_nice_inc, getpid()));
		printf("-----------------------\n");
		
		
		pid = fork();
		
		if(pid == 0){ // Process 3
	
			printf("Process 3\n");
			printf("Process 3: pid: %d\n", getpid());
			ret = getpriority(which, getpid());
			printf("Process 3: nice value: %d\n", ret);
			printf("Process 3: nice_inc value: %ld\n", syscall(NR_sys_get_nice_inc, getpid()));
			printf("-----------------------\n");
			
			sleep(6);
			
			printf("Updated Process 3\n");
			printf("Updated Process 3: pid: %d\n", getpid());
			printf("Updated Process 3: Parent Process 2 (pid: %d)\n",getppid());
			ret = getpriority(which, getpid());
			printf("Updated Process 3: nice value: %d\n", ret);
			printf("Updated Process 3: nice_inc value: %ld\n", syscall(NR_sys_get_nice_inc, getpid()));
			printf("-----------------------\n");


		}
		else{ // Process 2
			
			sleep(1);
			pid = fork();
			
			if(pid == 0){ // Process 4
							
				printf("Process 4\n");
				printf("Process 4: pid: %d\n", getpid());
				ret = getpriority(which, getpid());
				printf("Process 4: nice value: %d\n", ret);
				printf("Process 4: nice_inc value: %ld\n", syscall(NR_sys_get_nice_inc, getpid()));
				printf("-----------------------\n");	
				
				sleep(7);
				
				printf("Updated Process 4\n");
				printf("Updated Process 4: pid %d\n", getpid());
				printf("Updated Process 4: Parent Process 2 (pid: %d)\n",getppid());
				ret = getpriority(which, getpid());
				printf("Updated Process 4: nice value: %d\n", ret);
				printf("Updated Process 4: nice_inc value: %ld\n", syscall(NR_sys_get_nice_inc, getpid()));
				printf("-----------------------\n");

			}
			else{ // Process 2
				// after process 1 dead
				
				sleep(3);
				syscall(NR_sys_set_nice_inc, getppid(),2);
				
				printf("\nUpdated Process 1: new pid: %d\n", getppid());
				ret = getpriority(which, getppid());
				printf("Updated Process 1: nice value: %d\n", ret);
				printf("Updated Process 1: nice_inc value: %ld\n", syscall(NR_sys_get_nice_inc, getppid()));
				printf("-----------------------\n");
				
				printf("Updated Process 2\n");
				printf("Updated Process 2: pid: %d\n", getpid());
				printf("Updated Process 2: Parent Process 1 (pid: %d)\n",getppid());
				ret = getpriority(which, getpid());
				printf("Updated Process 2: nice value: %d\n", ret);
				printf("Updated Process 2: nice_inc value: %ld\n", syscall(NR_sys_get_nice_inc, getpid()));
				printf("-----------------------\n");
				sleep(5);
				getchar();
			}

		}
		// Process 2 
		getchar();
		
		
	}
	else{ // Process 1
		sleep(2);
		printf("Process 1 is killed!\n");
		printf("Don't quit! Ouputs will be displayed ASAP!\n\n");
		exit(0);
	}
	
	exit(0);
}
