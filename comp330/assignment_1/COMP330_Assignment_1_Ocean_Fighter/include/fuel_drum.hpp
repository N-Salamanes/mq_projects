/* Author: Nigel Salamanes 43690599
 *         nigel.salamanes@students.mq.edu.au
 * Date:   14 Apr 2017
 *
 * fuel_drum.hpp
 *
 * contains the declarations for fuel drum
 *
 */
#ifndef FUEL_DRUM_HPP_
#define FUEL_DRUM_HPP_
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "../include/object.hpp"

class FuelDrum : public Object
{
public:
	FuelDrum(double, double);			// constructor
	~FuelDrum();						// destructor
	void update(int);					// overrided function, updates movement
	void draw();						// overrided function, draws movement

	static int get_count();				// get how many fuel drums are on the screen
	static int get_limit();				// set the limit of fuel drums allowed

	static int m_fueldrumTimer;			// time in ms since the last fuel drum was created
	static int m_fueldrumTimerThreshold;// time in ms for threshold

	void set_isOnFire(bool);			// set the fuel drum to be on fire
	bool get_isOnFire();				// get if the fuel drum is on fire
private:
	bool m_isOnFire;					// fuel drum on fire?
	DrawLayer m_fire;					// layer animation for fire
	float m_xScaleFire;					// x-scaling fire
	float m_yScaleFire;					// y-scaling fire
	int m_fireTimer;					// on fire timer in ms
	int m_fireTimerThreshold;			// on fire threshold

	int m_circleSegments;				// circle segments
	int get_circleSegments();			// get how many points the circle should have
	void set_circleSegments(int);		// set how many points the circle should have

	double xRand, yRand;				// x/y random for direction change
	double m_directionTimer;			// timer for last movement change
	double m_directionTimerThreshold;	// determines when direction should change
	double get_directionTimer();		// get the direction timer
	void set_directionTimer(double);	// set the direction timer

	static int m_fueldrumCount;			// how many fuel drums are on screen
	static int m_fueldrumLimit;			// limit on how many fuel drums allowed
};

#endif /* FUEL_DRUM_HPP_ */
