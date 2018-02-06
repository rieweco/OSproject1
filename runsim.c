//runsim.c
//Cody Riewerts
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
        pid_t childpid = 0;
        int i, n;
	int pr_limit;	
	int pr_count = 0;	

        if(argc != 2)
        {
                fprintf(stderr, "Usage: %s processes\n", argv[0]);
                return 1;
        }
	pr_limit = atoi(argv[1]);
	
	
	/*
        n = atoi(argv[1]);
        for(i = 1; i < n; i++)
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
