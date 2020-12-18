/*
	Author: Nigel Salamanes, October 2016
	Student ID: 43690599
	Description: COMP202 - Assignment 3
	File Description: contains reading and parsing functions
*/


// user defined headers
#include "parse.h"


// main parse
void parseFile(FILE *_pInFile, int _printInfo){
	// this will control how to process the line
	int lineControl = -1;
	// see if we have a rule before commands
	int rulesBeforeCommand = NO;
	// counts how many lines have been processed
	int line_count = 1;
	// the size of the struct
	int structSize = 1;
	

	// do an infinite loop until EOF is reached
	while (INFINITE_LOOP){

		// get and test the next character
		int nextChar = fgetc(_pInFile);
		
		// check and see if the next character was successful or if the EOF was reached
		if(nextChar != EOF){
			// NOT! THE END OF FILE!
			// put the retrieved character back into the stream

			// set the line control switch
			if (isalpha(nextChar)){
				// first character is alpha-numeric, it must be a rule
				lineControl = RULE_HEADER;
				
				// we have a rule so commands may follow
				rulesBeforeCommand = YES;
			}
			else if ((nextChar == '\t') || (nextChar == ' ')){
				lineControl = COMMAND_LINES;
				
				// remove white space characters
				while((nextChar == '\t') || (nextChar == ' ')){
					nextChar = fgetc(_pInFile);
				}
				
				// set lineControl accordingly depending on what is after these white spaces
				if (nextChar == '#'){
					// detect if white space is preceeded by a comment tag '#'
					lineControl = COMMENTS;
				}
				if (nextChar == '\n'){
					// detect if white space is preceeded by a comment tag '#'
					lineControl = NEW_LINE;
				}
			}
			else if (nextChar == '\n'){
				// if its a new line char, skip it
				lineControl = NEW_LINE;
			}
			else if (nextChar == '#'){
				// its a comment
				lineControl = COMMENTS;
			}
			else{
				// it should never reach here though!!!
			}
			
			// put back the last character
			ungetc(nextChar, _pInFile);
		} 
		else {
			//END OF FILE!
			//quit the loop
			break;
		}
		
		// now lets analyse and break down the file line by line
		
		// the line read (stored) and required variables
		char *line = NULL;
		size_t length = 0;
		ssize_t read;
		
		if (read = getline(&line, &length, _pInFile) != -1){
			
			// switch depending on the first character of the line
			switch(lineControl){
				// its a rule, target/dependencies
				case RULE_HEADER:
					// check: The dmake file has a syntax error - no colon in the dependency line.
					if (validRules(line, line_count) == NO){
						exit(1);
					}
					
					if (g_iRuleCount == structSize){
						structSize *= 2;
						// allocate more memory for the structure and init
						g_structParse = (struct StructureParse*) realloc(g_structParse, (structSize) * sizeof(struct StructureParse));;
						initStructParse(g_iRuleCount);
					}
					
					// add rules, (TARGET/DEPENDENCIES)
					addRules(g_iRuleCount, line);
					
					// increase the rule count
					g_iRuleCount++;
					
					break;
				// its a command line(s)
				case COMMAND_LINES:
					// check: The dmake file has a syntax error - command without rule header line
					if (rulesBeforeCommand == NO){
						notValidCommands(line, line_count);
						exit(1);
					}
					
					// add command(s) - 
					//need -1 because rule count has increased but we aren't finished with it yet
					addCommands(g_iRuleCount-1, line);
					
					break;
				case COMMENTS:
					// do nothing, skip this read line from the stream
					break;
				case NEW_LINE:
					// do nothing, skip this read line from the stream
					break;
				default:
					printf("ERROR! Invalid lineControl. Exiting.\n");
					exit(1);
			}
		}
		
		line_count++;
	}// do an infinite loop until EOF is reached
	
	// close the file
	fclose(_pInFile);
	
	// if we need to print information
	if (_printInfo){
		// print information
		if (g_iRuleCount > 0){
			printInformation();
		}
	}
}


// add commands
void addCommands(int _rule, char *_line){
	// things to look for to break up the string
	const char delimiters[] = "\n";
	
	//extracted bits for commands
	char *token;
	token = strsep(&_line, delimiters);
	
	// allocate more memory for the list of commands
	g_structParse[_rule].Commands = (char**)realloc(g_structParse[_rule].Commands, 65535);
	// set the command
	g_structParse[_rule].Commands[g_structParse[_rule].CommandsCount] = token;
	// increase commands count
	g_structParse[_rule].CommandsCount++;
}


// add rules, Target and Dependencies
void addRules(int _rule, char *_line){
	
	// things to look for to break up the string
	const char delimiters[] = " :\n";
	
	//extracted bits
	char *token;
	
	// these control whether a target has been set
	int targetControl = NO;

	while(token){
		// get the next token
		token = strsep(&_line, delimiters);
		
		// if token is not null AND token's first character is a printable character
		if ((token != NULL) && (isprint(token[0]))){
			
			if (targetControl == NO){
				// its the TARGET
				targetControl = YES;
				//allocate memory for the target
				g_structParse[_rule].Targets = (char*)malloc(strlen(token));
				// increase target count
				g_structParse[_rule].TargetsCount++;
				// add target to the stucture
				g_structParse[_rule].Targets = token;
			}
			else{
				// its the dependencies
				// allocate more memory for the list of dependencies
				g_structParse[_rule].Dependencies = (char**)realloc(g_structParse[_rule].Dependencies, 65535);
				// set the token
				g_structParse[_rule].Dependencies[g_structParse[_rule].DependenciesCount] = token;
				// increase dependencies count
				g_structParse[_rule].DependenciesCount++;
			}
		}
	}
}

// check if rules are valid
int validRules(char *_line, int _count){
	
	// go through the string and check if it contains a colon
	int i;
	for (i = 0; i < strlen(_line); i++){
		if (_line[i] == ':'){
			return YES;
		}
	}
	
	// if it gets here that means its not a valid rule
	
	// int count converted to a string
	char *strCount;
	// the size of the strCount
	int countLength = 0;
	// allocate string size
	strCount = (char*)malloc(countLength);
	
	// allocate more memory as needed
	while (countLength <= 0){		
		
		countLength++;
		strCount = (char*) realloc(strCount, countLength);
		
		// try converting the int to string
		countLength = sprintf(strCount, "%i", _count);
	}
	
	// things to print to stderr
	
	// error message to print out
	char *errMsg;
	char *errMsgTemplate = "Syntax error at line : Expected colon separator in rule header:\n";
	
	// allocate the size of the error messsage
	errMsg = (char*)malloc(strlen(errMsgTemplate) + countLength);
	
	// store the error message
	sprintf(errMsg, "Syntax error at line %i: Expected colon separator in rule header:\n", _count);
	
	// print the error output to stderr
	fprintf(stderr, errMsg);
	fprintf(stderr, _line);
	
	return NO;
}

// command not valid, print to stderr
int notValidCommands(char *_line, int _count){
	
	// int count converted to a string
	char *strCount;
	// the size of the strCount
	int countLength = 0;
	// allocate string size
	strCount = (char*)malloc(countLength);
	
	// allocate more memory as needed
	while (countLength <= 0){		
		
		countLength++;
		strCount = (char*) realloc(strCount, countLength);
		
		// try converting the int to string
		countLength = sprintf(strCount, "%i", _count);
	}
	
	// things to print to stderr
	
	// the error message
	char *errMsg;
	char *errMsgTemplate = "Syntax error at line : Unexpected command without rule header:\n";
	
	// allocate the size of the error message
	errMsg = (char*)malloc(strlen(errMsgTemplate) + countLength);
	// store the error message
	sprintf(errMsg, "Syntax error at line %i: Unexpected command without rule header:\n", _count);
	// print the error message
	fprintf(stderr, errMsg);
	
	// the line message
	char lineMsg[strlen(_line)];	
	
	// format and print the incorrect line message
	sprintf(lineMsg, "	%s", _line);
	fprintf(stderr, lineMsg);
	
	return NO;
}


// initalise certain variables
void initStructParse(int _rule){
	g_structParse[_rule].TargetsCount = 0;
	g_structParse[_rule].DependenciesCount = 0;
	g_structParse[_rule].CommandsCount = 0;
}


// print information
void printInformation(){
	
	// print out the rules and commands
	int currentStruct = 0;
	for (currentStruct; currentStruct < g_iRuleCount; currentStruct++){
		// print out the rules
		printf("Rule %i:\n", currentStruct+1);
		
		// print out targets
		printf("    Targets:      ");
		int targetCount = 0;
		for (targetCount; targetCount < g_structParse[currentStruct].TargetsCount; targetCount++){
			printf("%s", g_structParse[currentStruct].Targets);
		}
		
		// new line to start dependencies
		printf("\n");
		
		printf("    Dependencies: ");
		int dependenciesCount = 0;
		for (dependenciesCount; dependenciesCount < g_structParse[currentStruct].DependenciesCount; dependenciesCount++){
			if (dependenciesCount > 0){
				// multiple dependencies
				printf(", %s", g_structParse[currentStruct].Dependencies[dependenciesCount]);
			}
			else{
				// only 1 dependencies
				printf("%s", g_structParse[currentStruct].Dependencies[dependenciesCount]);
			}
		}
		
		// new line to start commands (if any)
		printf("\n");
		
		// check if there are any associated commands
		if (g_structParse[currentStruct].CommandsCount > 0){
			printf("Commands:\n");
			int commandsCount = 0;
			for (commandsCount; commandsCount < g_structParse[currentStruct].CommandsCount; commandsCount++){
				printf("    %s\n", g_structParse[currentStruct].Commands[commandsCount]);
			}
		}
		
		// new line
		printf("\n");
	}
}





