/* Author: Nigel Salamanes 43690599
 *		   nigel.salamanes@students.mq.edu.au
 * Date: 17 August 2016
 */
 
#include <stdio.h>
#include <stdlib.h>
#include "compare.h"
#include "mystruct.h"

#define ARGV_EXPECTED_VALUE 3
#define ARGV_INFILE 1
#define ARGV_OUTFILE 2
#define INFINITE_LOOP 1
#define ONE_ELEMENT 1


//main program
int main(int argc, char** argv){
	//file to be read
	FILE *pInFile;
	//file to output to
	FILE *pOutFile;
	
	//check if files have been passed
	if (argc < ARGV_EXPECTED_VALUE){
		if (argc == 1){
			//no input and output file passed
			fprintf(stderr, "Please specify input and output files!\n");
		}
		if (argc == 2){
			//no output file passed
			fprintf(stderr, "Please specify output file!\n");
		}
		
		//exit with error
		return 1;
	}
	else{
		//files passed, lets see if we can read input file
		pInFile = fopen(argv[ARGV_INFILE], "rb");
		
		if (pInFile == NULL){
			fprintf(stderr, "Unable to open file!\n");
			return 1;
		}
		
		//lets see if we can write to output file
		pOutFile = fopen(argv[ARGV_OUTFILE], "wb");
		
		if (pOutFile == NULL){
			fprintf(stderr, "Unable to write to file!\n");
			return 1;
		}
	}
	
	//the current size of the struct
	unsigned int iStructSize = 1;
	
	//how many 'structs' have been used
	unsigned int iReadCount = 0;
	
	//initialise the struct
	struct myStruct *pStruct = (struct myStruct*) malloc(iStructSize * sizeof(struct myStruct));
	
	//do an infinite loop until EOF is reached
	while(INFINITE_LOOP) {
		//get and store the next character
		int next = fgetc(pInFile);
		
		//check and see if the next character was successful or if the EOF was reached
		if(next != EOF){
			//NOT! THE END OF FILE!
			//put the retrieved character back into the stream
			ungetc(next, pInFile);
		}  
		else {
			//END OF FILE!
			//quit the loop
			break;
		}
		
		//check and see if we need more memory
		if (iReadCount == iStructSize){
			//we have used up all the memory, lets allocate more
			//increase the multiplyer
			iStructSize *= 2;
			
			//reallocate memeory
			pStruct = (struct myStruct*) realloc (pStruct, iStructSize * sizeof(struct myStruct));
			
			//see if everything went okay
			if(pStruct!=NULL){
				//everyhing is okay
			}
			else{
				fprintf(stderr, "Error (re)allocating memory!\n");
			}
		}
		
		//read size of struct members from stream.
		fread(&pStruct[iReadCount].act, sizeof(pStruct[iReadCount].act), ONE_ELEMENT, pInFile);
		fread(&pStruct[iReadCount].ear, sizeof(pStruct[iReadCount].ear), ONE_ELEMENT, pInFile);
		fread(&pStruct[iReadCount].blade, sizeof(pStruct[iReadCount].blade), ONE_ELEMENT, pInFile);
		fread(&pStruct[iReadCount].afternoon, sizeof(pStruct[iReadCount].afternoon), ONE_ELEMENT, pInFile);
		fread(&pStruct[iReadCount].zinc, sizeof(pStruct[iReadCount].zinc), ONE_ELEMENT, pInFile);
		fread(&pStruct[iReadCount].degree, sizeof(pStruct[iReadCount].degree), ONE_ELEMENT, pInFile);
		fread(&pStruct[iReadCount].flag, sizeof(pStruct[iReadCount].flag), ONE_ELEMENT, pInFile);
		fread(&pStruct[iReadCount].quarter, sizeof(pStruct[iReadCount].quarter), ONE_ELEMENT, pInFile);
		fread(&pStruct[iReadCount].tin, sizeof(pStruct[iReadCount].tin), ONE_ELEMENT, pInFile);
		fread(&pStruct[iReadCount].grade, sizeof(pStruct[iReadCount].grade), ONE_ELEMENT, pInFile);
		fread(&pStruct[iReadCount].angle, sizeof(pStruct[iReadCount].angle), ONE_ELEMENT, pInFile);
		fread(&pStruct[iReadCount].ship, sizeof(pStruct[iReadCount].ship), ONE_ELEMENT, pInFile);
		fread(&pStruct[iReadCount].hot, sizeof(pStruct[iReadCount].hot), ONE_ELEMENT, pInFile);
		fread(&pStruct[iReadCount].caption, sizeof(pStruct[iReadCount].caption), ONE_ELEMENT, pInFile);
		fread(&pStruct[iReadCount].prison, sizeof(pStruct[iReadCount].prison), ONE_ELEMENT, pInFile);
		fread(&pStruct[iReadCount].mitten, sizeof(pStruct[iReadCount].mitten), ONE_ELEMENT, pInFile);
		fread(&pStruct[iReadCount].knife, sizeof(pStruct[iReadCount].knife), ONE_ELEMENT, pInFile);
		
		//increase the count
		iReadCount++;
	}
	
	//sort the elements
	qsort(pStruct, iReadCount, sizeof(struct myStruct), compare);
	
	//go through all the elements in the dynamic array
	int iWriteCount = 0;
	
	for (iWriteCount; iWriteCount < iReadCount; iWriteCount++){
		fwrite(&pStruct[iWriteCount].act, sizeof(pStruct[iWriteCount].act), ONE_ELEMENT, pOutFile);
		fwrite(&pStruct[iWriteCount].ear, sizeof(pStruct[iWriteCount].ear), ONE_ELEMENT, pOutFile);
		fwrite(&pStruct[iWriteCount].blade, sizeof(pStruct[iWriteCount].blade), ONE_ELEMENT, pOutFile);
		fwrite(&pStruct[iWriteCount].afternoon, sizeof(pStruct[iWriteCount].afternoon), ONE_ELEMENT, pOutFile);
		fwrite(&pStruct[iWriteCount].zinc, sizeof(pStruct[iWriteCount].zinc), ONE_ELEMENT, pOutFile);
		fwrite(&pStruct[iWriteCount].degree, sizeof(pStruct[iWriteCount].degree), ONE_ELEMENT, pOutFile);
		fwrite(&pStruct[iWriteCount].flag, sizeof(pStruct[iWriteCount].flag), ONE_ELEMENT, pOutFile);
		fwrite(&pStruct[iWriteCount].quarter, sizeof(pStruct[iWriteCount].quarter), ONE_ELEMENT, pOutFile);
		fwrite(&pStruct[iWriteCount].tin, sizeof(pStruct[iWriteCount].tin), ONE_ELEMENT, pOutFile);
		fwrite(&pStruct[iWriteCount].grade, sizeof(pStruct[iWriteCount].grade), ONE_ELEMENT, pOutFile);
		fwrite(&pStruct[iWriteCount].angle, sizeof(pStruct[iWriteCount].angle), ONE_ELEMENT, pOutFile);
		fwrite(&pStruct[iWriteCount].ship, sizeof(pStruct[iWriteCount].ship), ONE_ELEMENT, pOutFile);
		fwrite(&pStruct[iWriteCount].hot, sizeof(pStruct[iWriteCount].hot), ONE_ELEMENT, pOutFile);
		fwrite(&pStruct[iWriteCount].caption, sizeof(pStruct[iWriteCount].caption), ONE_ELEMENT, pOutFile);
		fwrite(&pStruct[iWriteCount].prison, sizeof(pStruct[iWriteCount].prison), ONE_ELEMENT, pOutFile);
		fwrite(&pStruct[iWriteCount].mitten, sizeof(pStruct[iWriteCount].mitten), ONE_ELEMENT, pOutFile);
		fwrite(&pStruct[iWriteCount].knife, sizeof(pStruct[iWriteCount].knife), ONE_ELEMENT, pOutFile);
	}
	
	//free the memory
	free(pStruct);
	
	//close the files
	fclose(pInFile);
	fclose(pOutFile);
	
	//exit the program
	return 0;
}



























