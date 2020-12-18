/* Author: Nigel Salamanes 43690599
 *		   nigel.salamanes@students.mq.edu.au
 * Date: 12 August 2016
 */

#include <stdio.h>

#define ARGV_START 1
#define INFINITE_LOOP 1
#define ONE_ELEMENT 1

//struct definition
struct myStruct{
	char act;				/* The field called act must be a 1-byte integer */
	unsigned char ear;		/* The field called ear must be a 1-byte unsigned
							integer */
	int blade;				/* The field calld blade must be a 4-byte integer */
	double afternoon;		/* The field called afternoon must be an 8-byte
							floating point number */
	char zinc[7];			/* The field called zinc must be a fixed-length string
							of no more than 7 characters
							(including terminating nulls) */
	unsigned int degree;	/* The field called degree must be a 4-byte unsigned
							integer */
	int flag;				/* The field called flag must be a 4-byte Boolean */
	short quarter;			/* The field called quarter must be a 2-byte Boolean */
	int tin;				/* The field called tin must be a 4-byte Boolean */
	short grade;			/* The field called grade must be a 2-byte Boolean */
	float angle;			/* The field called angle must be a 4-byte floating
							point number */
	unsigned short ship;	/* The field called ship must be a 2-byte unsigned 
							integer */
	char hot;				/* The field called hot must be a 1-byte Boolean */
	float caption;			/* The field called caption must be a 4-byte floating
							point number */
	char prison;			/* The field called prison must be a 1-byte
							character */
	short mitten;			/* The field called mitten must be a 2-byte Boolean */
	unsigned long knife;	/* The field called knife must be an 8-byte unsigned
							integer */
};

//main program
int main(int argc, char** argv){
	//initialise the struct
	struct myStruct oStruct;
	
	//i-o file pointer
	FILE *pFile;
	
	//we start at 1 because 0 means there were no arguments
	int i = ARGV_START;	
	//go through the passed files and point the file pointer to it
	for (i; i < argc; i++){
		pFile = fopen(argv[i], "rb");
	}

	//check if we can open the file
	if (pFile == NULL){
		fprintf(stderr, "Unable to open file!\n");
		
		//exit the program
		return 1;
	}
	else{
		//we're in business, we can open the file
		//each read binary file has the same struct structure
		printf("act, ear, blade, afternoon, zinc, degree, flag, quarter, tin, grade, angle, ship, hot, caption, prison, mitten, knife\n");
		
		//do an infinite loop until EOF is reached
		while(INFINITE_LOOP) {
			//get and store the next character
			int next = fgetc(pFile);
			
			//check and see if the next character was successful or if the EOF was reached
			if(next != EOF){
				//NOT! THE END OF FILE!
				//put the retrieved character back into the stream
				ungetc(next, pFile);
			}  
			else {
				//END OF FILE!
				//quit the loop
				break;
			}
								
			//read size of 'act' from stream. print value with correct format
			fread(&oStruct.act, sizeof(oStruct.act), ONE_ELEMENT, pFile);
			printf("%hhx, ", oStruct.act);
			
			//read size of 'ear' from stream. print value with correct format
			fread(&oStruct.ear, sizeof(oStruct.ear), ONE_ELEMENT, pFile);
			printf("%i, ", oStruct.ear);
			
			//read size of 'blade' from stream. print value with correct format
			fread(&oStruct.blade, sizeof(oStruct.blade), ONE_ELEMENT, pFile);
			printf("%i, ", oStruct.blade);
			
			//read size of 'afternoon' from stream. print value with correct format
			fread(&oStruct.afternoon, sizeof(oStruct.afternoon), ONE_ELEMENT, pFile);
			printf("%f, ", oStruct.afternoon);
			
			//read size of 'zinc' from stream. print value with correct format
			fread(&oStruct.zinc, sizeof(oStruct.zinc), ONE_ELEMENT, pFile);
			printf("%s, ", oStruct.zinc);
			
			//read size of 'degree' from stream. print value with correct format
			fread(&oStruct.degree, sizeof(oStruct.degree), ONE_ELEMENT, pFile);
			printf("%u, ", oStruct.degree);
			
			//read size of 'flag' from stream. print value with correct format
			fread(&oStruct.flag, sizeof(oStruct.flag), ONE_ELEMENT, pFile);
			printf("%i, ", oStruct.flag);
			
			//read size of 'quarter' from stream. print value with correct format
			fread(&oStruct.quarter, sizeof(oStruct.quarter), ONE_ELEMENT, pFile);
			printf("%hi, ", oStruct.quarter);
			
			//read size of 'tin' from stream. print value with correct format
			fread(&oStruct.tin, sizeof(oStruct.tin), ONE_ELEMENT, pFile);
			printf("%i, ", oStruct.tin);
			
			//read size of 'grade' from stream. print value with correct format
			fread(&oStruct.grade, sizeof(oStruct.grade), ONE_ELEMENT, pFile);
			printf("%hi, ", oStruct.grade);
			
			//read size of 'angle' from stream. print value with correct format
			fread(&oStruct.angle, sizeof(oStruct.angle), ONE_ELEMENT, pFile);
			printf("%f, ", oStruct.angle);
			
			//read size of 'ship' from stream. print value with correct format
			fread(&oStruct.ship, sizeof(oStruct.ship), ONE_ELEMENT, pFile);
			printf("%hu, ", oStruct.ship);
			
			//read size of 'hot' from stream. print value with correct format
			fread(&oStruct.hot, sizeof(oStruct.hot), ONE_ELEMENT, pFile);
			printf("%hhi, ", oStruct.hot);
			
			//read size of 'caption' from stream. print value with correct format
			fread(&oStruct.caption, sizeof(oStruct.caption), ONE_ELEMENT, pFile);
			printf("%f, ", oStruct.caption);
			
			//read size of 'prison' from stream. print value with correct format
			fread(&oStruct.prison, sizeof(oStruct.prison), ONE_ELEMENT, pFile);
			printf("%c, ", oStruct.prison);
			
			//read size of 'mitten' from stream. print value with correct format
			fread(&oStruct.mitten, sizeof(oStruct.mitten), ONE_ELEMENT, pFile);
			printf("%hi, ", oStruct.mitten);
			
			//read size of 'knife' from stream. print value with correct format
			fread(&oStruct.knife, sizeof(oStruct.knife), ONE_ELEMENT, pFile);
			printf("%llu\n", oStruct.knife);
			
		}
	}
	
	//close the file
	fclose(pFile);
	
	//exit the program nicely
	return 0;
}
