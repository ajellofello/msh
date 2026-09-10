#include <string.h>
#include <stdio.h>

#include "builtin.h"
#include "shell.h"

#define PROMPTSIZ 1024

int main()
{
	char* prompt;

	while ((prompt = getprompt(PROMPTSIZ)))
	{
		int shouldexit = (strcmp(prompt, "exit") == 0);
		if (shouldexit)
		{
			puts("exit");
			break;
		}
	}

	return 0;
}

