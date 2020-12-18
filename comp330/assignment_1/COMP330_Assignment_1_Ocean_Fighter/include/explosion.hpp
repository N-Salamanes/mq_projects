/* Author: Nigel Salamanes 43690599
 *         nigel.salamanes@students.mq.edu.au
 * Date:   15 Apr 2017
 *
 * fire.cpp
 *
 * the explosion header, declaration
 *
 */

#ifndef EXPLOSION_HPP_
#define EXPLOSION_HPP_
#include "../include/object.hpp"

class Explosion : public Object
{
public:
	Explosion(double, double);		// constructor
	~Explosion();					// destructor
	void update(int v);				// overrided function, updates movement
	void draw();					// overrided function, draws the object
private:
	void set_circleSegments(int);	// get how many points should the circle have
	int get_circleSegments();		// set how many points should the circle have
	int m_circleSegments;			// circle segments

	double m_scaleFactor;			// explosion scale factor
	double m_scaleInc;				// explsion increment factor
	double m_scaleLimit;			// explosion scale limit
};


#endif /* EXPLOSION_HPP_ */
