/* Author: Nigel Salamanes 43690599
 *         nigel.salamanes@students.mq.edu.au
 * Date:   12 Apr 2017
 *
 * ocean.hpp
 *
 * contains the function declarations for the ocean
 *
 */
#ifndef OCEAN_HPP_
#define OCEAN_HPP_
#include <math.h>
#include "../include/global.hpp"

class Ocean
{
public:
	Ocean();			// constructor
	~Ocean();			// destructor

	void update(int);	// update the ocean color
	float get_ocean();	// get the ocean color

private:
	float m_ocean;		// ocean color
	float m_oceanInc;	// ocean increment
	float m_upperLimit;	// upper ocean color limit
	float m_lowerLimit;	// lower ocean color limit
};



#endif /* OCEAN_HPP_ */
