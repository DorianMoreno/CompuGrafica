#ifndef __LIGHT__H__
#define __LIGHT__H__

#include "quaternion.h"
#include "vector.h"
#include "mesh.h"
#include <GL/glut.h>
#include <chrono>

class Light
{
public:
	//! Memory management
	//@{
	Light();
	//@}

	void setLight(GLenum light);
	void updatePosition();

private:
	float frequency;
	float radX;
	float radY;

	Vector center;
	Vector color;
	Quaternion rotation;
	GLenum lightNo;

	std::chrono::time_point< std::chrono::high_resolution_clock > startingTime;
};

#include "light.hxx"

#endif // __LIGHT__H__
