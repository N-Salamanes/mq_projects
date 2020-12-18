/*
	Author: Nigel Salamanes, October 2016
	Student ID: 43690599
	Description: COMP202 - Assignment 3
	File Description: debug header file
*/


// system headers
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// user defines
#define INFINITE_LOOP 1
// these are switch controls which control what to do depending on the first character
// of the line
#define RULE_HEADER 0
#define COMMAND_LINES 1
#define COMMENTS 2
#define NEW_LINE 3
// simple boolean replacements
#define YES 1
#define NO 0

#ifndef DEBUG_H_
#define DEBUG_H_

// function prototypes
int validRules(char*, int);
int notValidCommands(char*, int);
	
void printDebug(FILE*);
void printRules(char*);
void printCommands(char*);

int checkBackslash(char*);
#endif