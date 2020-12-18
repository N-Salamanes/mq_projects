/*
 * input.cpp
 *
 *  Created on: 2017-06-17
 *      Author: Nigel Salamanes
 *
 *  keyboard functions
 */

#include "include/keyboard.hpp"

/**
 * keyboard callback function
 */
void keyboardCB(unsigned char key, int x, int y){
	switch (key)	{
	case ' ':{
		titlePage = false;
		break;
	}
	case '\t':{
		if (titlePage == false){
			perspectiveSwitch += 1;
			if (perspectiveSwitch > 3){
				perspectiveSwitch = 0;
			}
			sideSwitch += 1;
			if (sideSwitch > 3){
				sideSwitch = 0;
			}
			cockpitSwitch += 1;
			if (cockpitSwitch > 3){
				cockpitSwitch = 0;
			}
			topdownSwitch += 1;
			if (topdownSwitch > 3){
				topdownSwitch = 0;
			}
		}
		break;
	}
	case '1':{
		if (titlePage == false){
			if (plane.animations == stopped){
				plane.animations = takeoff;
			}
		}
		break;
	}
	case '2':{
		if (plane.animations == holdingpattern){
			plane.corkscrewControl = true;
		}
		break;
	}
	case '3':{
		if (plane.animations == holdingpattern){
			plane.loopControl = true;
		}
		break;
	}
	case '4':{
		if(plane.animations == holdingpattern){
			plane.landingControl = true;
		}
		break;
	}
	}

	glutPostRedisplay();
}

void specialCB(int key, int x, int y){
	switch (key)	{
	case GLUT_KEY_UP:{
		//extra features
		break;
	}
	case GLUT_KEY_DOWN:{
		//extra features
		break;
	}
	}

	glutPostRedisplay();
}
