/*
	Author: Nigel Salamanes, October 2016
	Student ID: 43690599
	Description: COMP202 - Assignment 3
	File Description: contains reading and parsing functions
*/


// user defined headers
#include "parse.h"


// main parse
void parseFile(struct Structure *oStruct, FILE *pInFile, int printInfo){
	// this will control how to process the line
	int iLineControl = -1;
	// how many rules have been processed
	int rule_count = 0;
	// see if we have a rule before commands
	int rulesBeforeCommand = NO;
	// counts how many lines have been processed
	int line_count = 1;
	// the size of the struct
	int structSize = 1;
	

	// do an infinite loop until EOF is reached
	while (INFINITE_LOOP){

		// get and test the next character
		int nextChar = fgetc(pInFile);
		
		// check and see if the next character was successful or if the EOF was reached
		if(nextChar != EOF){
			// NOT! THE END OF FILE!
			// put the retrieved character back into the stream

			// set the line control switch
			if (isalpha(nextChar)){
				// first character is alpha-numeric, it must be a rule
				iLineControl = RULE_HEADER;
				
				// we have a rule so commands may follow
				rulesBeforeCommand = YES;
			}
			else if ((nextChar == '\t') || (nextChar == ' ')){
				iLineControl = COMMAND_LINES;
				
				// remove white space characters
				while((nextChar == '\t') || (nextChar == ' ')){
					nextChar = fgetc(pInFile);
				}
				
				// set iLineControl accordingly depending on what is after these white spaces
				if (nextChar == '#'){
					// detect if white space is preceeded by a comment tag '#'
					iLineControl = COMMENTS;
				}
				if (nextChar == '\n'){
					// detect if white space is preceeded by a comment tag '#'
					iLineControl = NEW_LINE;
				}
			}
			else if (nextChar == '\n'){
				// if its a new line char, skip it
				iLineControl = NEW_LINE;
			}
			else if (nextChar == '#'){
				// its a comment
				iLineControl = COMMENTS;
			}
			else{
				// it should never reach here though!!!
			}
			
			// put back the last character
			ungetc(nextChar, pInFile);
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
		
		if (read = getline(&line, &length, pInFile) != -1){
			
			// switch depending on the first character of the line
			switch(iLineControl){
				// its a rule, target/dependencies
				case RULE_HEADER:
					// check: The dmake file has a syntax error - no colon in the dependency line.
					if (validRules(line, line_count) == NO){
						exit(1);
					}
					
					if (rule_count == structSize){
						structSize *= 2;
						// allocate more memory for the structure and init
						oStruct = (struct Structure*) realloc(oStruct, (structSize) * sizeof(struct Structure));;
						initStructure(&oStruct[rule_count]);
					}
					
					// add rules, (TARGET/DEPENDENCIES)
					addRules(&oStruct[rule_count], line);
					
					// increase the rule count
					rule_count++;
					
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
					addCommands(&oStruct[rule_count - 1], line);
					
					break;
				case COMMENTS:
					// do nothing, skip this read line from the stream
					break;
				case NEW_LINE:
					// do nothing, skip this read line from the stream
					break;
				default:
					printf("ERROR! Invalid iLineControl. Exiting.\n");
					exit(1);
			}
		}
		
		line_count++;
	}// do an infinite loop until EOF is reached
	
	// close the file
	fclose(pInFile);
	
	// if we need to print information
	if (printInfo){
		// print information
		if (rule_count > 0){
			printInformation(oStruct, rule_count);
		}
	}
}


// add commands
void addCommands(struct Structure *_oStruct, char *line){
	// things to look for to break up the string
	const char delimiters[] = "\n";
	
	//extracted bits for commands
	char *token;
	token = strsep(&line, delimiters);
	
	// allocate more memory for the list of commands
	_oStruct->Commands = (char**)realloc(_oStruct->Commands, 65535);
	// set the command
	_oStruct->Commands[_oStruct->CommandsCount] = token;
	// increase commands count
	_oStruct->CommandsCount++;
}


// add rules, Target and Dependencies
void addRules(struct Structure *_oStruct, char *line){
	
	// duplicate line* so that we dont modify the original
	char *new_line;
	new_line = strdup(line);
	
	// things to look for to break up the string
	const char delimiters[] = " :\n";
	
	//extracted bits
	char *token;
	
	// these control whether a target has been set
	int targetControl = NO;

	while(token){
		// get the next token
		token = strsep(&new_line, delimiters);
		
		// if token is not null AND token's first character is a printable character
		if ((token != NULL) && (isprint(token[0]))){
			
			if (targetControl == NO){
				// its the TARGET
				targetControl = YES;
				//allocate memory for the target
				_oStruct->Targets = (char*)malloc(strlen(token));
				// increase target count
				_oStruct->TargetsCount++;
				// add target to the stucture
				_oStruct->Targets = token;
			}
			else{
				// its the dependencies
				//printf("DEP COUNT: %i, STRLEN(%i)\n",_oStruct->DependenciesCount, strlen(token));
				// allocate more memory for the list of dependencies
				_oStruct->Dependencies = (char**)realloc(_oStruct->Dependencies, 65535);
				// set the token
				_oStruct->Dependencies[_oStruct->DependenciesCount] = token;
				// increase dependencies count
				_oStruct->DependenciesCount++;
			}
		}
	}
}

// check if rules are valid
int validRules(char *line, int count){
	int i;
	
	// go through the string and check if it contains a colon
	for (i = 0; i < strlen(line); i++){
		if (line[i] == ':'){
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
		countLength = sprintf(strCount, "%i", count);
	}
	
	// things to print to stderr
	
	// error message to print out
	char *errMsg;
	char *errMsgTemplate = "Syntax error at line : Expected colon separator in rule header:\n";
	
	// allocate the size of the error messsage
	errMsg = (char*)malloc(strlen(errMsgTemplate) + countLength);
	
	// store the error message
	sprintf(errMsg, "Syntax error at line %i: Expected colon separator in rule header:\n", count);
	
	// print the error output to stderr
	fprintf(stderr, errMsg);
	fprintf(stderr, line);
	
	return NO;
}

// command not valid, print to stderr
int notValidCommands(char *line, int count){
	
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
		countLength = sprintf(strCount, "%i", count);
	}
	
	// things to print to stderr
	
	// the error message
	char *errMsg;
	char *errMsgTemplate = "Syntax error at line : Unexpected command without rule header:\n";
	
	// allocate the size of the error message
	errMsg = (char*)malloc(strlen(errMsgTemplate) + countLength);
	// store the error message
	sprintf(errMsg, "Syntax error at line %i: Unexpected command without rule header:\n", count);
	// print the error message
	fprintf(stderr, errMsg);
	
	// the line message
	char lineMsg[strlen(line)];	
	
	// format and print the incorrect line message
	sprintf(lineMsg, "	%s", line);
	fprintf(stderr, lineMsg);
	
	return NO;
}


// initalise certain variables
void initStructure(struct Structure *_oStruct){
	_oStruct->TargetsCount = 0;
	_oStruct->DependenciesCount = 0;
	_oStruct->CommandsCount = 0;
}


// print information
void printInformation(struct Structure *_struct, int ruleCount){
	
	// print out the rules and commands
	int currentStruct = 0;
	for (currentStruct; currentStruct < ruleCount; currentStruct++){
		// print out the rules
		printf("Rule %i:\n", currentStruct+1);
		
		// print out targets
		printf("    Targets:      ");
		int targetCount = 0;
		for (targetCount; targetCount < _struct[currentStruct].TargetsCount; targetCount++){
			printf("%s", _struct[currentStruct].Targets);
		}
		
		// new line to start dependencies
		printf("\n");
		
		printf("    Dependencies: ");
		int dependenciesCount = 0;
		for (dependenciesCount; dependenciesCount < _struct[currentStruct].DependenciesCount; dependenciesCount++){
			if (dependenciesCount > 0){
				// multiple dependencies
				printf(", %s", _struct[currentStruct].Dependencies[dependenciesCount]);
			}
			else{
				// only 1 dependencies
				printf("%s", _struct[currentStruct].Dependencies[dependenciesCount]);
			}
		}
		
		// new line to start commands (if any)
		printf("\n");
		
		// check if there are any associated commands
		if (_struct[currentStruct].CommandsCount > 0){
			printf("Commands:\n");
			int commandsCount = 0;
			for (commandsCount; commandsCount < _struct[currentStruct].CommandsCount; commandsCount++){
				printf("    %s\n", _struct[currentStruct].Commands[commandsCount]);
			}
		}
		
		// new line
		printf("\n");
	}
}





