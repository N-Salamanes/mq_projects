/* Author: Nigel Salamanes 43690599
 *         nigel.salamanes@students.mq.edu.au
 * Date:   30 Mar 2017
 *
 * user_boat.cpp
 *
 * the boat functions
 *
 */
#include "../include/user_boat.hpp"

User::User()
{
	// set the starting variables for the user
	set_x(SCREEN_WIDTH / 2);
	set_y(SCREEN_HEIGHT / 2);
	set_rotation(0.0);
	set_rotationSpeed(500.0);
	set_length(40.0);
	set_velocity(500.0);
	set_collision(false);
	set_destroy(false);

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
	layer.length = 40.0;
	// structure/points
	Point pt;
	pt.x = 0.5; pt.y = 0.0;
	layer.structure.push_back(pt);
	pt.x = -0.5; pt.y = -0.5;
	layer.structure.push_back(pt);
	pt.x = -0.5; pt.y = 0.5;
	layer.structure.push_back(pt);
	// add the layer
	m_structure.push_back(layer);

	// create layer(s) for an object
	// * - LAYER 2 - *
	// gl draw type
	layer.glType = GL_POLYGON;
	// colour
	layer.red = 0.662f;
	layer.green = 0.662f;
	layer.blue = 0.662f;
	// length
	layer.length = 32.5;
	// structure/points

	pt.x = -0.5; pt.y = 0.5;
	layer.structure.push_back(pt);
	pt.x = -1.5; pt.y = 0.5;
	layer.structure.push_back(pt);
	pt.x = -1.5; pt.y = -0.5;
	layer.structure.push_back(pt);
	pt.x = -0.5; pt.y = -0.5;
	layer.structure.push_back(pt);
	// add the layer
	m_structure.push_back(layer);

	// create layer(s) for an object
	// * - LAYER 3 - *
	// gl draw type
	layer.glType = GL_POLYGON;
	// colour
	layer.red = 0.15f;
	layer.green = 0.15f;
	layer.blue = 0.15f;
	// length
	layer.length = 20.0;
	// structure/points

	pt.x = -0.5; pt.y = 0.5;
	layer.structure.push_back(pt);
	pt.x = -1.5; pt.y = 0.5;
	layer.structure.push_back(pt);
	pt.x = -1.5; pt.y = -0.5;
	layer.structure.push_back(pt);
	pt.x = -0.5; pt.y = -0.5;
	layer.structure.push_back(pt);
	// add the layer
	m_structure.push_back(layer);
}

User::~User(){}

void User::update(int v)
{
	// time elapsed minus time since last call
	int delta_t = globals.time - v;

	User::isMoving = true;

	double delta_x, delta_y,
	length,
	rotation_size,
	movement_size;

	// Compute vector from current location to mouse
	delta_x = globals.mouse_x - get_x();
	delta_y = globals.mouse_y - get_y();

	// Compute length of the vector
	length = sqrt (delta_x*delta_x + delta_y*delta_y);

	// If the triangle is close to the mouse, then no motion is required.
	// this includes movement and rotation
	movement_size = get_velocity() * DELTA_TIME;
	rotation_size = get_rotation() * DELTA_TIME;

	// Normalise the delta vector and compute the step
	delta_x = delta_x / length;
	delta_y = delta_y / length;

	// old/prev angle and new angle
	double oldAngle = get_rotation();
	double targetAngle = atan2(delta_y, delta_x) * 180.0 / PI;

	// boat rotation
	if (length > movement_size * 0.55)
	{
		// increments
		double incAngle = 0.0;

		// convert angles to 360 for easier computation and calculations
		double oldAngle360 = oldAngle + 180.0;
		double targetAngle360 = targetAngle + 180.0;

		// calculate which way to rotate
		if (oldAngle360 < targetAngle360 - 180)
		{
			incAngle = -get_rotationSpeed();
		}
		else if (oldAngle360 > targetAngle360 + 180)
		{
			incAngle = get_rotationSpeed();
		}
		else if (targetAngle360 > oldAngle360)
		{
			incAngle = get_rotationSpeed();
		}
		else if (targetAngle360 < oldAngle360)
		{
			incAngle = -get_rotationSpeed();
		}

		// update angle with smooth rotation
		if (fabs(oldAngle360 - targetAngle360) <= rotation_size)
		{
			// snap rotation to point to mouse position
			set_rotation(targetAngle);
		}
		else
		{
			// smoothly rotate fighter
			set_rotation(oldAngle + (incAngle * DELTA_TIME));
		}

		// keep the rotation within bounds [-180, 180]
		if (get_rotation() > 180)
		{
			set_rotation(get_rotation() - 360);
		}
		else if (get_rotation() < -180)
		{
			set_rotation(get_rotation() + 360);
		}
	}

	// boat movement
	if (length > movement_size * 0.55)
	{
		// move the boat
		add_x(cos(get_rotationInRadians()) * movement_size);
		add_y(sin(get_rotationInRadians()) * movement_size);

		// Keep the triangle inside the world window.
		set_x(limit(get_x(), get_length()/2, SCREEN_WIDTH - get_length()/2));
		set_y(limit(get_y(), get_length()/2, SCREEN_HEIGHT - get_length()/2));
	}
	else
	{
		User::isMoving = false;
	}
}

void User::draw()
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

bool User::isMoving = false;
