#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pwd.h>
#include <limits.h>

#include <sys/types.h> 
#include <sys/wait.h> 

#define LINE_LEN     80
#define MAX_ARGS     64
#define MAX_ARG_LEN  16
#define MAX_PATHS    64
#define MAX_PATH_LEN 96
#define MAX_LINE_LEN 256     /* maximum allowed line length for part number to name map file */
#define WHITESPACE   " .,\t\n"
#define MAX_HOSTNAME_LEN 64

#ifndef NULL
#define NULL
#endif

struct command_t {
	char *name;
	int argc;
	char *argv[MAX_ARGS];
};