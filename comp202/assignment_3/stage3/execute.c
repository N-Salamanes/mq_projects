/*
	Author: Nigel Salamanes, November 2016
	Student ID: 43690599
	Description: COMP202 - Assignment 3
	File Description: executing commands based on determined rules
*/

// user defined headers
#include "execute.h"

// 
int *ErrcodeSigTerminate;
int *ErrcodeSigWarn;


void processCommands(){
	ErrcodeSigTerminate = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*ErrcodeSigTerminate = YES;
	ErrcodeSigWarn = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*ErrcodeSigWarn = YES;
	
	// execute each rule that is meant to be fired
	int RuleOrderNum;
	for (RuleOrderNum = 0; RuleOrderNum < g_structTriggerRules.RuleOrderCount; RuleOrderNum++){
		
		// go through each command of the given rule number to be fired 
		int CommandNum;
		for (CommandNum = 0; CommandNum < g_structParse[g_structTriggerRules.RuleOrderList[RuleOrderNum]].CommandsCount; CommandNum++){
			executeCommands(g_structTriggerRules.RuleOrderList[RuleOrderNum], CommandNum);
		}
	}
}


void executeCommands(int _RuleNum, int _CommandNum){
	// information about the forks
	pid_t cpid, w;
	int wstatus;
	
	// status about running commands
	int runSuccess;
	
	// flush stdout
	fflush(stdout);
	
	cpid = fork();
	if (cpid == 0){
		// its a child process
		
		// re-set the shared variables
		*ErrcodeSigWarn = YES;
		*ErrcodeSigTerminate = YES;
		
		// check if command starts with a modifer
		if ((g_structParse[_RuleNum].Commands[_CommandNum][0] == '@') ||
		(g_structParse[_RuleNum].Commands[_CommandNum][0] == '-' ) ||
		(g_structParse[_RuleNum].Commands[_CommandNum][0] == '=' ) ||
		(g_structParse[_RuleNum].Commands[_CommandNum][0] == '*' ) ||
		(g_structParse[_RuleNum].Commands[_CommandNum][0] == '&' )) {
			modifierBehaviour(g_structParse[_RuleNum].Commands[_CommandNum]);
		}
		else{
			// normal command
			write(1, g_structParse[_RuleNum].Commands[_CommandNum], strlen(g_structParse[_RuleNum].Commands[_CommandNum]));
			write(1, "\n", 1);
			
			runSuccess = execl("/bin/sh", "sh", "-c", g_structParse[_RuleNum].Commands[_CommandNum], NULL);
			_exit(1);
		}
	}
	else{
		// its a parent process
		
		// loop waiting for the child process to finish
		do {
			w = waitpid(cpid, &wstatus, WUNTRACED | WCONTINUED);
			if (w == -1){
				perror("waitpid");
				exit(EXIT_FAILURE);
			}
		
		}while(!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
		
		// if the program exited with an error
		if (wstatus == 256){
			if (*ErrcodeSigTerminate == YES){
				fprintf(stderr, "*** Exited with error %d ***\n", WIFEXITED(wstatus));
				_exit(1);
			}
			else{
				if (*ErrcodeSigWarn == YES){
					fprintf(stderr, "--- Exited with error %d (ignored) ---\n", WIFEXITED(wstatus));
				}
			}
		}
	}
}




void modifierBehaviour(char* _Command){
	// status about running commands
	int runSuccess;
	int printCommand = YES;
	int suppressStdOutCmd = NO;
	int suppressStdErrCmd = NO;
	
	// go through the first few characters and set accordingly
	int i;
	for (i = 0; i < strlen(_Command); i++){
		// if we have hit our first character
		if (isalpha(_Command[i])){
			break;
		}
		
		//go through and set the cases
		switch(_Command[i]){
			case '@':
			{
				printCommand = NO;
				break;
			}
			case '-':
			{
				*ErrcodeSigTerminate = NO;
				break;
			}
			case '=':
			{
				*ErrcodeSigTerminate = NO;
				*ErrcodeSigWarn = NO;
				break;
			}
			case '*':
			{
				suppressStdOutCmd = YES;
				break;
			}
			case '&':
			{
				suppressStdErrCmd = YES;
				break;
			}
			default:
			{
				break;
			}
		}
	}
	
	// set and run command
	char* CMD = trimString(_Command);
	if (printCommand == YES){
		write(1, CMD, strlen(CMD));
		write(1, "\n", 1);
	}
	if (suppressStdOutCmd == YES){
		freopen("/dev/null", "w", stdout);
	}
	if (suppressStdErrCmd == YES){
		freopen("/dev/null", "w", stderr);
	}
	runSuccess = execl("/bin/sh", "sh", "-c", CMD, NULL);
	_exit(1);
}

char* trimString(char* _Command){
	// command (string) to be returned
	char* newCommand;
	
	// find where to start the command
	int i;
	int startIndex = 0;
	for (i = 0; i < strlen(_Command); i++){
		// find the first alpha character
		if (isalpha(_Command[i])){
			startIndex = i;
			break;
		}
	}
	
	// allocate memory and set string for new command
	newCommand = malloc(sizeof(char) * 65535);
	strncpy(newCommand, _Command + startIndex, strlen(_Command) - startIndex);
	
	return newCommand;
}

















