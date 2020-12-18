/*
 * plane.hpp
 *
 *  Created on: 2017-06-03
 *      Author: Nigel Salamanes
 *
 *	header file for the plane
 */

#ifndef SRC_INCLUDE_PLANE_HPP_
#define SRC_INCLUDE_PLANE_HPP_

#include <math.h>
#include <GL/glut.h>

enum Animations
{
	stopped = 0,
	takeoff = 1,
	holdingpattern = 2,
	looping = 3,
	landing = 4
};

class Plane{

public:
	friend class PlaneAnimations;

	Plane(); /* constructor */
	~Plane();

	void update(int delta_t);
	void draw();

	Animations animations;
	int stage;

	double propeller_angle;
	double propeller_speed;

	double plane_speed_fast, plane_speed_slow;
	double yaw_speed_fast, yaw_speed_slow;
	double pitch_speed;

	double yaw_angle, pitch_angle, roll_angle;
	double x, y, z;

	bool landingControl;
	bool corkscrewControl;
	double corkscrewSpeed;
	bool loopControl;
	double loopSpeed;
	double loopYaw;
private:
	int timerAnimation;
	void takeoffAnimation(int delta_t);
	void holdingpatternAnimation(int delta_t);
	void landingAnimation(int delta_t);

};

extern Plane plane;

#endif /* SRC_INCLUDE_PLANE_HPP_ */
