/*
 * bullet.hpp
 *
 *  Created on: 12Apr.,2017
 *      Author: Nigel
 */
#ifndef BULLET_HPP_
#define BULLET_HPP_

#include <GL/glut.h>
#include <math.h>
#include "../include/object.hpp"
#include "../include/global.hpp"

class Bullet : public Object
{
public:
	Bullet(double, double, double); 	// constructor
	~Bullet();							// destructor
	void update(int);					// overrided function, updates movement
	void draw();						// overrided function, draws the object

	static int get_count();				// get how many bullets are on the screen
	static int get_limit();				// get the limit of bullets allowed on the screen

	static int m_bulletTimer;			// time in ms since last bullet fired
	static int m_bulletTimerThreshold;	// time in ms since last bullet fired
private:
	int get_circleSegments();			// get how many points should the circle have
	void set_circleSegments(int);		// set how many points should the circle have
	int m_circleSegments;				// circle segments

	bool isOffScreen();					// check if the bullet is off screen

	static int m_bulletCount;			// bullet count
	static int m_bulletLimit;			// bullet limit
};

#endif /* BULLET_HPP_ */
