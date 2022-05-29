#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
int main(void)
{
	
	

	
	pid_t child_pid = fork();
	if(child_pid>0){
		sleep(200);
	}else{
		exit(0);
	}
	
return 0;
}
