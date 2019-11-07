/* -------------------------------------------------------------------------
	Compilation on linux:

	g++ -std=c++17 entregaFinal.cxx -lm -lGL -lGLU -lglut -o entregaFinal

	Execution on linux (after compilation):

	./entregaFinal

	To move snake, use keys: W, A, S and D
   -------------------------------------------------------------------------
 */
#include "snake.h"
#include "camera.h"
#include "grid.h"
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <cmath>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>

// -------------------------------------------------------------------------

Camera myCamera;
Grid* myGrid;
std::chrono::time_point< std::chrono::high_resolution_clock > lastTime; //last fps report
ulong frames;
GLuint gridList;
Snake* snk;

//global vars (Camera, grid, snake, etc)

//--------------------------------------------------------------------------

//inits and destroyers
void initWorld( int argc, char* argv[] );
void destroyWorld();

// -------------------------------------------------------------------------
int fpsHelper();
void displayCbk( );
void idleCbk( );
void resizeCbk( int w, int h );
void keyboardCbk( unsigned char key, int x, int y );
void specialKeyboardCbk( int key, int x, int y);
void mouseClickCbk( int button, int state, int x, int y );
void mouseMoveCbk( int x, int y );

// -------------------------------------------------------------------------
int main( int argc, char* argv[] )
{
    //Init OpenGL context
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
	glutInitWindowPosition( 0, 0 );
	glutInitWindowSize( 1000 , 1000 );
	glutCreateWindow( "Entrega Final!" );

    // Init world
    try{
		initWorld(argc, argv);

        glutDisplayFunc( displayCbk );
        glutIdleFunc( idleCbk );
		glutReshapeFunc( resizeCbk );

        glutSpecialFunc( specialKeyboardCbk );
        glutKeyboardFunc( keyboardCbk);
        glutMouseFunc( mouseClickCbk );
        glutPassiveMotionFunc( mouseMoveCbk );
		glutSetCursor( GLUT_CURSOR_NONE );

		glutMainLoop(  );

        destroyWorld();
        return( 0 );
    }
    catch( std::exception& err ){
      std::cerr << err.what( ) << std::endl;
      return( 1 );
    } // end if

}
// -------------------------------------------------------------------------
void initWorld( int argc, char* argv[] ){

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);
	glDepthRange(0.0f, 1.0f);

	glEnable (GL_CULL_FACE);
	glCullFace (GL_BACK);

	float sectionNumber = 20;		//Number of sections on each side of the grid
	float initialSpeed = 1;			//Initial speed of snake, sections per second

	// Init grid
	myGrid = new Grid(sectionNumber);

	// Init Snake
	snk = new Snake(sectionNumber, initialSpeed);

    // OpenGL initialization
    glClearColor( 0, 0, 0, 0 );

    // Initialize 	camera
    myCamera.setFOV( 90 );
    myCamera.setPlanes( 1e-2, 10000 );
    myCamera.setPosition( Vector( 0, 0, 0 ) );
	myCamera.lookAt( Vector( 0, 0, -10 ) );

	gridList = glGenLists(1);
	glNewList(gridList, GL_COMPILE);
	{
		myGrid->draw();
	}
	glEndList();

	// Calculate frames
	frames =0;
	lastTime = std::chrono::high_resolution_clock::now();
}
// -------------------------------------------------------------------------
void destroyWorld()
{
	if( myGrid != nullptr )
		delete myGrid;
	// if( snk != nullptr )
	// 	delete snk;
}

//--------------------------------------------------------------------------
void keyboardCbk( unsigned char key, int x, int y )
{
	float speed = 0.7f;
    Quaternion rQuat;

    switch( key )
    {
	case 'w': case 'W':
		if(!myCamera.isTurning())
			myCamera.turn(snk->rotate('u'), 0.5/snk->getSpeed());
		break;
	case 's': case 'S':
		if(!myCamera.isTurning())
			myCamera.turn(snk->rotate('d'), 0.5/snk->getSpeed());
		break;
	case 'a': case 'A':
		if(!myCamera.isTurning())
			myCamera.turn(snk->rotate('l'), 0.5/snk->getSpeed());
		break;
	case 'd': case 'D':
		if(!myCamera.isTurning())
			myCamera.turn(snk->rotate('r'), 0.5/snk->getSpeed());
		break;
	case 'v':case 'V':
		snk->setSpeed(0);
		break;
	case 'p':case 'P':
		snk->setSpeed(snk->getSpeed()+0.01);
		break;
	case 27: // ESC
		std::exit( 0 );
		break;
	default:
break;
    } // end switch
}
// -------------------------------------------------------------------------
void specialKeyboardCbk( int key, int x, int y)
{
	switch(key){
		case GLUT_KEY_LEFT:
			if(!myCamera.isTurning())
				myCamera.turn(snk->rotate('l'), 0.5/snk->getSpeed());
			break;
		case GLUT_KEY_RIGHT:
			if(!myCamera.isTurning())
				myCamera.turn(snk->rotate('r'), 0.5/snk->getSpeed());
			break;
		case GLUT_KEY_UP:
			if(!myCamera.isTurning())
				myCamera.turn(snk->rotate('u'), 0.5/snk->getSpeed());
			break;
		case GLUT_KEY_DOWN:
			if(!myCamera.isTurning())
				myCamera.turn(snk->rotate('d'), 0.5/snk->getSpeed());
			break;
	}
	//glutPostRedisplay();
}

// -------------------------------------------------------------------------
void resizeCbk( int w, int h )
{
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity( );
  myCamera.setWindow( w, h );
  myCamera.loadProjectionMatrix( );
}
// -------------------------------------------------------------------------
int fpsHelper(){
    int fps = 0;
    double s =
    std::chrono::duration_cast< std::chrono::milliseconds >(
        std::chrono::high_resolution_clock::now( ) - lastTime
        ).count( );
    s/= 1000;

    if (s>3){
        fps = frames/s;
        frames = 0;
        lastTime = std::chrono::high_resolution_clock::now( );
    }
    return fps;
}
// -------------------------------------------------------------------------
void idleCbk( )
{
	glutPostRedisplay( );
}

// -------------------------------------------------------------------------
void mouseClickCbk( int button, int state, int x, int y )
{

}

// -------------------------------------------------------------------------
void mouseMoveCbk( int x, int y )
{
	float height = glutGet(GLUT_WINDOW_HEIGHT);
	float width = glutGet(GLUT_WINDOW_WIDTH);
	float dx = (float)(x - width/2);
	float dy = (float)(y - height/2);

	if(dx != 0)
		myCamera.rotH( snk->getForward(), -dx/50.0 );
	if(dy != 0)
		myCamera.rotV( snk->getForward(), -dy/50.0 );

	glutPostRedisplay( );
}

// -------------------------------------------------------------------------
void displayCbk( )
{
	frames++;
	int fps = fpsHelper();
	  if ( fps > 0  ) {std::cout<<"fps:"<<fps<<std::endl;}

	 glutWarpPointer(
	   glutGet(GLUT_WINDOW_WIDTH) / 2,
	   glutGet(GLUT_WINDOW_HEIGHT) / 2 );

	// Redraw
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glMatrixMode( GL_MODELVIEW );
	// Camara
	glLoadIdentity( );

	myCamera.loadCameraMatrix( );

	glCallList(gridList);

	glPushMatrix();
	snk->update();
	glPopMatrix();

	myCamera.setPosition(snk->getPosition());

	glutSwapBuffers( );
}
