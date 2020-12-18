/*
	Author: Nigel Salamanes, October 2016
	Student ID: 43690599
	Description: COMP202 - Assignment 3
	File Description: detrules header file
*/


// system headers
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

// user defined headers
#include "parse.h"


#ifndef DETRULES_H_
#define DETRULES_H_

// global variables
struct StructureTriggerRules g_structTriggerRules;


struct StructureTriggerRules{
	int* RuleOrderList;
	int RuleOrderCount;
	char** UpdatedTargetsList;
	int UpdatedTargetsCount;
};

void determineRules(int);
void addRulesToFire(int);

void printRulesToFire();

void addUpdatedTargetsList(char*);

void initStructTriggerRules();

#endif





