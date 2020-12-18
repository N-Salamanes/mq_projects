/*
	Author: Nigel Salamanes, October 2016
	Student ID: 43690599
	Description: COMP202 - Assignment 3
	File Description: the main program
	
	
	Using dmake program template,
	Author: Len Hamey, October 2016
*/


// system headers
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// user defined headers
#include "parse.h"

// function prototypes
void printUsage();


//main function
int main(int argc, char **argv) {
	// default file to look for
	char *file_dir_name = "Dmakefile";
	// default processing stage
	int processStage = 0;
	// pointer to file to be read
	FILE *pInFile;
			
    // parse the command line using getopt.
	int opt;
	while ((opt = getopt(argc, argv, "hz:f:")) != -1) {
        switch (opt) {
			case 'f':
				// set the file to read
				file_dir_name = optarg;
				break;
			case 'z':
				// set the processing stage
				processStage = atoi(optarg);
				break;
			case 'h':
                // print out usage
                printUsage();
                exit(0);
            case '?':
                exit(1);
			default:
				exit(1);
        }
    }
	
	// try opening the file
	pInFile = fopen(file_dir_name, "r");
	if (pInFile == NULL){
		fprintf(stderr, "Error: Could not read Dmakefile\n");
		exit(1);
	}
	
	// create instance of the structure of the dmake file
	// the starting size of the struct
	int startingStructSize = 1;
	g_structParse = (struct StructureParse*) malloc((startingStructSize) * sizeof(struct StructureParse));
	
	// load the appropriate process stage
	switch(processStage){
		case 0:// processing for stage 3, executing commands
			// parse the file, dont print information
			parseFile(pInFile, NO);
			// determine which commands/rules to execute, dont print rules
			determineRules(NO);
			// execute the commands
			processCommands(NO);	
			break;
		case 1:// processing for stage 1
			// parse file and print information
			parseFile(pInFile, YES);
			break;
		case 2:// processing for stage 2
			// parse the file, dont print information
			parseFile(pInFile, NO);
			// determine which commands/rules to execute, print rules
			determineRules(YES);
			break;
		case 4:// processing for stage 3, smart way of executing commands
			// parse the file, dont print information
			parseFile(pInFile, NO);
			// determine which commands/rules to execute, dont print rules
			determineRules(NO);
			// execute the commands
			processCommands(YES);
			break;
		default:
			fprintf(stderr, "Error: No processing stage available\n");
			break;
	}
	
    exit(0);
}


// prints out the usage
void printUsage() {
    printf ("Usage: dmake [-h] [-zN] [-f file]\n");
    printf ("  -h: Print this help information.\n");
    printf ("  -zN: Perform processing for stage N.\n");
    printf ("  -f file: Read dmake rules from file.\n");
    return;
}
