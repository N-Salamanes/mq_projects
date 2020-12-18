/* Author: Nigel Salamanes 43690599
 *		   nigel.salamanes@students.mq.edu.au
 * Date: 17 August 2016
 *
 * this header contains the struct definiton
 */
 
#ifndef MYSTRUCT_H_
#define MYSTRUCT_H_
 
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

#endif