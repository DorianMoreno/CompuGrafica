/* -------------------------------------------------------------------------
 * @brief Example on how to draw simple 2D shapes
 * @author Leonardo Flórez-Valencia (florez-l@javeriana.edu.co)
 * -------------------------------------------------------------------------
 * Compilation on linux:
 *
 * g++ -std=c++17 simple_2d_scene.cxx -lm -lGL -lGLU -lglut -o mySimple2DScene
 *
 * -------------------------------------------------------------------------
 */

#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <algorithm>

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
void DrawCircle( GLenum mode, unsigned int samples )
{
  glBegin( mode );
  for( unsigned int i = 0; i < samples; ++i )
  {
    float t = _2PI * float( i ) / float( samples );
    glVertex2f( std::cos( t ), std::sin( t ) );
  } // end if
  glEnd( );
}

// -------------------------------------------------------------------------
void DrawSquare( GLenum mode )
{
  glBegin( mode );
  {
    glVertex2f( -0.5, -0.5 );
    glVertex2f( -0.5,  0.5 );
    glVertex2f(  0.5,  0.5 );
    glVertex2f(  0.5, -0.5 );
  }
  glEnd( );
}

// -------------------------------------------------------------------------
void DrawTriangle( GLenum mode )
{
  glBegin( mode );
  {
    glVertex2f( -0.5, -_SQRT3_4 );
    glVertex2f(  0.5, -_SQRT3_4 );
    glVertex2f(    0,  _SQRT3_4 );
  }
  glEnd( );
}

//--------------------------------------------------------------------------
void ptnScaleRotate ( float tx, float ty, float sx, float sy, int r, int g, int b, char tp){
	glLoadIdentity();
	glColor3ub( r, g, b );
	glTranslatef(tx,ty,0);
	glScalef(sx,sy,1);
	switch(tp){
		case 's': //square
			DrawSquare(GL_POLYGON);
			break;
		case 'c': //circle
			DrawCircle(GL_POLYGON, 500);
			break;
		case 't': //triangle
			DrawTriangle(GL_POLYGON);
	}
}

// -------------------------------------------------------------------------
void DrawBase( )
{
  glBegin( GL_LINES );
  {
    glColor3f( 1, 0, 0 );
    glVertex2f( WORLD_MIN_X * 0.75, 0 );
    glVertex2f( WORLD_MAX_X * 0.75, 0 );

    glColor3f( 0, 1, 0 );
    glVertex2f( 0, WORLD_MIN_Y * 0.75 );
    glVertex2f( 0, WORLD_MAX_Y * 0.75 );
  }
  glEnd( );
}

// -------------------------------------------------------------------------
void Init( )
{
  glClearColor( 0.0, 0.0, 0.0, 0.0 );
}

// -------------------------------------------------------------------------
void ResizeCbk( int width, int height )
{
  height = std::max(1, height);
  int PortWidth, PortHeight;
  if(height >= RATIO*((float)width))
	{
	    PortWidth = width;
	    PortHeight = RATIO*PortWidth;
	}
	else
	{
	    PortHeight = height;
	    PortWidth = PortHeight/RATIO;
	}

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity( );
  glViewport( (width-PortWidth)/2, (height-PortHeight)/2, PortWidth, PortHeight );
  gluOrtho2D( WORLD_MIN_X, WORLD_MAX_X, WORLD_MIN_Y, WORLD_MAX_Y );
}

// -------------------------------------------------------------------------
void DisplayCbk( )
{
  // Reset viewport and model matrix
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity( );

  // Orthogonal base
  DrawBase( );

  /* TO TEST
     glTranslate[f/d]( sx, sy, 0 );
     glScale[f/d]( sx, sy, 1 );
     glRotate[f/d]( theta, 0, 0, 1 );
   */
  	char s = 's', c = 'c', t='t';

  	//CASA
	ptnScaleRotate( 500, 165, 210, 310, 255, 255, 255, s); 	//Bloque casa
	ptnScaleRotate( 500, 399, 530, 180, 255, 255, 255, t);	//Techo

	//PAVIMENTO
	ptnScaleRotate( 200, 25, 340, 30, 255, 255, 255, s);	//Pavimento

	//CAMION
	ptnScaleRotate( 145, 120, 170, 100, 255, 255, 255, s);	//Cuerpo camion
	ptnScaleRotate( 265, 95, 70, 50, 255, 255, 255, s);		//Cabeza camion
	ptnScaleRotate( 90, 55, 15, 15, 255, 255, 255, c);		//Rueda trasera
	ptnScaleRotate( 200, 55, 15, 15, 255, 255, 255, c);		//Rueda delantera

	//ARBOL
	ptnScaleRotate( 850, 90, 100, 160, 100, 80, 10, s);		//Tronco arbol
	ptnScaleRotate( 850, 225, 190, 130, 0, 153, 0, t);		//Copa 1
	ptnScaleRotate( 850, 255, 190, 130, 0, 153, 0, t);		//Copa 2
	ptnScaleRotate( 850, 285, 190, 130, 0, 153, 0, t);		//Copa 3

  /*

	ptnScaleRotate( , , , , 1, 1, 1, t);
	ptnScaleRotate( , , , , 1, 1, 1, t);

	*/
  // Finish
  glutSwapBuffers( );
}

// -------------------------------------------------------------------------
int main( int argc, char* argv[] )
{
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
  glutInitWindowPosition( 50, 50 );
  glutInitWindowSize( 1000, 1000 );
  glutCreateWindow( "2D test!!!" );
  glutDisplayFunc( DisplayCbk );
  glutReshapeFunc( ResizeCbk );
  Init( );
  glutMainLoop( );

  return( 0 );
}

// eof - mouse_click.cxx
