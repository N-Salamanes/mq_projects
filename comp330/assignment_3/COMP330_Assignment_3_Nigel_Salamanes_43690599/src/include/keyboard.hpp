/*
 * keyboard.hpp
 *
 *  Created on: 2017-06-05
 *      Author: Nigel Salamanes
 *
 *  keyboard header file
 */

#ifndef SRC_INCLUDE_KEYBOARD_HPP_
#define SRC_INCLUDE_KEYBOARD_HPP_

#include <GL/glut.h>

#include "plane.hpp"

void keyboardCB(unsigned char key, int x, int y);
void specialCB(int key, int x, int y);

extern bool titlePage;

extern int perspectiveSwitch;
extern int sideSwitch;
extern int cockpitSwitch;
extern int topdownSwitch;

#endif /* SRC_INCLUDE_KEYBOARD_HPP_ */
