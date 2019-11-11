/* -------------------------------------------------------------------------
	Compilation on linux:

	g++ -std=c++17 entregaFinal.cxx -lm -lGL -lGLU -lglut -o entregaFinal

	Execution on linux (after compilation):

	./entregaFinal

	To move snake, use keys: W, A, S and D
   -------------------------------------------------------------------------
 */
#include "game.h"
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <cmath>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>

// -------------------------------------------------------------------------
Game* myGame;

std::chrono::time_point< std::chrono::high_resolution_clock > lastTime; //last fps report
ulong frames;

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
	glutCreateWindow( "Entrega Final! (fps: --)" );

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
	glDepthRange(0.1f, 1.0f);

	glEnable (GL_CULL_FACE);
	glCullFace (GL_BACK);

	glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
	glShadeModel(GL_FLAT);
	glEnable(GL_COLOR_MATERIAL);

	// OpenGL initialization
	glClearColor( 0, 0, 0, 0 );

	myGame = new Game();

    //Prepare for calculating frames
    frames = 0;
    lastTime = std::chrono::high_resolution_clock::now();
}
// -------------------------------------------------------------------------
void destroyWorld()
{
	if( myGame != nullptr )
		delete myGame;
}

//--------------------------------------------------------------------------
void keyboardCbk( unsigned char key, int x, int y )
{
    switch( key )
    {
	case 27: // ESC
		std::exit( 0 );
		break;
	default:
		myGame->keyPress(key);
		break;
    } // end switch
}
// -------------------------------------------------------------------------
void specialKeyboardCbk( int key, int x, int y)
{
	myGame->specialKeyPress(key);
}

// -------------------------------------------------------------------------
void resizeCbk( int w, int h )
{
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
	myGame->resizeCamera(w, h);
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

	myGame->staticCameraRotation(dx, dy, 0.5, 0.5);

	glutPostRedisplay( );
}

// -------------------------------------------------------------------------
void displayCbk( )
{
	glutWarpPointer(
		glutGet(GLUT_WINDOW_WIDTH) / 2,
		glutGet(GLUT_WINDOW_HEIGHT) / 2 );

	frames++;
	int fps = fpsHelper();
	if ( fps > 0  ) {std::string aux = "Entrega Final! (fps: " + std::to_string(fps) + ")"; glutSetWindowTitle(aux.c_str());}

	// Redraw
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );

	glPushMatrix();
		myGame->draw();
	glPopMatrix();

	glutSwapBuffers( );
}
