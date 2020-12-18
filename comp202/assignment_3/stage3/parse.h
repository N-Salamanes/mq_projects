/*
	Author: Nigel Salamanes, October 2016
	Student ID: 43690599
	Description: COMP202 - Assignment 3
	File Description: parse header file
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


#ifndef PARSE_H_
#define PARSE_H_

// global variables
int g_iRuleCount; // how many rules have been processed
struct StructureParse *g_structParse; // parsing information for the dmake file


struct StructureParse{
	char* Targets;			// name of the rule targets
	int TargetsCount;		// how many targets
	char** Dependencies;	// name(s) of the dependencies
	int DependenciesCount;	// how many dependencies there are
	char** Commands; 		// commands to run per rule
	int CommandsCount;		// number of commands
};


// function prototypes
void parseFile(FILE*, int);

void addRules(int, char*);
void addCommands(int, char*);

int validRules(char*, int);
int notValidCommands(char*, int);

void initStructParse();

void printInformation();

#endif





