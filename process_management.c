/*
 ============================================================================
 Name        : process_manangment.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/wait.h>

void writeOuput(char* command, char* output) {
     FILE *fp;
     fp = fopen("output.txt","a");
     fprintf(fp,"The output of: %s : is\n",command);
     fprintf(fp,">>>>>>>>>>>>>>>\n%s<<<<<<<<<<<<<<<\n",output);
     fclose(fp);
}
int main(int argc, char *argv[]) {
        remove("output.txt");
	pid_t fpid;
	char* filename = argv[1];
	char *dya; //dynamic array
	int fd[2]; //pipe
	

	//create shared memory
	int shm_fd;
	char *name = "shared_memory";
	char *shm_base;
	char *ptr;
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
	//size of shared memory
	ftruncate(shm_fd, 4096);
	//map
	shm_base = mmap(0, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

	//fork()
	fpid = fork();
	if (fpid < 0)
		printf("error");
	else if (fpid == 0) {
		//read and store in shared memory
		char buff[255];
		FILE *fp;
		fp = fopen(filename, "r");
		ptr = shm_base;
		while (fgets(buff, 255, fp) != NULL) {
                       sprintf(ptr, "%s", buff);
                       ptr += strlen(buff);
		}
		fclose(fp);

	} else {
		dya = (char*) calloc(strlen(shm_base), sizeof(char));
		strcpy(dya, shm_base);//store in dynamic array
          

	}

	char *command = strtok(dya, "\n");
	char com1[20], com2[20];
        char readbuffer[4096];

	while (command != NULL) {
                pipe(fd);
		fpid = fork();
		if (fpid < 0)
			printf("error");
		else if (fpid == 0) {
                        //child
			strcpy(com2, " ");
                        //send to parent
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			char c[20];
			strcpy(c, command);
			char *p = strtok(c, " ");
			strcpy(com1, p);
			while (p != NULL) {
				strcat(com2, strcat(p, " "));
				p = strtok(NULL, " ");
			}
			char* argument_list[2] = { com2, NULL };
			execvp(com1, argument_list);
		} else {
                       
			wait(NULL);
                        
                        memset(readbuffer,0,4096);
			close(fd[1]);
		        read(fd[0], readbuffer, sizeof(readbuffer));
			//use given function, write to screen.
			writeOuput(command, readbuffer);

		}
		command = strtok(NULL, "\n");
         }
	return 0;
}
