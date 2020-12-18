/* Author: Nigel Salamanes 43690599
 *         nigel.salamanes@students.mq.edu.au
 * Date:   29 Mar 2017
 *
 * gameobject.hpp
 *
 * base class for objects declarations
 *
 */
#ifndef OBJECT_HPP_
#define OBJECT_HPP_
#include <GL/glut.h>
#include <vector>
#include <string>
#include "../include/global.hpp"

// holds information on each layer to draw for an object
struct DrawLayer
{
	float red, green, blue;
	GLenum glType;
	double length;
	std::vector<struct Point> structure;
};

// structure which holds x and y co-ordinates
struct Point
{
	double x;
	double y;
};

class Object
{
public:
	//destructor
	virtual ~Object();

	//functions to override
	virtual void update(int);
	virtual void draw();

	//x components
	double get_x();
	void  set_x(double);
	void  add_x(double);

	//y components
	double get_y();
	void  set_y(double);
	void  add_y(double);

	//rotation
	double get_rotation();
	void  set_rotation(double);
	double get_rotationInRadians();
	double get_rotationSpeed();
	void set_rotationSpeed(double);

	//length
	double get_length();
	void set_length(double);

	// velocity/acceleration
	double get_velocity();
	void set_velocity(double);

	// object to be removed/destroyed
	bool get_destroy();
	void set_destroy(bool);

	// collision with another object
	bool get_collision();
	void set_collision(bool);
protected:
	struct Point m_position;
	double m_rotation;
	double m_rotationSpeed;
	double m_length;
	double m_velocity;
	bool m_destroy;
	bool m_collision;

	std::vector<struct DrawLayer> m_structure;
};

#endif /* OBJECT_HPP_ */
