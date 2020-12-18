/*
	Author: Nigel Salamanes, November 2016
	Student ID: 43690599
	Description: COMP202 - Assignment 3
	File Description: detrules header file
*/


// system headers
#include <fcntl.h>
#include <sys/mman.h>

// user defined headers
#include "detrules.h"


#ifndef EXECUTE_H_
#define EXECUTE_H_


void processCommands(int);
void executeCommands(int, int);
void modifierBehaviour(char*);
char* trimString(char*);

int diffWithStat(char* _old, char* _new);
int newerWithStat(char* _file1, char* _file2);
	
#endif
