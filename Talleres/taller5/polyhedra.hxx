#ifndef __POLYHEDRA__HXX__
#define __POLYHEDRA__HXX__

#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <ctime>
#include <random>
#include <unordered_map>

// -------------------------------------------------------------------------
#define _PI       3.14159265359
#define _2PI      6.28318530718
#define _SQRT3    1.73205080757
#define _SQRT3_2  0.86602540378
#define _SQRT3_3  0.57735026919
#define _SQRT3_4  0.43301270189
#define _SQRT3_6  0.28867513459
#define _SQRT2_2  0.70710678118
#define _SQRT6_6  0.40824829046

#define TOLERANCE 0.00000000001
// -------------------------------------------------------------------------

Point::Point(){
	this->pos[0] = 0.0;
	this->pos[1] = 0.0;
	this->pos[2] = 0.0;
}

Point::Point(const float &x, const float &y, const float &z){
	this->pos[0] = x;
	this->pos[1] = y;
	this->pos[2] = z;
}

// -------------------------------------------------------------------------

Color::Color(){
	this->col[0] = 0.5;
	this->col[1] = 0.5;
	this->col[2] = 0.5;
}

Color::Color(const float &r, const float &g, const float &b){
	this->col[0] = r;
	this->col[1] = g;
	this->col[2] = b;
}

//--------------------------------------------------------------------------
	
Vector::Vector(){
	this->x = 0.0;
	this->y = 0.0;
	this->z = 1.0;
	normalize();
}

Vector::Vector(const Point &a, const Point &b){
	x = b.pos[0] - a.pos[0];
	y = b.pos[1] - a.pos[1];
	z = b.pos[2] - a.pos[2];
	normalize();
}

Vector::Vector(const Vector &v){
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	normalize();
}

Vector::Vector(const float &x, const float &y, const float &z){
	setVector(x, y, z);
}

void Vector::normalize() {
	float magP = x*x + y*y + z*z;
	if (fabs(magP - 1.0f) > TOLERANCE){
		float mag = sqrt(magP);
		x /= mag;
		y /= mag;
		z /= mag;
	}
}

void Vector::setVector(const float &x, const float &y, const float &z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	normalize();
}

// -------------------------------------------------------------------------
	
Quaternion::Quaternion(float x, float y, float z, float w){
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Quaternion::Quaternion(const Vector &v, float angle){
	FromAxis(v, angle);
}

Quaternion Quaternion::getConjugate(){
	return Quaternion(-x, -y, -z, w);
} 

void Quaternion::normalize() {
	float magP = w*w + x*x + y*y + z*z;
	if (fabs(magP - 1.0f) > TOLERANCE){
		float mag = sqrt(magP);
		w /= mag;
		x /= mag;
		y /= mag;
		z /= mag;
	}
}

Quaternion Quaternion::operator* (const Quaternion &rq) const {
	return Quaternion(w * rq.x + x * rq.w + y * rq.z - z * rq.y, w * rq.y + y * rq.w + z * rq.x - x * rq.z, w * rq.z + z * rq.w + x * rq.y - y * rq.x, w * rq.w - x * rq.x - y * rq.y - z * rq.z);
}

void Quaternion::FromAxis(const Vector &v, float angle) {
	float sinAngle;
	angle *= 0.5f;
	sinAngle = sin(angle);
	x = (v.x * sinAngle);
	y = (v.y * sinAngle);
	z = (v.z * sinAngle);
	w = cos(angle);
} 

void Quaternion::getAxisAngle(Vector *axis, float *angle){
	float scale = sqrt(x* x + y * y + z * z);
	axis->x = x / scale;
	axis->y = y / scale;
	axis->z = z / scale;
	*angle = acos(w) * 2.0f;
}

// -------------------------------------------------------------------------

Polyhedron::Polyhedron(GLenum mode = GL_POLYGON)
{
	this->mode = mode;
	this->tx = this->ty = this->tz = 0.0;
	this->sx = this->sy = this->sz = 1.0;
	this->angle = 0;
}

void Polyhedron::drawSides(){
	
		for(unsigned int i = 0; i < noFaces ; ++i ){
			glBegin(mode);
			glColor3fv(colors[i].col);
			
			for( unsigned int j = 0; j < noVertices; ++j ){
				glVertex3fv(vertices[ faces[i][j] ].pos);
			}
			
			glEnd( );
		}
}

void Polyhedron::render(){
	glTranslatef(tx, ty, tz);
	glRotatef(angle, axis.x, axis.y, axis.z);
	glScalef(sx, sy, sz);
	drawSides();
}

void Polyhedron::translate(const float &tx, const float &ty, const float &tz){
	this->tx += tx;
	this->ty += ty;
	this->tz += tz;
}

void Polyhedron::scale(const float &sx, const float &sy, const float &sz){
	this->sx *= sx;
	this->sy *= sy;
	this->sz *= sz;
}

void Polyhedron::rotate(const float &angle, const float &rx, const float &ry, const float &rz){
	Quaternion oldR(              axis, this->angle*0.0174532925);
	Quaternion newR(Vector(rx, ry, rz),       angle*0.0174532925);
	
	newR = newR * oldR;
	
	newR.getAxisAngle(&axis, &this->angle);
	axis.normalize();
	this->angle /= 0.0174532925;
}

void Polyhedron::setTranslation(const float &tx, const float &ty, const float &tz){
	this->tx = tx;
	this->ty = ty;
	this->tz = tz;
}

void Polyhedron::setEscalation(const float &sx, const float &sy, const float &sz){
	this->sx = sx;
	this->sy = sy;
	this->sz = sz;
}

void Polyhedron::setRotation(const float &angle, const float &rx, const float &ry, const float &rz){
	this->angle = angle;
	axis.setVector(rx, ry, rz);
}

// -------------------------------------------------------------------------

Cube::Cube():Polyhedron(){
	noFaces = 6;
	noVertices = 4;
	vertices.resize(8);
	
	vertices[0] = Point(-0.5, -0.5, -0.5);
	vertices[1] = Point( 0.5, -0.5, -0.5);
	vertices[2] = Point(-0.5, -0.5,  0.5);
	vertices[3] = Point( 0.5, -0.5,  0.5);
	vertices[4] = Point(-0.5,  0.5, -0.5);
	vertices[5] = Point(-0.5,  0.5,  0.5);
	vertices[6] = Point( 0.5,  0.5, -0.5);
	vertices[7] = Point( 0.5,  0.5,  0.5);
	
	int tempFaces[ noFaces ][ noVertices ] =
	{
		{ 0, 1, 3, 2 },
		{ 0, 2, 5, 4 },
		{ 2, 3, 7, 5 },
		{ 5, 7, 6, 4 },
		{ 1, 6, 7, 3 },
		{ 1, 0, 4, 6 }
	};
	
	faces.resize(noFaces);
	for(int i=0 ; i<noFaces ; ++i){
		faces[i].insert(faces[i].end(), &tempFaces[i][0], &tempFaces[i][noVertices]);
	}
	
	colors.resize(noFaces);
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(0.0, 1.0);
	for(short i=0 ; i<noFaces ; ++i)
		this->colors[i] = (Color(dist(mt), dist(mt), dist(mt)));
}

Cube::Cube(Color &side1, Color &side2, Color &side3, Color &side4, Color &side5, Color &side6):Polyhedron(){
	noFaces = 6;
	noVertices = 4;
	vertices.resize(8);
	
	vertices[0] = Point(-0.5, -0.5, -0.5);
	vertices[1] = Point( 0.5, -0.5, -0.5);
	vertices[2] = Point(-0.5, -0.5,  0.5);
	vertices[3] = Point( 0.5, -0.5,  0.5);
	vertices[4] = Point(-0.5,  0.5, -0.5);
	vertices[5] = Point(-0.5,  0.5,  0.5);
	vertices[6] = Point( 0.5,  0.5, -0.5);
	vertices[7] = Point( 0.5,  0.5,  0.5);
	
	int tempFaces[ noFaces ][ noVertices ] =
	{
		{ 0, 1, 3, 2 },
		{ 0, 2, 5, 4 },
		{ 2, 3, 7, 5 },
		{ 5, 7, 6, 4 },
		{ 1, 6, 7, 3 },
		{ 1, 0, 4, 6 }
	};
	
	faces.resize(noFaces);
	for(int i=0 ; i<noFaces ; ++i){
		faces[i].insert(faces[i].end(), &tempFaces[i][0], &tempFaces[i][noVertices]);
	}
	
	colors.push_back(side1);
	colors.push_back(side2);
	colors.push_back(side3);
	colors.push_back(side4);
	colors.push_back(side5);
	colors.push_back(side6);
}

// -------------------------------------------------------------------------

Octahedron::Octahedron():Polyhedron(){
	noFaces = 8;
	noVertices = 3;
	vertices.resize(6);
	
	vertices[0] = Point(-0.5,          0, -0.5);
	vertices[1] = Point( 0.5,          0, -0.5);
	vertices[2] = Point(-0.5,          0,  0.5);
	vertices[3] = Point( 0.5,          0,  0.5);
	vertices[4] = Point(   0,   _SQRT3_2,    0);
	vertices[5] = Point(   0,  -_SQRT3_2,    0);
	
	int tempFaces[ noFaces ][ noVertices ] =
	{
		{ 0, 2, 4},
		{ 0, 4, 1},
		{ 1, 4, 3},
		{ 2, 3, 4},
		{ 2, 5, 3},
		{ 1, 3, 5},
		{ 0, 1, 5},
		{ 0, 5, 2}
	};
	
	faces.resize(noFaces);
	for(int i=0 ; i<noFaces ; ++i){
		faces[i].insert(faces[i].end(), &tempFaces[i][0], &tempFaces[i][noVertices]);
	}
	
	colors.resize(noFaces);
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(0.0, 1.0);
	for(short i=0 ; i<noFaces ; ++i)
		this->colors[i] = (Color(dist(mt), dist(mt), dist(mt)));
}

Octahedron::Octahedron(Color &side1, Color &side2, Color &side3, Color &side4, Color &side5, Color &side6, Color &side7, Color &side8):Polyhedron(){
	noFaces = 8;
	noVertices = 3;
	vertices.resize(6);
	
	vertices[0] = Point(-0.5,          0, -0.5);
	vertices[1] = Point( 0.5,          0, -0.5);
	vertices[2] = Point(-0.5,          0,  0.5);
	vertices[3] = Point( 0.5,          0,  0.5);
	vertices[4] = Point(   0,   _SQRT3_2,    0);
	vertices[5] = Point(   0,  -_SQRT3_2,    0);
	
	int tempFaces[ noFaces ][ noVertices ] =
	{
		{ 0, 2, 4},
		{ 0, 4, 1},
		{ 1, 4, 3},
		{ 2, 3, 4},
		{ 2, 5, 3},
		{ 1, 3, 5},
		{ 0, 1, 5},
		{ 0, 5, 2}
	};
	
	faces.resize(noFaces);
	for(int i=0 ; i<noFaces ; ++i){
		faces[i].insert(faces[i].end(), &tempFaces[i][0], &tempFaces[i][noVertices]);
	}
	
	colors.push_back(side1);
	colors.push_back(side2);
	colors.push_back(side3);
	colors.push_back(side4);
	colors.push_back(side5);
	colors.push_back(side6);
	colors.push_back(side7);
	colors.push_back(side8);
}

// -------------------------------------------------------------------------

Tetrahedron::Tetrahedron():Polyhedron(){
	noFaces = 4;
	noVertices = 3;
	vertices.resize(4);
	
	vertices[0] = Point(   0, -_SQRT6_6,  _SQRT3_3);
	vertices[1] = Point(-0.5, -_SQRT6_6, -_SQRT3_6);
	vertices[2] = Point( 0.5, -_SQRT6_6, -_SQRT3_6);
	vertices[3] = Point(   0,  _SQRT6_6,         0);
	
	int tempFaces[ noFaces ][ noVertices ] =
	{
		{ 1, 2, 0},
		{ 1, 0, 3},
		{ 1, 3, 2},
		{ 2, 3, 0}
	};
	
	faces.resize(noFaces);
	for(int i=0 ; i<noFaces ; ++i){
		faces[i].insert(faces[i].end(), &tempFaces[i][0], &tempFaces[i][noVertices]);
	}
	
	colors.resize(noFaces);
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(0.0, 1.0);
	for(short i=0 ; i<noFaces ; ++i)
		this->colors[i] = (Color(dist(mt), dist(mt), dist(mt)));
}

Tetrahedron::Tetrahedron(Color &side1, Color &side2, Color &side3, Color &side4):Polyhedron(){
	noFaces = 4;
	noVertices = 3;
	vertices.resize(4);
	
	vertices[0] = Point(   0, -_SQRT6_6,  _SQRT3_3);
	vertices[1] = Point(-0.5, -_SQRT6_6, -_SQRT3_6);
	vertices[2] = Point( 0.5, -_SQRT6_6, -_SQRT3_6);
	vertices[3] = Point(   0,  _SQRT6_6,         0);
	
	int tempFaces[ noFaces ][ noVertices ] =
	{
		{ 1, 2, 0},
		{ 1, 0, 3},
		{ 1, 3, 2},
		{ 2, 3, 0}
	};
	
	faces.resize(noFaces);
	for(int i=0 ; i<noFaces ; ++i){
		faces[i].insert(faces[i].end(), &tempFaces[i][0], &tempFaces[i][noVertices]);
	}
	
	colors.push_back(side1);
	colors.push_back(side2);
	colors.push_back(side3);
	colors.push_back(side4);
}

// -------------------------------------------------------------------------

TPrism::TPrism():Polyhedron(){
	noFaces = 5;
	noVertices = 4;
	vertices.resize(6);
	
	vertices[0] = Point(   0, -0.5,  _SQRT3_3);
	vertices[1] = Point(-0.5, -0.5, -_SQRT3_6);
	vertices[2] = Point( 0.5, -0.5, -_SQRT3_6);
	vertices[3] = Point(   0,  0.5,  _SQRT3_3);
	vertices[4] = Point(-0.5,  0.5, -_SQRT3_6);
	vertices[5] = Point( 0.5,  0.5, -_SQRT3_6);
	
	int tempFaces[ noFaces ][ noVertices ] =
	{
		{ 0, 1, 2, 0},
		{ 5, 4, 3, 5},
		{ 0, 3, 4, 1},
		{ 1, 4, 5, 2},
		{ 2, 5, 3, 0}
	};
	
	faces.resize(noFaces);
	for(int i=0 ; i<noFaces ; ++i){
		faces[i].insert(faces[i].end(), &tempFaces[i][0], &tempFaces[i][noVertices]);
	}
	
	colors.resize(noFaces);
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(0.0, 1.0);
	for(short i=0 ; i<noFaces ; ++i)
		this->colors[i] = (Color(dist(mt), dist(mt), dist(mt)));
}

TPrism::TPrism(Color &side1, Color &side2, Color &side3, Color &side4):Polyhedron(){
	noFaces = 5;
	noVertices = 4;
	vertices.resize(6);
	
	vertices[0] = Point(   0, -0.5,  _SQRT3_3);
	vertices[1] = Point(-0.5, -0.5, -_SQRT3_6);
	vertices[2] = Point( 0.5, -0.5, -_SQRT3_6);
	vertices[3] = Point(   0,  0.5,  _SQRT3_3);
	vertices[4] = Point(-0.5,  0.5, -_SQRT3_6);
	vertices[5] = Point( 0.5,  0.5, -_SQRT3_6);
	
	int tempFaces[ noFaces ][ noVertices ] =
	{
		{ 0, 1, 2, 2},
		{ 5, 4, 3, 3},
		{ 0, 3, 4, 1},
		{ 1, 4, 5, 2},
		{ 2, 5, 1, 0}
	};
	
	faces.resize(noFaces);
	for(int i=0 ; i<noFaces ; ++i){
		faces[i].insert(faces[i].end(), &tempFaces[i][0], &tempFaces[i][noVertices]);
	}
	
	colors.push_back(side1);
	colors.push_back(side2);
	colors.push_back(side3);
	colors.push_back(side4);
}

// -------------------------------------------------------------------------

Polyhedra::Polyhedra(){ }

unsigned int Polyhedra::size(){
	return poly.size();
}

void Polyhedra::addPolyhedron(std::string name, Polyhedron *polyhedron){
	poly[name] = polyhedron;
}

void Polyhedra::renderAll(){
	std::unordered_map<std::string,Polyhedron*>::iterator it;
	for(it = poly.begin() ; it!=poly.end() ; it++){
		glPopMatrix();
		glPushMatrix();
		it->second->render();
	}
}

void Polyhedra::translateAll(const float &tx, const float &ty, const float &tz){
	std::unordered_map<std::string,Polyhedron*>::iterator it;
	for(it = poly.begin() ; it!=poly.end() ; it++)
		it->second->translate(tx, ty, tz);
}

void Polyhedra::scaleAll(const float &sx, const float &sy, const float &sz){
	std::unordered_map<std::string,Polyhedron*>::iterator it;
	for(it = poly.begin() ; it!=poly.end() ; it++)
		it->second->scale(sx, sy, sz);
}

void Polyhedra::rotateAll(const float &angle, const float &rx, const float &ry, const float &rz){
	std::unordered_map<std::string,Polyhedron*>::iterator it;
	for(it = poly.begin() ; it!=poly.end() ; it++)
		it->second->rotate(angle, rx, ry, rz);
}

void Polyhedra::setTranslationAll(const float &tx, const float &ty, const float &tz){
	std::unordered_map<std::string,Polyhedron*>::iterator it;
	for(it = poly.begin() ; it!=poly.end() ; it++)
		it->second->setTranslation(tx, ty, tz);
}

void Polyhedra::setEscalationAll(const float &sx, const float &sy, const float &sz){
	std::unordered_map<std::string,Polyhedron*>::iterator it;
	for(it = poly.begin() ; it!=poly.end() ; it++)
		it->second->setEscalation(sx, sy, sz);
}

void Polyhedra::setRotationAll(const float &angle, const float &rx, const float &ry, const float &rz){
	std::unordered_map<std::string,Polyhedron*>::iterator it;
	for(it = poly.begin() ; it!=poly.end() ; it++)
		it->second->setRotation(angle, rx, ry, rz);
}

void Polyhedra::render(const std::string &name){
	poly[name]->render();
}

void Polyhedra::translate(const std::string name, const float &tx, const float &ty, const float &tz){
	poly[name]->translate(tx, ty, tz);
}

void Polyhedra::scale(const std::string name, const float &sx, const float &sy, const float &sz){
	poly[name]->scale(sx, sy, sz);
}

void Polyhedra::rotate(const std::string name, const float &angle, const float &rx, const float &ry, const float &rz){
	poly[name]->rotate(angle, rx, ry, rz);
}

void Polyhedra::setTranslation(const std::string name, const float &tx, const float &ty, const float &tz){
	poly[name]->setTranslation(tx, ty, tz);
}

void Polyhedra::setEscalation(const std::string name, const float &sx, const float &sy, const float &sz){
	poly[name]->setEscalation(sx, sy, sz);
}

void Polyhedra::setRotation(const std::string name, const float &angle, const float &rx, const float &ry, const float &rz){
	poly[name]->setRotation(angle, rx, ry, rz);
}

Polyhedra::~Polyhedra(){
	poly.clear();
}

#endif //__POLYHEDRA__HXX__
