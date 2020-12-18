/*
 * view.cpp
 *
 *  Created on: 2017-06-04
 *      Author: Nigel Salamanes
 *
 *  functions for the different views
 */

#include "include/view.hpp"

void viewSwitch(int _switch, int X_RES, int Y_RES){
	switch(_switch){
	case 0:{// main view (top)
		glViewport(0, Y_RES/2, X_RES, Y_RES/2);
		glMatrixMode(GL_PROJECTION);;
		glLoadIdentity();
		gluPerspective(45, (float)X_RES/(Y_RES/2), 0.5, 100);
		break;
	}
	case 1:{// bottom left
		glViewport(0, 0, X_RES/3, Y_RES/2);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(90, (float)(X_RES/3)/(Y_RES/2), 0.5, 100);
		break;
	}
	case 2:{// bottom middle
		glViewport(X_RES/3, 0, X_RES/3, Y_RES/2);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(90, (float)(X_RES/3)/(Y_RES/2), 0.5, 100);
		break;
	}
	case 3:{// bottom right
		glViewport((X_RES/3)*2, 0, X_RES/3, Y_RES/2);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(90, (float)(X_RES/3)/(Y_RES/2), 0.5, 100);
		break;
	}

	}
}

void titlepageView(int X_RES, int Y_RES){
	glViewport(0, 0, X_RES, Y_RES);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, (float)X_RES/Y_RES, 0.5, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void perspectiveView(int _switch, int X_RES, int Y_RES){
	viewSwitch(_switch, X_RES, Y_RES);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void sideView(int _switch, int X_RES, int Y_RES){
	viewSwitch(_switch, X_RES, Y_RES);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void cockpitView(int _switch, int X_RES, int Y_RES){
	viewSwitch(_switch, X_RES, Y_RES);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void topdownView(int _switch, int X_RES, int Y_RES){
	viewSwitch(_switch, X_RES, Y_RES);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

