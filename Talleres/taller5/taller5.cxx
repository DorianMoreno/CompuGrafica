#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "polyhedra.h"

// -------------------------------------------------------------------------
#define WORLD_MIN_X  0
#define WORLD_MIN_Y  0
#define WORLD_MAX_X  1000
#define WORLD_MAX_Y  1000
#define RATIO 		 1
// -------------------------------------------------------------------------
Polyhedra poly;
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
	gluLookAt( 0, 0, 10, 0, 0, 0, 0, 1, 0 );
	
	glPushMatrix();
	
	//~ glPopMatrix();
	
	poly.renderAll();

	// Finish
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
