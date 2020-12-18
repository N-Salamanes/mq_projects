/* Author: Nigel Salamanes 43690599
 *         nigel.salamanes@students.mq.edu.au
 * Date:   14 Apr 2017
 *
 * fuel_drum.cpp
 *
 * the fuel drum functions
 *
 */
#include "../include/fuel_drum.hpp"

FuelDrum::FuelDrum(double _x, double _y)
{
	// set the starting variables for the fuel drum
	set_x(_x);
	set_y(_y);
	set_rotation(0.0);
	set_rotationSpeed(0.0);
	set_length(4.5);
	set_velocity(1.0);
	set_collision(false);
	set_destroy(false);

	// increase the count for fueldrums
	m_fueldrumCount++;

	m_isOnFire = false;
	xRand = (rand()%100) - 50;
	yRand = (rand()%100) - 50;
	m_fireTimer = 0;
	m_fireTimerThreshold = 2000;
	m_directionTimerThreshold = 1.5;
	set_directionTimer(0.0);

	// create layer(s) for an object
	// * - LAYER 1 - *
	DrawLayer layer;
	// gl draw type
	layer.glType = GL_POLYGON;
	// colour
	layer.red = 0.5f;
	layer.green = 0.5f;
	layer.blue = 0.5f;
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
	// * - LAYER 2 - *

	// gl draw type
	layer.glType = GL_POLYGON;
	// colour
	layer.red = 0.25f;
	layer.green = 0.25f;
	layer.blue = 0.25f;
	// length
	layer.length = 3.5;
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

FuelDrum::~FuelDrum()
{
	m_fueldrumCount--;
}

void FuelDrum::update(int v)
{
	// time elapsed minus time since last call
	int delta_t = globals.time - v;

	set_directionTimer(get_directionTimer() + DELTA_TIME);

	if (get_directionTimer() > m_directionTimerThreshold)
	{
		xRand = (rand()%100) - 50;
		yRand= (rand()%100) - 50;
		// reset
		set_directionTimer(0.0);
	}

	double movement_size = get_velocity() * DELTA_TIME;

	add_x(movement_size * xRand);
	add_y(movement_size * yRand);

	// Keep the fuel drum inside the world window
	set_x(limit(get_x(), get_length()/2, SCREEN_WIDTH - get_length()/2));
	set_y(limit(get_y(), get_length()/2, SCREEN_HEIGHT - get_length()/2));

	// update the fire scale if need
	if (get_isOnFire() == true)
	{
		m_fireTimer += delta_t;

		m_xScaleFire = rand()%6;
		m_yScaleFire = rand()%6;

		if (m_fireTimer > m_fireTimerThreshold)
		{
			set_destroy(true);
		}
	}
}

void FuelDrum::draw()
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
	if (get_isOnFire() == true)
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
		glScalef(m_fire.length * m_xScaleFire, m_fire.length * m_yScaleFire, 0);
		// set the color
		glColor3f(m_fire.red, m_fire.green, m_fire.blue);

		// begin drawing
		glBegin(m_fire.glType);
			// begin drawing given points
			for (unsigned int j = 0; j < m_fire.structure.size(); j++)
			{
				glVertex2f(m_fire.structure[j].x, m_fire.structure[j].y);
			}
		// end drawing
		glEnd();

		glFlush();
	}
}

int FuelDrum::m_fueldrumTimer = 0;
int FuelDrum::m_fueldrumTimerThreshold = 2000;

int FuelDrum::m_fueldrumCount = 0;
int FuelDrum::get_count()
{
	return m_fueldrumCount;
}

int FuelDrum::m_fueldrumLimit = 10;
int FuelDrum::get_limit()
{
	return m_fueldrumLimit;
}

bool FuelDrum::get_isOnFire()
{
	return m_isOnFire;
}

void FuelDrum::set_isOnFire(bool _isOnFire)
{
	if (get_isOnFire() == false)
	{
		if (_isOnFire == true)
		{
			m_isOnFire = _isOnFire;

			// gl draw type
			m_fire.glType = GL_POLYGON;
			// colour
			m_fire.red = 1.0f;
			m_fire.green = 0.0f;
			m_fire.blue = 0.0f;
			// length
			m_fire.length = 2.0;
			// scale
			m_xScaleFire = 0.0f;
			m_yScaleFire = 0.0f;
			// structure/points
			set_circleSegments(20);
			Point pt;
			for(int i = 0; i < get_circleSegments(); i++)
			{
				// copied and modified drawing circle code from:
				// http://stackoverflow.com/questions/22444450/drawing-circle-with-opengl

				float theta = 2.0f * 3.1415926f * float(i) / float(get_circleSegments());//get the current angle

				pt.x = m_fire.length * cosf(theta);//calculate the x component
				pt.y = m_fire.length * sinf(theta);//calculate the y component

				m_fire.structure.push_back(pt);
			}
		}
	}
}

int FuelDrum::get_circleSegments()
{
	return m_circleSegments;
}

void FuelDrum::set_circleSegments(int _segments)
{
	m_circleSegments = _segments;
}

double FuelDrum::get_directionTimer(){
	return m_directionTimer;
}

void FuelDrum::set_directionTimer(double _timer)
{
	m_directionTimer = _timer;
}






