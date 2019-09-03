#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "figuras.h"

// -------------------------------------------------------------------------
#define _PI      3.14159265359
#define _2PI     6.28318530718
#define _SQRT3   1.73205080757
#define _SQRT3_2 0.86602540378
#define _SQRT3_3 0.57735026919
#define _SQRT3_4 0.43301270189

#define WORLD_MIN_X  0
#define WORLD_MIN_Y  0
#define WORLD_MAX_X  1000
#define WORLD_MAX_Y  1000
#define RATIO 		 1
// -------------------------------------------------------------------------
Polyhedra poly;
// -------------------------------------------------------------------------
void Init( )
{
	glClearColor( 0.7, 0.7, 0.7, 0.0 );
	poly.addPolyhedron("octa", new Cube());
}

// -------------------------------------------------------------------------
void ResizeCbk( int width, int height )
{
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
	glViewport( 0, 0, width, height );

	// Ortho
	// glOrtho( -2, 6, 0, 8, -2, 200 );

	// Prespective
	gluPerspective(
		45,
		float( width ) / float( height ),
		0.01, 200
		);
}

// -------------------------------------------------------------------------
void DisplayCbk( )
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glMatrixMode( GL_MODELVIEW );
	
	glEnable (GL_CULL_FACE);
	glCullFace (GL_BACK);
	
	// Camara
	glLoadIdentity( );
	gluLookAt( 0, 0, 10, 0, 0, 0, 0, 1, 0 );

	//poly.setTranslation("octa", 1, 1, 0);
	//poly.setRotation("octa", -90, 0, 1, 0);
	poly.rotate("octa", 1, 0, 0, 1);
	poly.renderAll();
	
	// Cubo 1
	//~ glPushMatrix( );
	//~ glScalef( 3, 3, 3 );
	//~ DrawUnitaryCube( );

	//~ // Cubo 2
	//~ glPopMatrix( );
	//~ glPushMatrix( );
	//~ glScalef( 2, 1.5, 1 );
	//~ DrawUnitaryCube( );

	// Finish
	glutSwapBuffers( );
}

// -------------------------------------------------------------------------
int main( int argc, char* argv[] )
{
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
	glutInitWindowPosition( 50, 50 );
	glutInitWindowSize( 500, 500 );
	glutCreateWindow( "3D test!!!" );
	glutDisplayFunc( DisplayCbk );
	glutReshapeFunc( ResizeCbk );
	Init( );
	glutMainLoop( );

	return( 0 );
}

// eof
