//testsim.c
//Cody Riewerts

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int sleepTimer = 0;
	int repeatTimer = 0;

	//if # of args is not 3
	if(argc != 3)
	{
		perror("Must be 3 Arguments!");
		return 1;
	}
	
	//set sleepTimer from 2nd argument
	sleepTimer = atoi(argv[1]);

	//set repeatTimer for 3rd argument
	repeatTimer = atoi(argv[2]);

	//error checking for argument value
	if(sleepTimer < 0)
	{
		perror("Sleep Timer must be at least 0!");
		return 1;
	}
	
	if(repeatTimer < 0)
	{
		perror("Repeat Timer must be at least 0!");
		return 1;
	}
	
	//loop for repeatTimer to set child processes to sleep
	while(repeatTimer > 0)
	{
		sleep(sleepTimer);
		perror("Process is sleeping!");
		fprintf(stderr,"PID: %ld, repeating(%d).", (long)getpid(), repeatTimer);
		//decrement
		repeatTimer--;
	}

	//print end of child process
	perror("Process has ended!");
	fprintf(stderr,"PID: %ld has ended! \n", (long)getpid());

	return 0;	
}
