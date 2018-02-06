//runsim.c
//Cody Riewerts
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <getopt.h>
#include "makeargv.h"

#define MAX_CANNON 100

int main(int argc, char* argv[])
{
        pid_t childpid = 0;
        int i;
	int pr_limit;	
	int pr_count = 0;
	int opt = 0;
	char line[MAX_CANNON];
	char delimiters[] = "\t";
	char **myargv;

        if(argc != 3)
        {
                fprintf(stderr, "Usage: %s processes\n", argv[0]);
                return 1;
        }
		
	while((opt = getopt(argc, argv, "n:")) != -1)
	{
		switch(opt)
		{
			case 'n': pr_limit = atoi(optarg);	
			break;
		default: fprintf(stderr, "Invalid Option: %s !\n", argv[0]);
			exit(EXIT_FAILURE);
		}
	}
	
	while(fgets(line, MAX_CANNON, stdin) != NULL)
	{
		
		pr_count++;
		childpid = fork();
		
		if(childpid == 0)
		{
			if(makeargv(line, delimiters, &myargv) == -1)
				//perror for no args
			{
			}
	
			else
			{ 
				execvp(myargv[0], &myargv[0]);
			}
			return 0;
		}
	
		//check for closed processes 	
		if(waitpid(-1, NULL, WNOHANG) != 0)
		{
			pr_count--;
		}
		
	}

	//while loop to check child processes and close them
	
		
		
	

	/*
        for(i = 1; i < pr_limit; i++)
        {
                if((childpid = fork()) <= 0)
                {
                        break;
                }
        }
	*/
        fprintf(stderr, "i:%d Process ID:%1d ParentID:%1d ChildID:%1d\n",
                 i, (long)getpid(), (long)getppid(), (long)childpid);

        return 0;
}
