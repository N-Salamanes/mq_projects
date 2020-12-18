/* Author: Nigel Salamanes 43690599
 *         nigel.salamanes@students.mq.edu.au
 * Date:   29 Mar 2017
 *
 * object.cpp
 *
 * functions for the base class objects
 *
 */
#include "../include/object.hpp"

struct Point;

Object::~Object(){}

//override function
void Object::update(int){}
//override function
void Object::draw(){}

double Object::get_x()
{
	return m_position.x;
}

void Object::set_x(double _x)
{
	m_position.x = _x;
}

void Object::add_x(double _x)
{
	m_position.x += _x;
}

double Object::get_y()
{
	return m_position.y;
}

void Object::set_y(double _y)
{
	m_position.y = _y;
}

void Object::add_y(double _y)
{
	m_position.y += _y;
}

double Object::get_rotation()
{
	return m_rotation;
}

void Object::set_rotation(double _rotation)
{
	m_rotation = _rotation;
}

double Object::get_rotationInRadians()
{
	return m_rotation * PI / 180;
}

double Object::get_rotationSpeed()
{
	return m_rotationSpeed;
}

void Object::set_rotationSpeed(double _rotationSpeed)
{
	m_rotationSpeed = _rotationSpeed;
}

double Object::get_length()
{
	return m_length;
}

void Object::set_length(double _length)
{
	m_length = _length;
}

double Object::get_velocity()
{
	return m_velocity;
}

void Object::set_velocity(double _speed)
{
	m_velocity = _speed;
}

bool Object::get_destroy()
{
	return m_destroy;
}

void Object::set_destroy(bool _destroy)
{
	m_destroy = _destroy;
}

bool Object::get_collision()
{
	return m_collision;
}

void Object::set_collision(bool _collision)
{
	m_collision = _collision;
}

