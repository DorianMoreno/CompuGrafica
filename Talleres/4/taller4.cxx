/* -------------------------------------------------------------------------
 * @brief Example on how to draw simple 2D shapes
 * @author Leonardo Fl�rez-Valencia (florez-l@javeriana.edu.co)
 * -------------------------------------------------------------------------
 * Compilation on linux:
 *
 * g++ -std=c++17 taller4.cxx -lm -lGL -lGLU -lglut -o taller4
 *
 * -------------------------------------------------------------------------
 */

#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <algorithm>

struct color
{
	float r;
	float g;
	float b;

	color()
	{
		this->r = this->g = this->b = 1.0;
	}

	color(float r, float g, float b)
	{
		this->r = r;
		this->g = g;
		this->b = b;
	}
};

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
void drawScaleTranslate( float tx, float ty, float sx, float sy, float r, float g, float b, char tp){
	glLoadIdentity();
	glColor3f( r, g, b );
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

//--------------------------------------------------------------------------

void drawTruck(float posX, float posY, float width, float height, color body, color wheels)
{
	//TRUCK
	drawScaleTranslate(0.35416666666*width + posX,  0.69565217391*height + posY, 0.70833333333*width, 0.86956521739*height,   body.r,   body.g,   body.b, 's');		//Cargo
	drawScaleTranslate(0.85416666666*width + posX,  0.47826086956*height + posY, 0.29166666666*width, 0.43478260869*height,   body.r,   body.g,   body.b, 's');		//Cabin
	drawScaleTranslate(        0.125*width + posX,   0.1304347826*height + posY,        0.0625*width,  0.1304347826*height, wheels.r, wheels.g, wheels.b, 'c');		//Back wheel
	drawScaleTranslate(0.58333333333*width + posX,   0.1304347826*height + posY,        0.0625*width,  0.1304347826*height, wheels.r, wheels.g, wheels.b, 'c');		//Front wheel
}

void drawTruckWidthRatio(float posX, float posY, float width, float sizeRatio, color body, color wheels)
{
	float ratio = 0.47916666666;
	drawTruck(posX, posY, width, width*ratio*sizeRatio, body, wheels);
}

void drawTruckHeightRatio(float posX, float posY, float height, float sizeRatio, color body, color wheels)
{
	float ratio = 0.47916666666;
	drawTruck(posX, posY, height/ratio*sizeRatio, height, body, wheels);
}

//--------------------------------------------------------------------------

void drawRoad(float posX, float posY, float width, float height, color asphalt)
{
	//ROAD
	drawScaleTranslate(0.5*width + posX, 0.5*height + posY, width, height, asphalt.r, asphalt.g, asphalt.b, 's');	//Road
}
//--------------------------------------------------------------------------

void drawHouse(float posX, float posY, float width, float height, color structure, color roof)
{
  	//HOUSE
	drawScaleTranslate(0.5*width+posX, 0.33270043502*height+posY, 0.49056603773*width, 0.66540087004*height, structure.r, structure.g, structure.b, 's'); 	//Structure
	drawScaleTranslate(0.5*width+posX, 0.83270043502*height+posY,               width,  0.3863617955*height,      roof.r,      roof.g,      roof.b, 't');		//Roof
}

void drawHouseWidthRatio(float posX, float posY, float width, float sizeRatio, color structure, color roof)
{
	float ratio = 0.87902749562;
	drawHouse(posX, posY, width, width*ratio*sizeRatio, structure, roof);
}

void drawHouseHeightRatio(float posX, float posY, float height, float sizeRatio, color structure, color roof)
{
	float ratio = 0.87902749562;
	drawHouse(posX, posY, height/ratio*sizeRatio, height, structure, roof);
}

//--------------------------------------------------------------------------

void drawTree(float posX, float posY, float width, float height, color trunk, color leafs)
{
	//TREE
	drawScaleTranslate( 0.5*width + posX, 0.22394030468*height + posY, 0.52631578947*width, 0.44788060937*height, trunk.r, trunk.g, trunk.b, 's');			//Trunk
	drawScaleTranslate( 0.5*width + posX, 0.62796588839*height + posY,               width, 0.41588913727*height, leafs.r, leafs.g, leafs.b, 't');		//Leaf 1
	drawScaleTranslate( 0.5*width + posX, 0.72394030468*height + posY,               width, 0.41588913727*height, leafs.r, leafs.g, leafs.b, 't');		//Leaf 2
	drawScaleTranslate( 0.5*width + posX, 0.81991472098*height + posY,               width, 0.41588913727*height, leafs.r, leafs.g, leafs.b, 't');		//Leaf 3
}

void drawTreeWidthRatio(float posX, float posY, float width, float sizeRatio, color trunk, color leafs)
{
	float ratio = 1.64517527627;
	drawTree(posX, posY, width, width*ratio*sizeRatio, trunk, leafs);
}

void drawTreeHeightRatio(float posX, float posY, float height, float sizeRatio, color trunk, color leafs)
{
	float ratio = 1.64517527627;
	drawTree(posX, posY, height/ratio*sizeRatio, height, trunk, leafs);
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

	drawRoad(0, 0, 1000, 1000, color(0, 0.6, 1));
	drawRoad(0, 0, 1000, 300, color(0.4, 0.4, 0.4));

	drawHouseWidthRatio(400, 300, 400, 1.5, color( 0.9, 0.9, 0), color(0.3, 0.2, 0.1));
	drawHouseWidthRatio(-100, 300, 400, 1.2, color(), color(0.75, 0.3, 0));

	drawTreeWidthRatio(  0, 300, 100, 2.3, color(0.25546875, 0.103125, 0.00640625), color(0, 0.45, 0));
	drawTreeWidthRatio(100, 300, 100, 2.3, color(0.25546875, 0.103125, 0.00640625), color(0, 0.45, 0));
	drawTreeWidthRatio(200, 300, 100, 2.3, color(0.25546875, 0.103125, 0.00640625), color(0, 0.45, 0));
	drawTreeWidthRatio(300, 300, 100, 2.3, color(0.25546875, 0.103125, 0.00640625), color(0, 0.45, 0));
	drawTreeWidthRatio(400, 300, 100, 2.3, color(0.25546875, 0.103125, 0.00640625), color(0, 0.45, 0));
	drawTreeWidthRatio(500, 300, 100, 2.3, color(0.25546875, 0.103125, 0.00640625), color(0, 0.45, 0));
	drawTreeWidthRatio(600, 300, 100, 2.3, color(0.25546875, 0.103125, 0.00640625), color(0, 0.45, 0));
	drawTreeWidthRatio(700, 300, 100, 2.3, color(0.25546875, 0.103125, 0.00640625), color(0, 0.45, 0));
	drawTreeWidthRatio(800, 300, 100, 2.3, color(0.25546875, 0.103125, 0.00640625), color(0, 0.45, 0));
	drawTreeWidthRatio(900, 300, 100, 2.3, color(0.25546875, 0.103125, 0.00640625), color(0, 0.45, 0));

	drawTreeWidthRatio(-50, 300, 100, 2.0, color(0.35546875, 0.203125, 0.06640625), color(0, 0.6, 0));
	drawTreeWidthRatio( 50, 300, 100, 2.0, color(0.35546875, 0.203125, 0.06640625), color(0, 0.6, 0));
	drawTreeWidthRatio(150, 300, 100, 2.0, color(0.35546875, 0.203125, 0.06640625), color(0, 0.6, 0));
	drawTreeWidthRatio(250, 300, 100, 2.0, color(0.35546875, 0.203125, 0.06640625), color(0, 0.6, 0));
	drawTreeWidthRatio(350, 300, 100, 2.0, color(0.35546875, 0.203125, 0.06640625), color(0, 0.6, 0));
	drawTreeWidthRatio(450, 300, 100, 2.0, color(0.35546875, 0.203125, 0.06640625), color(0, 0.6, 0));
	drawTreeWidthRatio(550, 300, 100, 2.0, color(0.35546875, 0.203125, 0.06640625), color(0, 0.6, 0));
	drawTreeWidthRatio(650, 300, 100, 2.0, color(0.35546875, 0.203125, 0.06640625), color(0, 0.6, 0));
	drawTreeWidthRatio(750, 300, 100, 2.0, color(0.35546875, 0.203125, 0.06640625), color(0, 0.6, 0));
	drawTreeWidthRatio(850, 300, 100, 2.0, color(0.35546875, 0.203125, 0.06640625), color(0, 0.6, 0));
	drawTreeWidthRatio(950, 300, 100, 2.0, color(0.35546875, 0.203125, 0.06640625), color(0, 0.6, 0));

	drawHouseHeightRatio(600, 300, 400, 1.0, color(0.4, 0.5, 0.6), color(0.6, 0.3, 0.2));
	drawRoad(0, 300, 1000, 20, color(0.2, 0.2, 0.2));

	drawTruckHeightRatio(100, 100, 160, 2.0, color(0, 0, 0.4), color(0, 0, 0));
	drawTruckHeightRatio(300, 320, 50, 1.0, color(0.7, 0, 0), color(0, 0, 0));
	drawTruckHeightRatio(50, 20, 180, 1.0, color(1, 1, 1), color(0, 0, 0));

	// Finish
	glutSwapBuffers( );
}

// -------------------------------------------------------------------------
int main( int argc, char* argv[] )
{
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
  glutInitWindowPosition( 50, 50 );
  int isws;//init square win size
  isws = (argc>1) ? atoi(argv[1]):1000;
  glutInitWindowSize( isws, isws );
  glutCreateWindow( "2D scene!!!" );
  glutDisplayFunc( DisplayCbk );
  glutReshapeFunc( ResizeCbk );
  Init( );
  glutMainLoop( );

  return( 0 );
}

// eof - mouse_click.cxx
