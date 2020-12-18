/* Author: Nigel Salamanes 43690599
 *         nigel.salamanes@students.mq.edu.au
 * Date:   12 Apr 2017
 *
 * bullet.cpp
 *
 * the bullet functions
 *
 */

#include "../include/bullet.hpp"

Bullet::Bullet(double _angle, double _x, double _y)
{
	// set the starting variables for the bullet
	set_x(_x);
	set_y(_y);
	set_rotation(_angle);
	set_rotationSpeed(0.0);
	set_length(2.0);
	set_velocity(1000.0);
	set_collision(false);
	set_destroy(false);

	// increase the bullet count
	m_bulletCount++;

	// create layer(s) for an object
	// * - LAYER 1 - *
	DrawLayer layer;
	// gl draw type
	layer.glType = GL_POLYGON;
	// colour
	layer.red = 1.0f;
	layer.green = 0.0f;
	layer.blue = 0.0f;
	// length
	layer.length = 2.0;
	// structure/points
	set_circleSegments(20);
	Point pt;
	for(int i = 0; i < get_circleSegments(); i++)
	{
		// copied and modified drawing circle code from:
		// http://stackoverflow.com/questions/22444450/drawing-circle-with-opengl

		float theta = 2.0f * 3.1415926f * float(i) / float(get_circleSegments());//get the current angle

		pt.x = layer.length * cosf(theta);//calculate the x component
		pt.y = layer.length * sinf(theta);//calculate the y component

		layer.structure.push_back(pt);
	}
	m_structure.push_back(layer);
}

Bullet::~Bullet()
{
	// decrement bullet count
	m_bulletCount--;
}

void Bullet::update(int v)
{
	// time elapsed minus time since last call
	int delta_t = globals.time - v;

	// if the bullet is off the screen, set it to be destroyed
	if (isOffScreen() == true)
	{
		set_destroy(true);
	}

	double movement_size = get_velocity() * DELTA_TIME;

	add_x(movement_size * cos(get_rotationInRadians()));
	add_y(movement_size * sin(get_rotationInRadians()));
}

void Bullet::draw()
{
	for (unsigned int i = 0; i < m_structure.size(); i++)
	{
		// set the matrix mode
		glMatrixMode(GL_MODELVIEW);
		// load identity
		glLoadIdentity();
		// translate the x and y position
		glTranslatef(get_x(), get_y(), 0.0);
		// Then rotation about the [Z] axis
		glRotatef(get_rotation(), 0.0, 0.0, 1.0);
		// Then scaling to the desired size
		glScalef(m_structure[i].length, m_structure[i].length, 0);
		// set the color
		glColor3f(m_structure[i].red, m_structure[i].green, m_structure[i].blue);

		// begin drawing
		glBegin(m_structure[i].glType);
			// begin drawing given points
			for (unsigned int j = 0; j < m_structure[i].structure.size(); j++)
			{
				glVertex2f(m_structure[i].structure[j].x, m_structure[i].structure[j].y);
			}
		// end drawing
		glEnd();

		glFlush();
	}
}

int Bullet::m_bulletCount = 0;
int Bullet::get_count()
{
	return m_bulletCount;
}

int Bullet::m_bulletLimit = 3;
int Bullet::get_limit()
{
	return m_bulletLimit;
}

int Bullet::m_bulletTimer = 250; // 250 so we can shoot a bullet straight away
int Bullet::m_bulletTimerThreshold = 250; // 250 so we can shoot a bullet straight away

int Bullet::get_circleSegments()
{
	return m_circleSegments;
}

void Bullet::set_circleSegments(int _segments)
{
	m_circleSegments = _segments;
}

bool Bullet::isOffScreen()
{
	if (get_x() > SCREEN_WIDTH)
	{
		return true;
	}
	if (get_x() < 0)
	{
		return true;
	}
	if (get_y() > SCREEN_HEIGHT)
	{
		return true;
	}
	if (get_y() < 0)
	{
		return true;
	}

	return false;
}


