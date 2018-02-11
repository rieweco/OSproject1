//makeargv.c
//
#include "makeargv.h"
#include <string.h>
#include <stdlib.h>

int makeargv(char *s, char *delimiters, char ***argvp)
{
	char *t;
	char *snew;
	int numtokens;
	int i;
	
	snew = s + strspn(s, delimiters);

	if((t = calloc(strlen(snew) + 1, sizeof(char))) == NULL)
	{
		* argvp = NULL;
		numtokens = -1;
	}
	else
	{
		strcpy(t, snew);
		if(strtok(t, delimiters) == NULL)
			numtokens = 0;
		else
			for(numtokens = 1; strtok(NULL, delimiters) != NULL; numtokens++)
				;
		if((*argvp = calloc(numtokens + 1, sizeof(char*))) == NULL)
		{
			free(t);
			numtokens = -1;
		}
		else
		{
			if(numtokens > 0)
			{
				strcpy(t, snew);
				**argvp = strtok(t, delimiters);
				for(i = 1; i < numtokens + 1; i++)
				{
					*((*argvp) + 1) = strtok(NULL, delimiters);
				}
			}
			else
			{
				**argvp = NULL;
				free(t);
			}
		}
	}
	return numtokens;					
}










