/* Author: Nigel Salamanes 43690599
 *         nigel.salamanes@students.mq.edu.au
 * Date:   17 Apr 2017
 *
 * wake.cpp
 *
 * the wake functions
 *
 */
#include "../include/wake.hpp"
#include <iostream>//DELETE ME
Wake::Wake(double _x, double _y)
{
	// set the starting variables for the user
	set_x(_x);
	set_y(_y);
	set_rotation(0);
	set_rotationSpeed(0.0);
	set_length(3.0);
	set_velocity(0.0);
	set_collision(false);
	set_destroy(false);

	m_scaleInc = 10.00;

	m_alphaFactor = 1.0;
	m_alphaInc = 1.5;

	// create layer(s) for an object
	// * - LAYER 1 - *
	DrawLayer layer;
	// gl draw type
	layer.glType = GL_POLYGON;
	// colour
	layer.red = 1.0f;
	layer.green = 1.0f;
	layer.blue = 1.0f;
	// length
	layer.length = get_length();
	// structure/points
	set_circleSegments(8);
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

Wake::~Wake(){};

void Wake::update(int v)
{
	// time elapsed minus time since last call
	int delta_t = globals.time - v;

	// increase the length (radius)
	for (unsigned int i = 0; i < m_structure.size(); i++)
	{
		m_structure[i].length += m_scaleInc * DELTA_TIME;

	}

	// increase the alpha
	m_alphaFactor -= m_alphaInc * DELTA_TIME;
	if (m_alphaFactor <= 0)
	{
		set_destroy(true);
	}
}

void Wake::draw()
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
		// enable blending and set the color with alpha
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glColor4f(m_structure[i].red, m_structure[i].green, m_structure[i].blue, m_alphaFactor);
		// begin drawing
		glBegin(m_structure[i].glType);
			// begin drawing given points
			for (unsigned int j = 0; j < m_structure[i].structure.size(); j++)
			{
				glVertex2f(m_structure[i].structure[j].x, m_structure[i].structure[j].y);
			}
		// end drawing
		glEnd();

		// set blending back to original
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glFlush();
	}
}

int Wake::wakeTimer = 0;
int Wake::wakeTimerThreshold = 15;

int Wake::get_circleSegments()
{
	return m_circleSegments;
}

void Wake::set_circleSegments(int _segments)
{
	m_circleSegments = _segments;
}
