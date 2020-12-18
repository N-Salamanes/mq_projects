/*
 * view.hpp
 *
 *  Created on: 2017-06-04
 *      Author: Nigel Salamanes
 *
 *  header file for the different views
 */

#ifndef SRC_INCLUDE_VIEW_HPP_
#define SRC_INCLUDE_VIEW_HPP_

#include <GL/glut.h>

void titlepageView(int X_RES, int Y_RES);
void perspectiveView(int _switch, int X_RES, int Y_RES);
void sideView(int _switch, int X_RES, int Y_RES);
void cockpitView(int _switch, int X_RES, int Y_RES);
void topdownView(int _switch, int X_RES, int Y_RES);
void viewSwitch(int _switch, int X_RES, int Y_RES);

#endif /* SRC_INCLUDE_VIEW_HPP_ */
