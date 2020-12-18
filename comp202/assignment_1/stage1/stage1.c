/* Author: Nigel Salamanes 43690599
 *		   nigel.salamanes@students.mq.edu.au
 * Date: 5 August 2016
 */

#include <stdio.h>

#define ACT -44				/* Field act must be decimal -44  */
#define EAR 4				/* Field ear must be decimal 4 */
#define BLADE 0517			/* Field blade must be decimal number 335 converted
							to octal */
#define AFTERNOON -0.871582	/* Field afternoon must be -0.871582 */
#define ZINC "bat"			/* Field zinc must be the string "bat" */
#define DEGREE 0x67E		/* Field degree must be decimal 1662 converted
							to hexadecimal */
#define FLAG 1				/* Field flag must be 1 */
#define QUARTER 0			/* Field quarter must be 0 */
#define	TIN 0				/* Field tin must be 0 */
#define	GRADE 0				/* Field grade must be 0 */
#define	ANGLE -360.837311	/* Field angle must be -360.837311 */
#define	SHIP 037			/* Field ship must be decimal number 31 converted
							to octal */
#define	HOT	0				/* Field hot must be 0 */
#define	CAPTION	-7.871643	/* Field caption must be -7.871643 */
#define	PRISON ']'			/* Field prison must be the character ']' */
#define	MITTEN 0			/* Field mitten must be 0 */
#define	KNIFE 0xD3			/* Field knife must be decimal 211 converted
							to hexadecimal */
#define ZINC_SIZE 7

//struct definition
struct myStruct{
	char act;				/* The field called act must be a 1-byte integer */
	unsigned char ear;		/* The field called ear must be a 1-byte unsigned
							integer */
	int blade;				/* The field calld blade must be a 4-byte integer */
	double afternoon;		/* The field called afternoon must be an 8-byte
							floating point number */
	char zinc[ZINC_SIZE];			/* The field called zinc must be a fixed-length string
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
	struct myStruct oStruct = {ACT, EAR, BLADE, AFTERNOON, ZINC, DEGREE, FLAG,
	QUARTER, TIN, GRADE, ANGLE, SHIP, HOT, CAPTION, PRISON, MITTEN, KNIFE};
	
	//print out the names of the struct members
	printf("act, ear, blade, afternoon, zinc, degree, flag, quarter, tin, "
	"grade, angle, ship, hot, caption, prison, mitten, knife\n");
	
	printf("%hhx, %i, %i, %f, %s, %u, %i, %hi, %i, %hi, %f, %i, %hhi, %f, %c, %hi, %lli\n",
	oStruct.act,
	oStruct.ear,
	oStruct.blade,
	oStruct.afternoon,
	oStruct.zinc,
	oStruct.degree,
	oStruct.flag,
	oStruct.quarter,
	oStruct.tin,
	oStruct.grade,
	oStruct.angle,
	oStruct.ship,
	oStruct.hot,
	oStruct.caption,
	oStruct.prison,
	oStruct.mitten,
	oStruct.knife);
	
	return 0;
}







