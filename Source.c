/* This is a very minimal shell. It finds an executable in the
* PATH, then loads it and executes it (using execv). Since
* it uses "." (dot) as a separator, it cannot handle file names
* like "minishell.h".
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "myFunc.h"


int main() {
	
		/* Shell initialization */
	char *lookupPath(char **, char **);
	int parseCommand(char *, struct command_t *);
	int parsePath(char **);
	void printPrompt();
	void readCommand(char *);
	int pid;
	int status;
	char** pathv =(char*)calloc(MAX_PATHS, MAX_PATH_LEN);
	struct command_t command;
	char* commandLine = (char*)malloc(LINE_LEN);
	

		parsePath(pathv); /* Get directory paths from PATH */

	while(strcmp(commandLine,"exit") != 0 ) {
		printPrompt();

		/* Read the command line and parse it */
		readCommand(commandLine);
		//...
			parseCommand(commandLine, &command);
		//...

			/* Get the full pathname for the file */
			command.name = lookupPath(command.argv, pathv);
		if (command.name == NULL && strcmp(commandLine,"exit") != 0) {
			/* Report error */
			printf("Invalid command\n");
			continue;
		}
		if(command.argv[command.argc] != NULL) {
			command.argv[command.argc] = NULL;
		}

		/* Create child and execute the command */
		if(pid = fork() == 0) {
            execv(command.name,command.argv);
        }

			/* Wait for the child to terminate */
			wait(&status);

	}

	/* Shell termination */
    exit(EXIT_SUCCESS);
}