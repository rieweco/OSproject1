//runsim.c
//Cody Riewerts
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <getopt.h>
#include "makeargv.h"
#include <errno.h>

#define MAX_CANNON 100

int main(int argc, char *argv[])
{
        pid_t childpid = 0;
	int prLimit = 0;	
	int prCount = 0;
	int opt = 0;
	char line[MAX_CANNON];
	char delimiters[] = "\t\n";
	char **myargv;

	//check for correct # of arguments
        if(argc != 3)
        {
                perror("Incorrect Number of Arguments!");
                return 1;
        }
	
	//read in options
	while((opt = getopt(argc, argv, "n:")) != -1)
	{
		switch(opt)
		{
			//set program limit
			case 'n': prLimit = atoi(optarg);
			fprintf(stderr, "limit set to: %d\n", prLimit);	
			break;
		default: perror("Incorrect Argument!");
			exit(EXIT_FAILURE);
		}
	}
	
	//read in file line by line
	while(fgets(line, MAX_CANNON - 1, stdin) != NULL)
	{	
		//if program count = limit, wait
		if(prLimit == prCount)
		{
			wait(NULL);
			prCount--;
		}
		
		fprintf(stderr, "Count: %d\n", prCount);
		prCount++;
		childpid = fork();
		
		if(childpid < 0)
		{
			perror("Program failed to fork!");
			return 1;
		}		

		if(childpid == 0)
		{
			if(makeargv(line, delimiters, &myargv) == -1)
			{
				perror("Incorrect Argument!");
			 
			}
	
			else
			{	
				fprintf(stderr, "myargv[0]: %s\n", myargv[0]);
				fprintf(stderr, "Process ID:%ld ParentID:%ld ChildID:%ld\n",
                 		(long)getpid(), (long)getppid(), (long)childpid);	
				execvp(myargv[0], &myargv[0]);
				perror("Child Process failed to execvp!");
			}
			return 1;
		}
	
		//check for closed processes 	
		if(waitpid(-1, NULL, WNOHANG) != 0)
		{
			prCount--;
		}
		
	}

	//while loop to check child processes and close them
	while(1)
	{
		childpid = wait(NULL);

		if((childpid == -1) && (errno != EINTR))
		{
			break;
		}
	}
		
	
       /* fprintf(stderr, "i:%d Process ID:%1d ParentID:%1d ChildID:%1d\n",
                 i, (long)getpid(), (long)getppid(), (long)childpid);
	*/
        return 0;
}
