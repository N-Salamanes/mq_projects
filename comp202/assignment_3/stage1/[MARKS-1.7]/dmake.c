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

// function prototypes
void printUsage();


// global variables
// default file to look for
char *file_dir_name = "Dmakefile";
// default processing stage
int iProcessStage = 0;


//main function
int main(int argc, char **argv) {

	// pointer to file to be read
	FILE *pInFile;
				
	int opt;
	
    // parse the command line using getopt.
    //while ((opt = getopt(argc, argv, "hz:f:")) >= 0) {
	while ((opt = getopt(argc, argv, "hz:f:")) != -1) {
        switch (opt) {
			case 'f':
				// set the file to read
				file_dir_name = optarg;
				break;
			case 'z':
				// set the processing stage
				iProcessStage = atoi(optarg);
				break;
			case 'h':
                // print out usage
                printUsage();
                exit(0);
            case '?':
                exit(1);
        }
    }
	
	// processing for stage 1
	if (iProcessStage == 1){
		// try opening the file
		pInFile = fopen(file_dir_name, "r");
		if (pInFile == NULL){
			fprintf(stderr, "Error: Could not read Dmakefile\n");
			exit(1);
		}
		
		// run debug print information
		printDebug(pInFile);
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
