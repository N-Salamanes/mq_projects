/* Author: Nigel Salamanes 43690599
 *         nigel.salamanes@students.mq.edu.au
 * Date:   15 Apr 2017
 *
 * fire.cpp
 *
 * the explosion functions
 *
 */
#include "../include/explosion.hpp"

Explosion::Explosion(double _x, double _y)
{
	// set the starting variables for the user
	set_x(_x);
	set_y(_y);
	set_rotation(0);
	set_rotationSpeed(0.0);
	set_length(10.0);
	set_velocity(0.0);
	set_collision(false);
	set_destroy(false);

	m_scaleFactor = 1.0;
	m_scaleInc = 1.5;
	m_scaleLimit = 1.5;

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
	layer.length = 4.5;
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

	// create layer(s) for an object
	// * - LAYER 1 - *

	// gl draw type
	layer.glType = GL_POLYGON;
	// colour
	layer.red = 0.5f;
	layer.green = 0.0f;
	layer.blue = 0.0f;
	// length
	layer.length = 2.0;
	// structure/points
	set_circleSegments(20);

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

Explosion::~Explosion(){}

void Explosion::update(int v)
{
	// time elapsed minus time since last call
	int delta_t = globals.time - v;

	m_scaleFactor += m_scaleInc * DELTA_TIME;

	if (m_scaleFactor > m_scaleLimit)
	{
		m_scaleInc = -m_scaleInc * 2;
	}
	if (m_scaleFactor < 0)
	{
		set_destroy(true);
	}
}

void Explosion::draw()
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
		glScalef(m_structure[i].length * m_scaleFactor, m_structure[i].length * m_scaleFactor, 0);
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


int Explosion::get_circleSegments()
{
	return m_circleSegments;
}

void Explosion::set_circleSegments(int _segments)
{
	m_circleSegments = _segments;
}
