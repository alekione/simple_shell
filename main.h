#ifndef MAIN_H
#define MAIN_H
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
extern char **environ;

void _free(char *(*)[], char **);
void _free2(char ***, char **);
void isexit(char *[]);
void sig_handler_child(int);
void sig_handler_parent(int);
void strjn(char **, char*);
void interactive(void);
void interactive2(char *[], char *);
bool pathexist(char *);
void stripstr(char **);
void createargv(char *(*)[], char *, char);
int processenv(char *[]);
int cd(char *);
bool isreadable(char *);
bool iswritable(char *);
bool isexecutable(char *);
void iscommand(char **, char *);
int process_file(char *);
int process_file2(char *[]);
int process_multiple(char *[]);
int complete_process_multiple(char *[], char *);
int process_other(char *[]);
bool ismore_than_onecommand(char *[]);
int execute_command(char *[]);
void process_dollar_sign(char *[]);
char *string_dollar(char **);
char *num_tostring(unsigned long int);
void _strcpy(char (*)[], char *);
int string_dollar2(int, int, char *, char **);
#endif
