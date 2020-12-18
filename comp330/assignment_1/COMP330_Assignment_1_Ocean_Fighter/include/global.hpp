/* Author: Nigel Salamanes 43690599
 *         nigel.salamanes@students.mq.edu.au
 * Date:   29 Mar 2017
 *
 * global.hpp
 *
 * contains global variables used within the program
 *
 */
#ifndef GLOBAL_HPP_
#define GLOBAL_HPP_
#include <math.h>
// PI
# define PI 3.1415926535897932

// size of screen window
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 750

// Animation time step in msec. 300 frames per second.
#define ANIMATION_STEP (1000/300)

// each object is defined within a layer so we know which order to draw objects
#define FIGHTER 0
#define FIGHTER_LAYER 0
#define BULLET_LAYER 1
#define FUEL_DRUM_LAYER 2
#define EXPLOSION_LAYER 3
#define WAKE_LAYER 4

// menu options
#define ANIMATING 1

#define DELTA_TIME (delta_t / 1000.0)

struct Globals {
	float mouse_x, mouse_y;
	bool mouse_left;
	bool mouse_right;
	int animating;
	int time;
};

extern struct Globals globals;

float limit(float, float, float);
bool nearby(float, float, float, float, float);
#endif /* GLOBAL_H_ */
