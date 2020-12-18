/*
 * main.cpp
 *
 *  Created on: 2017-06-03
 *      Author: Nigel Salamanes (43690599)
 *
 *  main source file for COMP330 - Assignment 3
 */

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <GL/glut.h>

#include "include/keyboard.hpp"
#include "include/view.hpp"
#include "include/plane.hpp"

#define ANIMATION_STEP (1000/300)
int SCREEN_X = 1280;
int SCREEN_Y = 768;

using namespace std;

Plane plane;

bool titlePage;
int perspectiveSwitch;
int sideSwitch;
int cockpitSwitch;
int topdownSwitch;

struct Globals{
	int time;
}globals;

void text(string _text, int _posX, int _posY)
{
    glMatrixMode( GL_PROJECTION );
    glPushMatrix();
		glLoadIdentity();
		gluOrtho2D( 0, SCREEN_X, 0, SCREEN_Y);
		glMatrixMode( GL_MODELVIEW );

		glPushMatrix();
			glLoadIdentity();

			glRasterPos2i(_posX, _posY);// text position

			for (unsigned int i = 0; i < _text.size(); i++ )
			{
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, _text[i]);
			}
		glPopMatrix();

		glMatrixMode( GL_PROJECTION );
    glPopMatrix();
    glMatrixMode( GL_MODELVIEW );
}

void drawEnvironment(){

	glPushMatrix();

		//floor
		glPushMatrix();
			GLfloat floorMat[] = {0.2, 0.9, 0.4, 0.75};
		    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, floorMat);

			glBegin(GL_POLYGON);
				glVertex3f(-50.0, 0.0, -50.0);
				glVertex3f(50.0, 0.0, -50.0);
				glVertex3f(50.0, 0.0, 50.0);
				glVertex3f(-50.0, 0.0, 50.0);
			glEnd();
		glPopMatrix();

		//runway
		glPushMatrix();
			GLfloat runwayMat[] = {0.2, 0.2, 0.2, 1.0};
		    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, runwayMat);

			glBegin(GL_POLYGON);
				glVertex3f(-2.0, 0.01, -20.0);
				glVertex3f(2.0, 0.01, -20.0);
				glVertex3f(2.0, 0.01, 20.0);
				glVertex3f(-2.0, 0.01, 20.0);
			glEnd();
		glPopMatrix();
		//terminal road
		glPushMatrix();
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, runwayMat);

			glBegin(GL_POLYGON);
				glVertex3f(-20.0, 0.01, -2.0);
				glVertex3f(-2.0, 0.01, -2.0);
				glVertex3f(-2.0, 0.01, 2.0);
				glVertex3f(-20.0, 0.01, 2.0);
			glEnd();
		glPopMatrix();

		//building 1
		glPushMatrix();
			GLfloat building1[] = {0.49, 0.0, 1.0, 1.0};
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, building1);
			glTranslated(-5.0, 0.0, 10.0);
			glScalef(2.0, 7.5, 2.0);
			glutSolidCube(1.0f);
		glPopMatrix();

		//building 2
		glPushMatrix();
			GLfloat building2[] = {1.0, 0.0, 0.0, 1.0};
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, building2);
			glTranslated(15.0, 0.0, 10.0);
			glScalef(2.0, 7.5, 2.0);
			glutSolidCube(1.0f);
		glPopMatrix();

		//building 3
		glPushMatrix();
			GLfloat building3[] = {0.37, 0.37, 0.37, 1.0};
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, building3);
			glTranslated(-17.5, 0.0, -12.5);
			glScalef(5.0, 7.0, 5.0);
			glutSolidCube(1.0f);
		glPopMatrix();

		//building 4
		glPushMatrix();
			GLfloat building4[] = {0.0, 1.0, 0.0, 1.0};
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, building4);
			glTranslated(20.0, 0.0, -15.0);
			glScalef(5.0, 7.0, 5.0);
			glutSolidCube(1.0f);
		glPopMatrix();

		//sky - top
		glPushMatrix();
			GLfloat skyTop[] = {0.0, 0.75, 1.0, 1.0};
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, skyTop);

			glBegin(GL_POLYGON);
				glVertex3f(-50.0, 50.0, -50.0);
				glVertex3f(50.0, 50.0, -50.0);
				glVertex3f(50.0, 50.0, 50.0);
				glVertex3f(-50.0, 50.0, 50.0);
			glEnd();
		glPopMatrix();

		//sky - front
		glPushMatrix();
			GLfloat skyFront[] = {0.0, 0.75, 1.0, 1.0};
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, skyFront);

			glBegin(GL_POLYGON);
				glVertex3f(-50.0, 50.0, 50.0);
				glVertex3f(50.0, 50.0, 50.0);
				glVertex3f(50.0, 0.0, 50.0);
				glVertex3f(-50.0, 0.0, 50.0);
			glEnd();
		glPopMatrix();

		//sky - back
		glPushMatrix();
			GLfloat skyBack[] = {0.0, 0.75, 1.0, 1.0};
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, skyBack);

			glBegin(GL_POLYGON);
				glVertex3f(-50.0, 50.0, -50.0);
				glVertex3f(50.0, 50.0, -50.0);
				glVertex3f(50.0, 0.0, -50.0);
				glVertex3f(-50.0, 0.0, -50.0);
			glEnd();
		glPopMatrix();

		//sky - left
		glPushMatrix();
			GLfloat skyLeft[] = {0.0, 0.75, 1.0, 1.0};
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, skyLeft);

			glBegin(GL_POLYGON);
				glVertex3f(-50.0, 50.0, 50.0);
				glVertex3f(-50.0, 50.0, -50.0);
				glVertex3f(-50.0, 0.0, -50.0);
				glVertex3f(-50.0, 0.0, 50.0);
			glEnd();
		glPopMatrix();

		//sky - right
		glPushMatrix();
			GLfloat skyRight[] = {0.0, 0.75, 1.0, 1.0};
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, skyRight);

			glBegin(GL_POLYGON);
				glVertex3f(50.0, 50.0, 50.0);
				glVertex3f(50.0, 50.0, -50.0);
				glVertex3f(50.0, 0.0, -50.0);
				glVertex3f(50.0, 0.0, 50.0);
			glEnd();
		glPopMatrix();
	glPopMatrix();
}

void drawScene(){
	glPushMatrix();

		GLfloat lightpos[] = {0.0, 30.0, 0.0, 1.0}; //GLfloat lightpos[] = {0, 0.0, 4.0, 1.0};

		glEnable(GL_DEPTH_TEST);
		glShadeModel(GL_SMOOTH);
		glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);

		drawEnvironment();

		plane.draw();

    glPopMatrix();
}

void reshapeCB(int width, int height) /* function called whenever window is resized */{
	SCREEN_X = width;
	SCREEN_Y = height;
}

void timerCB(int v){
	globals.time = glutGet(GLUT_ELAPSED_TIME);

	// Set up next timer event
	glutTimerFunc(ANIMATION_STEP, timerCB, globals.time);

	// time in ms since last call
	int delta_t = globals.time - v;

	plane.update(delta_t);

	glutPostRedisplay();
}

/**
 * display callback function
 */
void displayCB(void){
	glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT); //clear the screen

	if (titlePage){
		titlepageView(SCREEN_X, SCREEN_Y);
		gluLookAt(plane.x+3, plane.y+2, plane.z+3,	/* From X,Y,Z position	*/
					plane.x, plane.y, plane.z,		/* To X,Y,Z position	*/
					0, 1, 0);						/* Up X,Y,Z position 	*/
		drawScene();

		text("Welcome to COMP330 Assignment 3", 100, SCREEN_Y - 100);
		text("by Nigel Salamanes (43690599)", 100, SCREEN_Y - 150);

		text("Press spacebar to continue", 100, SCREEN_Y - 250);

		text("Flight controls:", 100, SCREEN_Y - 350);
		text("1: Depart airport", 100, SCREEN_Y - 400);
		text("2: Corkscrew", 100, SCREEN_Y - 450);
		text("3: Loop", 100, SCREEN_Y - 500);
		text("4: Landing", 100, SCREEN_Y - 550);
		text("TAB: Switch views", 100, SCREEN_Y - 650);
	}
	else{
		perspectiveView(perspectiveSwitch, SCREEN_X, SCREEN_Y);
		gluLookAt(-15, 5, -10,	/* From X,Y,Z position	*/
					plane.x, plane.y, plane.z,		/* To X,Y,Z position	*/
					0, 1, 0);						/* Up X,Y,Z position 	*/
		drawScene();

		sideView(sideSwitch, SCREEN_X, SCREEN_Y);
		double camX = plane.x + (5 * cos(plane.yaw_angle * M_PI / 180));
		double camZ = plane.z + (5 * sin(plane.yaw_angle * M_PI / 180));
		gluLookAt(camX, plane.y, camZ,	/* From X,Y,Z position	*/
							plane.x, plane.y, plane.z,		/* To X,Y,Z position	*/
							0, 1, 0);						/* Up X,Y,Z position 	*/
		drawScene();

		cockpitView(cockpitSwitch, SCREEN_X, SCREEN_Y);
		gluLookAt(plane.x, plane.y + 1, plane.z,	/* From X,Y,Z position	*/
					plane.x, plane.y, plane.z+1,	/* To X,Y,Z position	*/
					0, 1, 0);						/* Up X,Y,Z position 	*/
		drawScene();

		topdownView(topdownSwitch, SCREEN_X, SCREEN_Y);
		gluLookAt(0, 40, 0,							/* From X,Y,Z position	*/
					0, 0, 0,						/* To X,Y,Z position	*/
					0, 0, 1);						/* Up X,Y,Z position 	*/
		drawScene();
	}

	glFlush(); /* Complete any pending operations */
	glutPostRedisplay();//post the ready scenes.
	glutSwapBuffers();
}

void init(){
	titlePage = true;
	perspectiveSwitch = 0;
	sideSwitch = 1;
	cockpitSwitch = 2;
	topdownSwitch = 3;
}

/**
 * main function
 */
int main(int argc, char *argv[]) {
	glutInit(&argc, argv);											/* initialize GLUT system */
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);			/* glut display mode */
	glutInitWindowSize(SCREEN_X, SCREEN_Y); 						/* set window size */
	glutInitWindowPosition(10, 10);									/* set window position */
	glutCreateWindow("Assignment 3 - Nigel Salamanes (43690599)");	/* create window */

	glutTimerFunc(ANIMATION_STEP, timerCB, 0);						/* timer callback */
	glutDisplayFunc(displayCB);										/* set display callback */
	glutReshapeFunc(reshapeCB);										/* set reshape callback */
	glutKeyboardFunc(keyboardCB);									/* set keyboard callback */
	glutSpecialFunc(specialCB);

	init();

	glutMainLoop();													/* start processing events... */

	return 0;
}
