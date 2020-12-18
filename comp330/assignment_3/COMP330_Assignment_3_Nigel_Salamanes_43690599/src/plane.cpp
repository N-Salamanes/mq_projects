/*
 * plane.cpp
 *
 *  Created on: 2017-06-03
 *      Author: Nigel Salamanes
 *
 *  functions required for the plane
 */

#include "include/plane.hpp"

#define PLANE_GROUND_LEVEL 0.5

Plane::Plane(){
	// starting properties of the plane
	x = -19.5;
	y = PLANE_GROUND_LEVEL;
	z = 0.0;
	yaw_angle = 90;
	pitch_angle = roll_angle = 0.0;

	// plane speed
	plane_speed_fast = 0.01;
	plane_speed_slow = 0.005;
	yaw_speed_fast = 0.2;
	yaw_speed_slow = 0.05;
	pitch_speed = 0.1;

	//plane propeller properties
	propeller_angle = 0.0;
	propeller_speed = 1.0;

	// set animation properties
	animations = stopped;
	stage = 0;
	timerAnimation = 0;
	landingControl = false;
	corkscrewControl = false;
	corkscrewSpeed = 1.0;
	loopControl = false;
	loopSpeed = 0.05;
	loopYaw = 0.0;
}

Plane::~Plane(){};

void Plane::draw(){
	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();

	glPushMatrix();
		if (loopControl == false){
			//global co-ordinates
			glTranslated(x, y, z);
		}
		else{
			double xRef, yRef, zRef;
			xRef = x/2;
			yRef = y/2;
			zRef = z/2;

			// new reference point
			glTranslated(xRef, yRef, zRef);

			glRotatef(loopYaw, 0.0f,1.0f,0.0f);

			glTranslated(xRef, yRef, zRef);
		}

		glRotatef(yaw_angle, 0.0f,1.0f,0.0f);
		glRotatef(pitch_angle, 1.0f,0.0f,0.0f);
		glRotatef(roll_angle, 0.0f,0.0f,1.0f);

		//body
		glPushMatrix();
			GLfloat bodyMat[] = {0.7, 0.7, 0.7, 1.0};
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, bodyMat);

			gluCylinder(quadratic, 0.3, 0.3, 2.0, 32, 32);
		glPopMatrix();

		//front
		glPushMatrix();
			GLfloat frontMat[] = {0.25, 0.25, 0.25, 1.0};
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, frontMat);

			glTranslated(0.0, 0.0, 2.0);
			gluCylinder(quadratic, 0.3, 0.1, 0.5, 32, 32);
		glPopMatrix();

		//front propeller
		glPushMatrix();
			glRotatef(propeller_angle, 0.0f,0.0f,1.0f);
			GLfloat propelMat[] = {0.0, 0.0, 0.0, 1.0};
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, propelMat);

			glTranslated(0.0, 0.0, 2.5);
			glScaled(0.8, 0.15, 0.01);
			glutSolidCube(1.0);
		glPopMatrix();
		glPushMatrix();
			glRotatef(propeller_angle, 0.0f,0.0f,1.0f);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, propelMat);

			glTranslated(0.0, 0.0, 2.5);
			glScaled(0.15, 0.8, 0.01);
			glutSolidCube(1.0);
		glPopMatrix();


		//wings
		glPushMatrix();
			GLfloat wingsMat[] = {0.1, 0.1, 0.1, 1.0};
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, wingsMat);

			glScaled(2.5, 0.05, 0.5);
			glTranslated(0.0, 0.0, 2.0);
			glutSolidCube(1.0);
		glPopMatrix();

	glPopMatrix();
}

void Plane::update(int delta_t){
	//update propeller
	propeller_angle += propeller_speed * delta_t;
	if (propeller_angle > 360){
		propeller_angle -= 360;
	}

	// update corkscrew animation
	if (corkscrewControl == true){
		roll_angle += corkscrewSpeed * delta_t;
		if (roll_angle > 360){
			corkscrewControl = false;
			roll_angle = 0;
		}
	}

	//update looping animation
	if (loopControl == true){
		loopYaw -= loopSpeed * delta_t;
		if (loopYaw < -360){
			loopYaw = 0;
			loopControl = false;
			animations = holdingpattern;
		}
	}

	switch(animations){
	case stopped:{

		break;
	}
	case takeoff:{
		//
		takeoffAnimation(delta_t);
		break;
	}
	case holdingpattern:{
		if (loopControl == true){
			animations = looping;
		}
		holdingpatternAnimation(delta_t);
		break;
	}
	case looping:{
		// do nothing
		break;
	}
	case landing:{
		landingAnimation(delta_t);
		break;
	}
	}
}

void Plane::takeoffAnimation(int delta_t){
	switch(stage){
	case 0:{// leaving the terminal to runway
		// move plane to the runway
		if (x < 0){
			x += plane_speed_slow * delta_t;
		}
		else{
			stage = 1;
		}
		break;
	}
	case 1:{// rotating at the runway
		if (yaw_angle > 0){
			yaw_angle -= yaw_speed_slow * delta_t;
		}
		else{
			yaw_angle = 0;
			stage = 2;
		}
		break;
	}
	case 2:{// pause here till lift off
		timerAnimation += delta_t;
		if (timerAnimation > 2000){
			timerAnimation = 0;
			stage = 3;
		}
		break;
	}
	case 3:{// go halfway down runway
		if (z < 10){
			z += plane_speed_slow * delta_t;
		}
		else{
			stage = 4;
		}
		break;
	}
	case 4:{// lift off
		if (z < 20){
			z += plane_speed_fast * delta_t;
			y += plane_speed_fast * delta_t;
			if (pitch_angle > -30.0){
				pitch_angle -= pitch_speed * delta_t;
			}
		}
		else{
			stage = 5;
		}
		break;
	}
	case 5:{// straighten up
		if (pitch_angle < 0){
			pitch_angle += pitch_speed * delta_t;
			z += plane_speed_fast * delta_t;
		}
		else{
			pitch_angle = 0;
			stage = 6;
		}
		break;
	}
	case 6:{// go to first corner
		if (yaw_angle > -90){
			yaw_angle -= yaw_speed_fast * delta_t;
		}
		else{
			yaw_angle = -90;
		}
		if (x > -20){
			x -= plane_speed_fast * delta_t;
		}
		else{
			stage = 7;
		}
		break;
	}
	case 7:{// go to holding pattern
		stage = 3;
		animations = holdingpattern;
		break;
	}
	}
}

void Plane::holdingpatternAnimation(int delta_t){
	switch(stage){
	case 0:{// 1st to 2nd
		if (yaw_angle > -270){
			yaw_angle -= yaw_speed_fast * delta_t;
		}
		else{
			yaw_angle = -270;
		}
		// check if we need to land
		if (((x < 0) && (x > -5)) && (landingControl == true)){
			stage = 0;
			animations = landing;
		}
		else if (x < 20){
			x += plane_speed_fast * delta_t;
		}
		else{
			stage = 1;
		}
		break;
	}
	case 1:{// 2nd to 3rd
		if (yaw_angle > -360){
			yaw_angle -= yaw_speed_fast * delta_t;
		}
		else{
			yaw_angle = -360;
		}
		if (z < 20){
			z += plane_speed_fast * delta_t;
		}
		else{
			yaw_angle = 0;
			stage = 2;
		}
		break;
	}
	case 2:{// 3rd to 4th
		if (yaw_angle > -90){
			yaw_angle -= yaw_speed_fast * delta_t;
		}
		else{
			yaw_angle = -90;
		}
		if (x > -20){
			x -= plane_speed_fast * delta_t;
		}
		else{
			stage = 3;
		}
		break;
	}
	case 3:{// 4th to 1st
		if (yaw_angle > -180){
			yaw_angle -= yaw_speed_fast * delta_t;
		}
		else{
			yaw_angle = -180;
		}
		if (z > -20){
			z -= plane_speed_fast * delta_t;
		}
		else{
			stage = 0;
		}
		break;
	}
	}
}

void Plane::landingAnimation(int delta_t){
	switch(stage){
	case 0:{// line up to the runway
		if (x < 0){
			x += plane_speed_fast * delta_t;
		}
		else{
			x = 0;
			stage = 1;
			landingControl = false;
		}
		break;
	}
	case 1:{// rotate to runway and start landing
		if (pitch_angle < 30.0){
			pitch_angle += pitch_speed * delta_t;
		}
		if (yaw_angle > -360){
			yaw_angle -= yaw_speed_fast * delta_t;
		}
		else{
			yaw_angle = -360;
		}
		if (y > PLANE_GROUND_LEVEL * 4){
			y -= plane_speed_fast * delta_t;
		}
		if (z < -15){
			z += plane_speed_fast * delta_t;
		}
		else{
			stage = 2;
			yaw_angle = 0;
		}
		break;
	}
	case 2:{// decending
		if (pitch_angle > 0){
			pitch_angle -= pitch_speed * delta_t;
		}
		else{
			pitch_angle = 0;
		}
		if (y > PLANE_GROUND_LEVEL){
			y -= plane_speed_fast * delta_t;
		}
		else{
			y = PLANE_GROUND_LEVEL;
		}
		if (z < -5){
			z += plane_speed_fast * delta_t;
		}
		else{
			stage = 3;
		}
		break;
	}
	case 3:{// decending to landing
		if (z < 0){
			z += plane_speed_fast * delta_t;
		}
		else{
			z = 0;
			stage = 4;
		}
		break;
	}
	case 4:{// rotate to terminal
		if (yaw_angle < 90){
			yaw_angle += yaw_speed_slow * delta_t;
		}
		else{
			yaw_angle = 90;
			stage = 5;
		}
		break;
	}
	case 5:{
		// move plane back to the terminal
		if (x > -19.5){
			x -= plane_speed_slow * delta_t;
		}
		else{
			x = -19.5;
			stage = 0;
			animations = stopped;
			break;
		}
		break;
	}
	}

}

