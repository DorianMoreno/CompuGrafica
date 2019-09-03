#ifndef __POLYHEDRA__H__
#define __POLYHEDRA__H__

#include<vector>
#include<unordered_map>

struct Point{
	float pos[3];			//pos[0] = x, pos[1] = y, pos[2] = z
	
	Point();
	Point(const float &x, const float &y, const float &z);
};

struct Color{
	float col[3];			//col[0] = r, col[1] = g, col[2] = b
	
	Color();
	
	Color(const float &r, const float &g, const float &b);
};

struct Vector{
	float x;
	float y;
	float z;
	
	Vector();
	Vector(const Point &a, const Point &b);
	Vector(const Vector &v);
	Vector(const float &x, const float &y, const float &z);
	
	void normalize();
	void setVector(const float &x, const float &y, const float &z);
};

struct Quaternion{
	float w;
	float x;
	float y;
	float z;
	
	Quaternion(float x, float y, float z, float w);
	Quaternion(const Vector &v, float angle);
	Quaternion getConjugate();
	
	Quaternion operator* (const Quaternion &rq) const;
	
	void normalize();
	void FromAxis(const Vector &v, float angle);
	void getAxisAngle(Vector *axis, float *angle);
};

// -------------------------------------------------------------------------

class Polyhedron{
	protected:
		int noFaces;										//Number of faces in the polyhedron
		int noVertices;										//Number of vertices in each face
		GLenum mode;
		float tx, ty, tz;									//Translation parameters
		float sx, sy, sz;									//Scaling parameters
		float angle;										//Rotation angle
		Vector axis;										//Rotation axis
		std::vector<Color> colors;							//Color of each side
		std::vector<Point> vertices;						//Coordinate of each vertex
		std::vector<std::vector<int> > faces;					//Vertices in each face
	public:
		Polyhedron(GLenum mode);
		
		void drawSides();
		void render();
		void translate(const float &tx, const float &ty, const float &tz);
		void scale(const float &sx, const float &sy, const float &sz);
		void rotate(const float &angle, const float &rx, const float &ry, const float &rz);
		void setTranslation(const float &tx, const float &ty, const float &tz);
		void setScaling(const float &sx, const float &sy, const float &sz);
		void setRotation(const float &angle, const float &rx, const float &ry, const float &rz);
};

// -------------------------------------------------------------------------

class Cube: public Polyhedron{
	public:
		Cube();
		Cube(Color &side1, Color &side2, Color &side3, Color &side4, Color &side5, Color &side6);
};

// -------------------------------------------------------------------------

class Octahedron: public Polyhedron{
	public:
		Octahedron();
		Octahedron(Color &side1, Color &side2, Color &side3, Color &side4, Color &side5, Color &side6, Color &side7, Color &side8);
};

// -------------------------------------------------------------------------

class Tetrahedron: public Polyhedron{
	public:
		Tetrahedron();
		Tetrahedron(Color &side1, Color &side2, Color &side3, Color &side4);
};

// -------------------------------------------------------------------------

class TPrism: public Polyhedron{
	public:
		TPrism();
		TPrism(Color &side1, Color &side2, Color &side3, Color &side4);
};

// -------------------------------------------------------------------------

class Polyhedra{
	private:
		std::unordered_map<std::string, Polyhedron*> poly;
	public:
		Polyhedra();
		
		unsigned int size();
		void addPolyhedron(std::string name, Polyhedron *polyhedron);
		
		void renderAll();
		void translateAll(const float &tx, const float &ty, const float &tz);
		void scaleAll(const float &sx, const float &sy, const float &sz);
		void rotateAll(const float &angle, const float &rx, const float &ry, const float &rz);
		void setTranslationAll(const float &tx, const float &ty, const float &tz);
		void setScalingAll(const float &sx, const float &sy, const float &sz);
		void setRotationAll(const float &angle, const float &rx, const float &ry, const float &rz);
		
		void render(const std::string &name);
		void translate(const std::string name, const float &tx, const float &ty, const float &tz);
		void scale(const std::string name, const float &sx, const float &sy, const float &sz);
		void rotate(const std::string name, const float &angle, const float &rx, const float &ry, const float &rz);
		void setTranslation(const std::string name, const float &tx, const float &ty, const float &tz);
		void setScaling(const std::string name, const float &sx, const float &sy, const float &sz);
		void setRotation(const std::string name, const float &angle, const float &rx, const float &ry, const float &rz);
		
		virtual ~Polyhedra();
};


#include "polyhedra.hxx"

#endif // __POLYHEDRA__H__
