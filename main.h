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

void sig_handler_child(int);
void sig_handler_parent(int);
char *strjn(char *, char*);
void interactive(char *[]);
bool pathexist(char *);
char *stripstr(char *);
void createargv(int, char *[], char *, char [], char);
int processenv(char *[]);
int cd (char *[]);
bool isreadable(char *);
bool iswritable(char *);
bool isexecutable(char *);
char *iscommand(char *, char *);
void process_multiple(char *[], char *[]);
int process_other(char *[], char *[]);
bool ismore_than_onecommand(char *[]);
int execute_command(char *[], char *[]);
#endif
