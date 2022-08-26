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

char *strjn(char *, char*);
void interactive(char *[]);
bool pathexist(char *);
bool withbin(char *);
char *stripstr(char *);
void createargv(int, char *[], char *, char []);
bool isexit(char *[]);
int processenv(char *[]);
int cd (char *[]);
bool isreadable(char *);
bool iswritable(char *);
bool isexecutable(char *);
char *iscommand(char *, char *[]);
void process_multiple(char *[], char *[]);
void execute_command(char *[], char *[]);
#endif
