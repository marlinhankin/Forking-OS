#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minishell.h"

	char *lookupPath(char **, char **); /*checking the input*/
	int parseCommand(char *, struct command_t *); /*takes the command and executes if successful*/
	int parsePath(char **); /*Parses Path for command*/
	void printPrompt(); /*sets up the screen*/
	void readCommand(char *buffer); /*Takes in the command that the user inputs*/
	
	
/***************************Functions**************************************************************/

int parseCommand(char *cLine, struct command_t *cmd) {
	int argc = 0;
	char **clPtr;
	/*initialization*/
	clPtr = &cLine; /*cLine is command line*/
	cmd->argv[argc] = (char *)malloc(MAX_ARG_LEN);
	/*fill argv[]*/
	while ((cmd->argv[argc] = strsep(clPtr, WHITESPACE)) != NULL) {
		cmd->argv[++argc] = (char *)malloc(MAX_ARG_LEN);
	}
	/*Set the command name and argc*/
	cmd->argc = argc - 1;
	cmd->name = (char *)malloc(sizeof(cmd->argv[0]));
	strcpy(cmd->name, cmd->argv[0]);
	return 1;
}

void printPrompt() {
	
	char dir[1024];
	getcwd(dir, sizeof(dir));
	char hostname[MAX_HOSTNAME_LEN];
	
    struct passwd *p = getpwuid(getuid());
	gethostname(hostname,MAX_HOSTNAME_LEN);
	printf("%s@%s: %s> ",p->pw_name,hostname,dir);
}


void readCommand(char *buffer)
{

    size_t bufferSize = LINE_LEN ;


    getline(&buffer,&bufferSize,stdin);

    if(bufferSize > LINE_LEN)
    {
        printf("Command line has exceed maximum number of characters\n");

    }


}

int parsePath(char** dirs) {
	int i = 0;
    char* pathEnvVar;
    char* thePath;

    for(i = 0 ; i < MAX_ARGS; i++) {
        dirs[i] = NULL;
    }
	
	i = 0;

    pathEnvVar = (char*)getenv("PATH");
    thePath = (char*)malloc(strlen(pathEnvVar) + 1);
    strcpy(thePath,pathEnvVar);
	
    dirs[i]= (char*)malloc(MAX_PATH_LEN);
    dirs[i]= strtok(thePath,":");

    while(dirs[i] != NULL)
    {
        dirs[++i] = (char*)malloc(MAX_PATH_LEN);
        dirs[i] = strtok(NULL,":");
    }

    return 0;
}

char* lookupPath(char ** argv, char ** dir) {
	int i = 0;
    char* result;
    char pName[MAX_PATH_LEN];


    if(*argv[0] == '/') {
        result = (char*)malloc(strlen(argv[0]));
        strcpy(result,argv[0]);
        return result;
    }

    while(dir[i] != NULL) {
        strcpy(pName,dir[i]);
        strcat(pName,"/");
        strcat(pName,argv[0]);

        if((access(pName,F_OK)) != -1) {
            result = (char*)malloc(strlen(pName));
            strcpy(result,pName);

            return result;
        }

        i++;
    }

    return NULL;
}
