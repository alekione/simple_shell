#ifndef MAIN_H
#define MAIN_H
#define ARR_SIZE 250
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>

typedef struct command
{
	int argc;
	char *p_name;
	FILE *fd;
	char **env;
	char **argv1;
	char **argv2;
} command;

/*void print(char, char *, const char *);*/
/*void printarr(char **, char *);*/
/*======== shell01.c ======== */

bool iscommand(char **, command *);
bool ismultiple_command(char *[]);
void add_to_hist(char **, command *);
int _strcmp(char *, char *);

/* ======= shell02.c ======= */

void createargv(char **, char *, char, command *);
char *_strdup(char *, command *);
void strjn(char **, char *);
void stripstr(char **);
int _strlen(char *);

/* ===== shell03.c ===== */

void is_exit(int, command *);
void free_str(char **);
void free_argv(char **);
void free_half(command *);
void free_onexit(command *);

/* ======= shell04.c ======= */

int execute_command(char *[], command *);
int execute_custom(char *[], command *);

/* ====== shell05.c ====== */

int process_multiple(char *[], command *);
int process_multiple2(char *[], command *);

/*  ===== file.c ======= */

int process_file(char *, command *);
int process_file2(char *[], command *);

/* ======== dir.c ======= */

int cd(char *[], command *);

/* ========= permissions.c ======== */

bool isreadable(char *);
bool isexecutable(char *);
bool iswritable(char *);

/* ===== processenv.c ===== */

int set_env(char *, char *, command *);
int unset_env(char *, command *);
char *_getenv(char *, command *);

/* ======= main.c ====== */
void sig_handler(int);
void initialize(int, char *[], char *[], command **);
void interactive(command *);

#endif
