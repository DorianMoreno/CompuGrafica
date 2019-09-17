/* -------------------------------------------------------------------------
  Compilation on linux:
 
  g++ -std=c++17 taller5.cxx -lm -lGL -lGLU -lglut -o taller5
 
   -------------------------------------------------------------------------
 */

#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "polyhedra.h"

// -------------------------------------------------------------------------
#define WORLD_MIN_X  0
#define WORLD_MIN_Y  0
#define WORLD_MAX_X  1000
#define WORLD_MAX_Y  1000
#define RATIO 		 1
// -------------------------------------------------------------------------
Polyhedra poly;
std::vector<CelestialObject*> objs;
// -------------------------------------------------------------------------

void SpecialKeyboardCbk( int key, int x, int y)
{
	switch(key){
		case GLUT_KEY_LEFT:
			poly.rotateAll(-1, 0, 1, 0);
			break;
		case GLUT_KEY_RIGHT:
			poly.rotateAll( 1, 0, 1, 0);
			break;
		case GLUT_KEY_UP:
			poly.rotateAll(-1, 1, 0, 0);
			break;
		case GLUT_KEY_DOWN:
			poly.rotateAll( 1, 1, 0, 0);
	}
	glutPostRedisplay();
}

// -------------------------------------------------------------------------
void Init( )
{
	glClearColor( 0.7, 0.7, 0.7, 0.0 );
	poly.addPolyhedron("Cub", new Cube());
	poly.setEscalation("Cub", 1.5, 1.5, 1.5);
	poly.setTranslation("Cub", 0, -2.0, 0);
	
	poly.addPolyhedron("Oct", new Octahedron());
	poly.setEscalation("Oct", 1.5, 1.5, 1.5);
	poly.setTranslation("Oct", 2.0, 0, 0);
	
	poly.addPolyhedron("Tet", new Tetrahedron());
	poly.setEscalation("Tet", 1.5, 1.5, 1.5);
	poly.setTranslation("Tet", -2.0, 0, 0);
	
	poly.addPolyhedron("TPr", new TPrism());
	poly.setEscalation("TPr", 1.5, 1.5, 1.5);
	poly.setTranslation("TPr", 0, 2.0, 0);

	//sun
	objs.push_back(new CelestialObject( ));
	objs.back()->setBody( new Cube() );
	objs.back()->setBdEscl(1, 1, 1);
	objs.back()->setPath(std::vector<Point> (1, Point(0,0,0)));
	objs.back()->setCenter(Point(0, 0, 0));
	
	//planet 1
	objs.push_back(new CelestialObject());
	objs.back()->setBody( new Tetrahedron() );
	objs.back()->setBdEscl(0.4, 0.4, 0.4);
	objs.back()->setPath( objs.back()->ellipticOrbit(1,2,Vector(0,0,-1)) );
	objs.back()->setCenter(Point(0, 0, 0));
	objs[0]->addSatellite("1",objs[1]); 
	//planet 2
	objs.push_back(new CelestialObject());
	objs.back()->setBody( new Cube() );
	objs.back()->setBdEscl(0.3, 0.3, 0.3);
	objs.back()->setPath( objs.back()->ellipticOrbit(2,1,Vector(0,0,-1)) );
	objs.back()->setCenter(Point(0, 0, 0));
	objs[0]->addSatellite("2",objs[2]);
	
	//planet 3
	objs.push_back(new CelestialObject());
	objs.back()->setBody( new TPrism() );
	objs.back()->setBdEscl(0.2, 0.2, 0.2);
	objs.back()->setPath( objs.back()->ellipticOrbit(4,3,Vector(0,0,-1)) );
	objs.back()->setCenter(Point(0, 0, 0));
	objs[0]->addSatellite("3",objs[3]);
	
	//planet 4
	objs.push_back(new CelestialObject());
	objs.back()->setBody( new Octahedron() );
	objs.back()->setBdEscl(0.5, 0.6, 0.7);
	objs.back()->setPath( objs.back()->ellipticOrbit(3,3,Vector(0,0,-1)) );
	objs.back()->setCenter(Point(0, 0, 0));
	objs[0]->addSatellite("4",objs[4]);

	//moon 1
	objs.push_back(new CelestialObject());
	objs.back()->setBody( new Tetrahedron() );
	objs.back()->setBdEscl(0.05, 0.05, 0.05);
	objs.back()->setPath( objs.back()->ellipticOrbit(.5,1,Vector(0,0,-1)) );
	objs.back()->setCenter(Point(0, 0, 0));
	objs[3]->addSatellite("5",objs[5]);
	
	//moon 2
	objs.push_back(new CelestialObject());
	objs.back()->setBody( new TPrism() );
	objs.back()->setBdEscl(0.02, 0.02, 0.02);
	objs.back()->setPath( objs.back()->ellipticOrbit(1,.2,Vector(0,0,-1)) );
	objs.back()->setCenter(Point(0, 0, 0));
	objs[3]->addSatellite("6",objs[6]);
	
	//moon 3
	objs.push_back(new CelestialObject());
	objs.back()->setBody( new Cube() );
	objs.back()->setBdEscl(0.05, 1, 0.01);
	objs.back()->setPath( objs.back()->ellipticOrbit(.5,1,Vector(0,0,-1)) );
	objs.back()->setCenter(Point(0, 0, 0));
	objs[1]->addSatellite("7",objs[7]);
	
	//moon 4
	objs.push_back(new CelestialObject());
	objs.back()->setBody( new Octahedron() );
	objs.back()->setBdEscl(0.1, 0.1, 0.1);
	objs.back()->setPath( objs.back()->ellipticOrbit(.5,1,Vector(0,0,-1)) );
	objs.back()->setCenter(Point(0, 0, 0));
	objs[2]->addSatellite("8",objs[8]);
	
//CelObj.ellipticOrbit(1,2,Vector(0,0,-1))


}

// -------------------------------------------------------------------------
void ResizeCbk( int width, int height )
{
	glViewport( 0, 0, width, height );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );

	// Ortho
	// glOrtho( -2, 6, 0, 8, -2, 200 );

	// Prespective
	gluPerspective(
		45,
		float( width ) / float( height ),
		0.01, 200
		);
	glMatrixMode( GL_MODELVIEW );
}

// -------------------------------------------------------------------------
void DisplayCbk( )
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	// Camara
	glLoadIdentity( );
	gluLookAt( 0, 0, 15, 0, 0, 0, 0, 1, 0 );
	
	glPushMatrix();
	

	//for(auto it: objs)
    objs[0]->renderCO();
	
	glPopMatrix();
	glutSwapBuffers( );
}

// -------------------------------------------------------------------------
int main( int argc, char* argv[] )
{
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition( 50, 50 );
	glutInitWindowSize( 500, 500 );
	glutCreateWindow( "3D test!!!" );
	glutDisplayFunc( DisplayCbk );
    glutSpecialFunc(SpecialKeyboardCbk );
	glutReshapeFunc( ResizeCbk );
	Init( );
	
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);
	glDepthRange(0.0f, 1.0f);
	glEnable (GL_CULL_FACE);
	glCullFace (GL_BACK);
	glutMainLoop( );

	return( 0 );
}

// eof
