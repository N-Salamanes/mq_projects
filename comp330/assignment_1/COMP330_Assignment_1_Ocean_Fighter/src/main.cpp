/* Author: Nigel Salamanes 43690599
 *         nigel.salamanes@students.mq.edu.au
 * Date:   29 Mar 17
 *
 * main.cpp
 * main source file which initializes the program with openGL and other required
 * functions.
 *
 * This is adapted from chaser.cpp by Len Hamey
 * which animates a square that chases the mouse
 */
#include <GL/glut.h>
#include <math.h>

#include "../include/global.hpp"
#include "../include/object.hpp"
#include "../include/user_boat.hpp"
#include "../include/ocean.hpp"
#include "../include/bullet.hpp"
#include "../include/fuel_drum.hpp"
#include "../include/explosion.hpp"
#include "../include/wake.hpp"

Ocean ocean; 					// create an instance of ocean
std::vector< std::vector<Object*> > Objects;// contains all the objects instantiated

void menu(int selected)
{
	switch(selected)
	{
	case ANIMATING: // enable/disable animating
	{
		globals.animating = !globals.animating;
		glutPostRedisplay();
		break;
	}
	}
}

void keyboard (unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
	{
		menu(ANIMATING);
		break;
	}
	}
}

// The parameters are screen coordinates of the mouse.
// Record them to determine the direction of motion at the next time step.
void mousemotion(int x, int yc)
{
	globals.mouse_x = x;
	globals.mouse_y = SCREEN_HEIGHT - yc;
}

void onMouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		globals.mouse_left = true;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		globals.mouse_left = false;
	}
}

// the parameter v is the time (in msec) of the last call
void timer(int v) // aka update
{
	globals.time = glutGet(GLUT_ELAPSED_TIME);

	// Set up next timer event
	glutTimerFunc(ANIMATION_STEP, timer, globals.time);

	// time elapsed minus time since last call
	int delta_t = globals.time - v;

	if (globals.animating == 1) {
		// animate the ocean
		ocean.update(v);

		// create a wake behind the fighter
		Wake::wakeTimer += delta_t;
		if (User::isMoving == true)
		{
			if (Wake::wakeTimer > Wake::wakeTimerThreshold)
			{
				Wake::wakeTimer = 0;
				Wake* wake = new Wake(Objects[FIGHTER_LAYER][FIGHTER]->get_x(), Objects[FIGHTER_LAYER][FIGHTER]->get_y());
				Objects[WAKE_LAYER].push_back(wake);
			}
		}

		//spawn bullets
		Bullet::m_bulletTimer += delta_t;
		if (globals.mouse_left == true)
		{
			if ((Bullet::m_bulletTimer > Bullet::m_bulletTimerThreshold) &&(Bullet::get_count() < Bullet::get_limit()))
			{
				Bullet* bullet = new Bullet(Objects[FIGHTER_LAYER][FIGHTER]->get_rotation(), Objects[FIGHTER_LAYER][FIGHTER]->get_x(), Objects[FIGHTER_LAYER][FIGHTER]->get_y());
				Objects[BULLET_LAYER].push_back(bullet);
				Bullet::m_bulletTimer = 0;
			}
		}

		// spawn fuel drums
		FuelDrum::m_fueldrumTimer += delta_t;
		if (FuelDrum::m_fueldrumTimer >  FuelDrum::m_fueldrumTimerThreshold)
		{
			if (FuelDrum::get_count() < FuelDrum::get_limit())
			{
				double x = rand() % SCREEN_WIDTH;
				double y = rand() % SCREEN_HEIGHT;

				FuelDrum* fd = new FuelDrum(x, y);

				Objects[FUEL_DRUM_LAYER].push_back(fd);
				FuelDrum::m_fueldrumTimer = 0;
			}
		}

		// update the objects
		for (unsigned int objectType = 0; objectType < Objects.size(); objectType++)
		{
			for (unsigned int element = 0; element < Objects[objectType].size(); element++)
			{
				Objects[objectType][element]->update(v);
			}
		}

		// check for intersections
		// checking between bullets and fuel drums
		for (unsigned int bullet = 0; bullet < Objects[BULLET_LAYER].size(); bullet++)
		{
			for (unsigned int drum = 0; drum < Objects[FUEL_DRUM_LAYER].size(); drum++)
			{
				if(nearby(
						Objects[BULLET_LAYER][bullet]->get_x(), Objects[BULLET_LAYER][bullet]->get_y(),
						Objects[FUEL_DRUM_LAYER][drum]->get_x(), Objects[FUEL_DRUM_LAYER][drum]->get_y(),
						(Objects[BULLET_LAYER][bullet]->get_length()*2 + Objects[FUEL_DRUM_LAYER][drum]->get_length()*2)
						))
				{
					// create fire at drum location
					Explosion* fire = new Explosion(Objects[2][drum]->get_x(), Objects[2][drum]->get_y());
					Objects[EXPLOSION_LAYER].push_back(fire);

					Objects[BULLET_LAYER][bullet]->set_destroy(true);
					Objects[FUEL_DRUM_LAYER][drum]->set_destroy(true);
				}
			}
		}

		// checking between ocean fighter and fuel drums
		for (unsigned int fighter = 0; fighter < Objects[FIGHTER_LAYER].size(); fighter++)
		{
			for (unsigned int drum = 0; drum < Objects[FUEL_DRUM_LAYER].size(); drum++)
			{
				if(nearby(
						Objects[FIGHTER_LAYER][fighter]->get_x(), Objects[FIGHTER_LAYER][fighter]->get_y(),
						Objects[FUEL_DRUM_LAYER][drum]->get_x(), Objects[FUEL_DRUM_LAYER][drum]->get_y(),
						(Objects[FIGHTER_LAYER][fighter]->get_length() + Objects[FUEL_DRUM_LAYER][drum]->get_length())
						))
				{
					FuelDrum* fd = dynamic_cast<FuelDrum*>(Objects[FUEL_DRUM_LAYER][drum]);
					fd->set_isOnFire(true);
				}
			}
		}

		// delete and remove objects
		for (unsigned int objectType = 0; objectType < Objects.size(); objectType++)
		{
			for (unsigned int element = 0; element < Objects[objectType].size(); element++)
			{
				if (Objects[objectType][element]->get_destroy() == true)
				{
					delete Objects[objectType][element];
					Objects[objectType].erase(Objects[objectType].begin() + element);
				}
			}
		}
		glutPostRedisplay();
	}
}

void display(void) // aka draw
{
	// clear the background to the ocean color
	glClearColor(0.0, 0.0, ocean.get_ocean(), 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// draw the objects
	// go in reverse so that the boat is drawn last (is on top)
	for (signed int objectType = Objects.size()-1; objectType >= 0; objectType--)
	{
		for (signed int element = Objects[objectType].size()-1; element >= 0; element--)
		{
			Objects[objectType][element]->draw();
		}
	}
	glutSwapBuffers();
}

void init(void)
{
	// initialise the vector of objects (5 for now so we can be flexible later on)
	Objects.resize(5);

	// create the user and add it to the list of objects
	User* user = new User();
	Objects[0].push_back(user);

	// Pretend initial position of the mouse - if it out of the window
	// then the chaser will initially move to this position
	globals.mouse_x = SCREEN_WIDTH / 2;
	globals.mouse_y = SCREEN_HEIGHT / 2;

	globals.mouse_left = false;

	globals.animating = 1;
	/* Define world window and set up window-to-viewport transformation */
	glMatrixMode(GL_PROJECTION); // Set the projection matrix
	glLoadIdentity();            // Initialise to identity matrix
	gluOrtho2D(0.0, SCREEN_WIDTH, 0.0, SCREEN_HEIGHT); // Set to orthographic projection of window
}

/**
 * main function,
 * init/set up openGL, register callback, enter main loop
 *
 */
int main(int argc, char** argv)
{
	srand (time(NULL)); 								// random generator with time as seed
	glutInit(&argc, argv);								// init OpenGL Utility Toolkit
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);		// display mode
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);	// window size based on parameters
	glutInitWindowPosition(100, 100);					// set window position
	glutCreateWindow ("Ocean Fighter - 43690599");		// title of the program
	glutDisplayFunc(display);							// display callback
	glutTimerFunc(ANIMATION_STEP, timer, 0);			// timer callback
	glutKeyboardFunc(keyboard);							// keyboard callback
	glutPassiveMotionFunc(mousemotion);					// passive mouse motion callback
	glutMotionFunc(mousemotion);						// mouse motion callback
	glutMouseFunc(onMouseClick);						// when mouse buttons are clicked
	glutCreateMenu(menu);								// create menu
	glutAddMenuEntry("a: Animating on/off", ANIMATING);	// add menu entry
	glutAttachMenu(GLUT_RIGHT_BUTTON);					// attach menu to right mouse button
	init();												// init
	glutMainLoop();										// enter main loop
	return 0;											// exit
}





