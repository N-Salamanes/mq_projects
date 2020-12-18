/* Author: Nigel Salamanes 43690599
 *         nigel.salamanes@students.mq.edu.au
 * Date:   14 Apr 2017
 *
 * global.cpp
 *
 * contains the global functions & instances used within the program
 *
 */
#include "../include/global.hpp"

struct Globals globals;

float limit(float x, float min, float max)
{
	if (x < min) {
		x = min;
	}
	if (x > max) {
		x = max;
	}
	return x;
}

bool nearby(float x1, float y1, float x2, float y2, float distance)
{
	if ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2) < distance*distance)
	{
		return true;
	}

	return false;
}
