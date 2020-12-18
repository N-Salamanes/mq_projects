/*
	Author: Nigel Salamanes, November 2016
	Student ID: 43690599
	Description: COMP202 - Assignment 3
	File Description: detrules header file
*/


// system headers
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>

// user defined headers
#include "detrules.h"


#ifndef EXECUTE_H_
#define EXECUTE_H_


void processCommands();
void executeCommands(int, int);
void modifierBehaviour(char*);
char* trimString(char*);
	
	
#endif
