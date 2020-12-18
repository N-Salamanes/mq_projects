/* Author: Nigel Salamanes 43690599
 *         nigel.salamanes@students.mq.edu.au
 * Date:   30 Mar 2017
 *
 * user_boat.hpp
 *
 * the boat declarations
 *
 */
#ifndef USER_BOAT_HPP_
#define USER_BOAT_HPP_
#include <GL/glut.h>
#include <math.h>
#include "../include/global.hpp"
#include "../include/object.hpp"

class User : public Object
{
public:
	User();					// default constructor for User
	~User();				// deconstructor

	void update(int);		// overrided function, updates the object
	void draw();			// ovverided function, draws the object

	static bool isMoving; 	// is the object moving or not
};

#endif /* USER_BOAT_HPP_ */
