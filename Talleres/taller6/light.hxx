#ifndef __LIGHT__HXX__
#define __LIGHT__HXX__

#include "light.h"
#include "vector.h"
#include "quaternion.h"
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <cmath>
#include <random>
#include <iostream>

//------------------------------------------------------------------------------
#define _MIN_TIME   0.01
#define _THRESHOLD  0.01
#define _GRAVITY    100
#define _GRAVITY_2  50

//------------------------------------------------------------------------------
Light::Light():
	frequency(0),
	radX(0),
	radY(0),
	lightNo(GL_LIGHT0),
	center(false),
	color(false)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(0.0, 1.0);

	this->frequency = 5.0;
	this->radX = 10.0*dist(mt);
	this->radY = 10.0*dist(mt);
	this->center = Vector(12*dist(mt), 12*dist(mt), 12*dist(mt)) - Vector(6, 6, 6);
	this->color = Vector(dist(mt), dist(mt), dist(mt));

	Vector aux(dist(mt), dist(mt), dist(mt));
	aux.normalize();
	this->rotation = Quaternion(aux, fmod(360*dist(mt), 360));

	this->startingTime = std::chrono::high_resolution_clock::now( );
}

void Light::setLight(GLenum light){
	this->lightNo = light;
}

void Light::updatePosition(){
	double s =
	  std::chrono::duration_cast< std::chrono::milliseconds >(
		std::chrono::high_resolution_clock::now( ) - this->startingTime
		).count( );
	float angle = 2.0 * _PI * s / ( this->frequency * 1000.0 );

	angle = fmod(angle, 2.0 * _PI);

	float t = std::atan(this->radX/this->radY * std::tan(angle));
	if(angle > _PI /2){
		t += _PI;
		if(angle > _PI*3/2)
			t += _PI;
	}

	float x, y;
	x = std::cos( t ) * this->radX;
	y = std::sin( t ) * this->radY;

	Vector end = this->rotation.rotatePoint(Vector(x, y, 0));
	GLfloat light_position[] = {end[0] + this->center[0], end[1] + this->center[1], end[2] + this->center[2], 1.0};
	GLfloat light_color[] = {this->color[0], this->color[1], this->color[2], 1.0};
	glPushMatrix();
		glPushMatrix();
			gluLookAt(0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
			glLightfv(this->lightNo, GL_POSITION, light_position);
			glLightfv(this->lightNo, GL_DIFFUSE, light_color);
			glLightfv(this->lightNo, GL_SPECULAR, light_color);
		glPopMatrix();
		glTranslatef(end[0] + this->center[0], end[1] + this->center[1], end[2] + this->center[2]);
		glDisable(GL_LIGHTING);
		glColor3f(this->color[0], this->color[1], this->color[2]);
		glutSolidSphere(0.25, 5, 5);
		glEnable(GL_LIGHTING);
	glPopMatrix();
}

#endif //__LIGHT__HXX__
