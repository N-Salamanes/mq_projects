/*
	Author: Nigel Salamanes, October 2016
	Student ID: 43690599
	Description: COMP202 - Assignment 3
	File Description: contains determining rules to fire functions
*/

// user defined headers
#include "detrules.h"

void determineRules(int _printRuleOrder){
	
	// struct which holds information about files
	struct stat fileTargetStatus;
	// int struct which holds which rules should be ran
	initStructTriggerRules();
	
	// go in reverse, bottom to top of dmakefile
	int ruleNum;
	for (ruleNum = g_iRuleCount-1; ruleNum >= 0; ruleNum--){
		// get the targets
		char* target = g_structParse[ruleNum].Targets;
		
		// check if target exists
		if (stat(target, &fileTargetStatus) == -1){
			// FILE(TARGET) DOES NOT EXIST, add it to list of rules to fire
			addRulesToFire(ruleNum);
			// update the list of updated targets
			addUpdatedTargetsList(target);
		}
		else{
			// FILE(TARGET) DOES EXIST
			
			// checks whether rule has already been added to the list to update/fire
			int alreadyAdded = NO;
			
			// see if the target is newer than dependencies
			int dependency;
			for (dependency = 0; dependency < g_structParse[ruleNum].DependenciesCount; dependency++){
				struct stat fileDependencyStatus;
				
				// go through dependencies
				if (stat(g_structParse[ruleNum].Dependencies[dependency], &fileDependencyStatus) == -1){
					// FILE(DEPENDENCY) DOES NOT EXIST
					
					// check if the dependency is being built from previous rules
					if (alreadyAdded == NO){
						// now check whether dependency was an updated target
						int updatedTarget;
						for (updatedTarget = 0; updatedTarget < g_structTriggerRules.UpdatedTargetsCount; updatedTarget++){
							if (strcmp(g_structTriggerRules.UpdatedTargetsList[updatedTarget],
								g_structParse[ruleNum].Dependencies[dependency]) == 0){
									// strings are equal
									// dependency needs to be updated
									addRulesToFire(ruleNum);
									// update the list of updated targets
									addUpdatedTargetsList(target);
									alreadyAdded = YES;
								}
						}
					}
					
					// no dependency at all
					if (alreadyAdded == NO){
						char* errMsg;
						char *errMsgTemplate = "Error: No rule to build \n";
						// allocate the size of the error message
						errMsg = (char*)malloc(strlen(errMsgTemplate) + strlen(g_structParse[ruleNum].Dependencies[dependency]));
						// store the error message
						sprintf(errMsg, "Error: No rule to build %s\n", g_structParse[ruleNum].Dependencies[dependency]);
						fprintf(stderr, errMsg);
						
						exit(1);
					}
				}
				else{
					// FILE(DEPENDENCY) DOES EXIST
					
					if (alreadyAdded == NO){
						// calculate difference in time, target[time] - dependency[time]
						double difference = difftime(fileTargetStatus.st_mtime, fileDependencyStatus.st_mtime);
						
						if (difference > 0){
							// target is newer, do nothing
						}
						else{
							// dependency is newer
							addRulesToFire(ruleNum);
							// update the list of updated targets
							addUpdatedTargetsList(target);
							alreadyAdded = YES;
						}
					}
					
					if (alreadyAdded == NO){
						// now check whether dependency was an updated target
						int updatedTarget;
						for (updatedTarget = 0; updatedTarget < g_structTriggerRules.UpdatedTargetsCount; updatedTarget++){
							if (strcmp(g_structTriggerRules.UpdatedTargetsList[updatedTarget],
								g_structParse[ruleNum].Dependencies[dependency]) == 0){
									// strings are equal
									// dependency needs to be updated
									addRulesToFire(ruleNum);
									// update the list of updated targets
									addUpdatedTargetsList(target);
									alreadyAdded = YES;
								}
						}
					}
				}
			}// going through each dependency
		}
	}// going through rules
	
	// print out which rules to fire in order (or not)
	if (_printRuleOrder == YES){
		printRulesToFire();
	}
}


// adds rules to the list of rules to fire
void addRulesToFire(int _ruleNum){
	// increase the rule trigger count
	g_structTriggerRules.RuleOrderCount++;
	
	// allocate more memory for the size of rules to fire
	g_structTriggerRules.RuleOrderList = realloc(g_structTriggerRules.RuleOrderList,
		g_structTriggerRules.RuleOrderCount * sizeof(int));
		
	// add the rule # to the list of rules to fire, (+1) because starting index 0
	g_structTriggerRules.RuleOrderList[g_structTriggerRules.RuleOrderCount-1] = _ruleNum+1;
}

// print out which rules to fire
void printRulesToFire(){
	int i;
	for (i = 0; i < g_structTriggerRules.RuleOrderCount; i++){
		printf("Fire rule %i\n", g_structTriggerRules.RuleOrderList[i]);
	}
}


// add to the list of updated targets
void addUpdatedTargetsList(char* _target){
	g_structTriggerRules.UpdatedTargetsCount++;
	g_structTriggerRules.UpdatedTargetsList = (char**) realloc(g_structTriggerRules.UpdatedTargetsList, sizeof(char*) * strlen(_target));
	g_structTriggerRules.UpdatedTargetsList[g_structTriggerRules.UpdatedTargetsCount-1] = _target;
}

// init the struct
void initStructTriggerRules(){
	g_structTriggerRules.RuleOrderCount = 0;
	g_structTriggerRules.RuleOrderList = malloc(0);
	g_structTriggerRules.UpdatedTargetsCount = 0;
	
}



