/*
	Author: Nigel Salamanes, November 2016
	Student ID: 43690599
	Description: COMP202 - Assignment 3
	File Description: detrules header file
*/


// system headers
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


// user defined headers
#include "detrules.h"


#ifndef EXECUTE_H_
#define EXECUTE_H_


void processCommands(int);
void executeCommands(int, int);
void modifierBehaviour(char*);
char* trimString(char*);

char* fnRename(char*);
int diffWithStat(char* _old, char* _new);
	
	
#endif
