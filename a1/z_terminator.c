#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <ctype.h>
int main(void)
{
	
	FILE *fp;
	char pro[1000];
	char subpid[4];
	system("./z_creator &");
	printf("Zombie list: \n");
	system("ps -l");		
	fp = popen("ps  -l | grep 'Z'","r");
	if (fp != NULL){
		while (fgets(pro,1000,fp)!=NULL){
		
			strncpy(subpid,pro+17,4);
			//subpid[strlen(subpid)-1]='\0';
			//subpid[strlen(subpid)-1]='\0';
			//printf("\n");
			//printf("%s+%ld",subpid,strlen(subpid));
			if (subpid[0]!='P'){
	
				kill(atoi(subpid),SIGKILL);
			}				
		}
	pclose(fp);
	printf("updated list :\n");
	system("ps -l");
}
	return 0;
}

