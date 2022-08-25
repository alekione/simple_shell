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
void interactive(void);
int checkfile(char *);
int withbin(char *);
char *stripstr(char *);
#endif
