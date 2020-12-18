/* Author: Nigel Salamanes 43690599
 *		   nigel.salamanes@students.mq.edu.au
 * Date: 17 August 2016
 * 
 * this header contains the required functionality for comparing
 */

#ifndef COMPARE_H_
#define COMPARE_H_

#include <string.h>
#include "mystruct.h"

 //compare function (following the sorting order)
int compare (const void * a, const void * b){
	struct myStruct * const *p_a = a;
	struct myStruct * const *p_b = b;
	
	//caption in descending order.
	if ((*p_a)->caption > (*p_b)->caption){
		return -1;
	}
	if ((*p_a)->caption < (*p_b)->caption){
		return 1;
	}
	//hot in ascending order. 
	if ((*p_a)->hot > (*p_b)->hot){
		return 1;
	}
	if ((*p_a)->hot < (*p_b)->hot){
		return -1;
	}
	//tin in ascending order. 
	if ((*p_a)->tin > (*p_b)->tin){
		return 1;
	}
	if ((*p_a)->tin < (*p_b)->tin){
		return -1;
	}
	//degree in descending order. 
	if ((*p_a)->degree > (*p_b)->degree){
		return -1;
	}
	if ((*p_a)->degree < (*p_b)->degree){
		return 1;
	}
	//prison in ascending order. 
	if ((*p_a)->prison > (*p_b)->prison){
		return 1;
	}
	if ((*p_a)->prison < (*p_b)->prison){
		return -1;
	}
	//act in descending order. 
	if ((*p_a)->act > (*p_b)->act){
		return -1;
	}
	if ((*p_a)->act < (*p_b)->act){
		return 1;
	}
	//quarter in descending order.
	if ((*p_a)->quarter > (*p_b)->quarter){
		return -1;
	}
	if ((*p_a)->quarter < (*p_b)->quarter){
		return 1;
	}
	//knife in ascending order. 
	if ((*p_a)->knife > (*p_b)->knife){
		return 1;
	}
	if ((*p_a)->knife < (*p_b)->knife){
		return -1;
	}
	//mitten in ascending order. 
	if ((*p_a)->mitten > (*p_b)->mitten){
		return 1;
	}
	if ((*p_a)->mitten < (*p_b)->mitten){
		return -1;
	}
	//blade in ascending order. 
	if ((*p_a)->blade > (*p_b)->blade){
		return 1;
	}
	if ((*p_a)->blade < (*p_b)->blade){
		return -1;
	}
	//ear in ascending order. 
	if ((*p_a)->ear > (*p_b)->ear){
		return 1;
	}
	if ((*p_a)->ear < (*p_b)->ear){
		return -1;
	}
	//afternoon in descending order.
	if ((*p_a)->afternoon > (*p_b)->afternoon){
		return -1;
	}
	if ((*p_a)->afternoon < (*p_b)->afternoon){
		return 1;
	}
	//flag in ascending order. 
	if ((*p_a)->flag > (*p_b)->flag){
		return 1;
	}
	if ((*p_a)->flag < (*p_b)->flag){
		return -1;
	}
	//grade in descending order. 
	if ((*p_a)->grade > (*p_b)->grade){
		return -1;
	}
	if ((*p_a)->grade < (*p_b)->grade){
		return 1;
	}
	//ship in descending order. 
	if ((*p_a)->ship > (*p_b)->ship){
		return -1;
	}
	if ((*p_a)->ship < (*p_b)->ship){
		return 1;
	}
	//zinc in descending order. 
	if (strcmp((*p_a)->zinc, (*p_b)->zinc) > 0){
		return -1;
	}
	if (strcmp((*p_a)->zinc, (*p_b)->zinc) < 0){
		return 1;
	}
	//angle in ascending order. 
	if ((*p_a)->angle > (*p_b)->angle){
		return 1;
	}
	if ((*p_a)->angle < (*p_b)->angle){
		return -1;
	}
	
	//if it hits here, the struct is equivalent
	return 0;
}

#endif