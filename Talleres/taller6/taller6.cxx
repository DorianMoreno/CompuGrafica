/* -------------------------------------------------------------------------
	Compilation on linux:

	g++ -std=c++17 taller6.cxx -lm -lGL -lGLU -lglut -o taller6

	Execution on linux (after compilation):

	./taller6 armadillo.obj

    or

    ./taller6 bunny.obj

	You can explore the world using WASD and the mouse
   -------------------------------------------------------------------------
 */

#include "mesh.h"
#include "light.h"
#include "camera.h"
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <cmath>
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <vector>

static GLfloat mat_specular[] = {1.0,1.0,1.0,1.0};
static GLfloat mat_shininess[] = {50.0};

std::chrono::time_point< std::chrono::high_resolution_clock > lastTime; //last fps report
Camera myCamera;
Mesh* myObject;
GLuint drawList;
ulong frames;
std::vector<Light> myLights;

//inits and destroyers
void initWorld( int argc, char* argv[] );
void destroyWorld();

/* predefine function names */
int fpsHelper();
void display(void);
void idleCbk( );
void resizeCbk( int w, int h );
void keyboardCbk( unsigned char key, int x, int y );
void specialKeyboardCbk( int key, int x, int y);
void mouseClickCbk( int button, int state, int x, int y );
void mouseMoveCbk( int x, int y );


/* main program - setup window using GLUT */
int
main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("taller6");

    // Init world
    try{
		initWorld(argc, argv);

        glutDisplayFunc( display );
        glutIdleFunc( idleCbk );
		glutReshapeFunc( resizeCbk );

        glutKeyboardFunc( keyboardCbk);
        glutMouseFunc( mouseClickCbk );
        glutMotionFunc( mouseMoveCbk );

		glutMainLoop(  );

        destroyWorld();
        return( 0 );
    }
    catch( std::exception& err ){
      std::cerr << err.what( ) << std::endl;
      return( 1 );
    } // end if

    glutMainLoop();
    return  0;
}

/* Initialisation of OpenGL */
void initWorld( int argc, char* argv[] )
{
    glEnable(GL_DEPTH_TEST);
    glDepthRange(0.0f, 0.10f);

    glEnable(GL_COLOR_MATERIAL);

    // glEnable (GL_CULL_FACE);
    // glCullFace (GL_BACK);

    if( argc < 2 )
       throw std::runtime_error(
       std::string( "Usage: " ) + argv[ 0 ] + " <mesh name>"
    );


    // OpenGL initialization
    glClearColor( 0.5, 0.5, 0.5, 0 );

    // Initialize camera
    myCamera.setFOV( 45 );
    myCamera.setPlanes( 1e-2, 10000 );
    myCamera.move( Vector( 0, 0, 5 ) );
	myCamera.lookAt( Vector( 0, 0, 0 ) );

    myObject = new Mesh(argv[1]);
    myObject->setColor(1, 1, 1);
	drawList = glGenLists(1);
	glNewList(drawList, GL_COMPILE);
	{
		myObject->drawInOpenGLContext(GL_POLYGON);
	}
	glEndList();

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    glShadeModel(GL_SMOOTH);
    // TODO: glShadeModel(GL_SMOOTH);

    glEnable(GL_LIGHTING);

    myLights.resize(8);
    glEnable(GL_LIGHT0);
    myLights[0].setLight(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    myLights[1].setLight(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    myLights[2].setLight(GL_LIGHT2);
    glEnable(GL_LIGHT3);
    myLights[3].setLight(GL_LIGHT3);
    glEnable(GL_LIGHT4);
    myLights[4].setLight(GL_LIGHT4);
    glEnable(GL_LIGHT5);
    myLights[5].setLight(GL_LIGHT5);
    glEnable(GL_LIGHT6);
    myLights[6].setLight(GL_LIGHT6);
    glEnable(GL_LIGHT7);
    myLights[7].setLight(GL_LIGHT7);

    // Calculate frames
    frames =0;
    lastTime = std::chrono::high_resolution_clock::now();
}

/* display function called by OpenGL */
void display(void)
{
    frames++;
    int fps = fpsHelper();
      if ( fps > 0  ) {std::cout<<"fps:"<<fps<<std::endl;}

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    myCamera.loadCameraMatrix( );

    glColor3f( 0, 1, 1 );
    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glTranslatef(0,0,-2);

    glCallList(drawList);

    for(int i=0 ; i<myLights.size() ; ++i)
        myLights[i].updatePosition();

    glutSwapBuffers( );
}

// -------------------------------------------------------------------------
void destroyWorld()
{
	if( myObject != nullptr )
		delete myObject;
}

//--------------------------------------------------------------------------
void keyboardCbk( unsigned char key, int x, int y )
{
	float speed = 0.7f;

    switch( key )
    {
        case 'w': case 'W':
        {
          myCamera.forward( 2 ) ;
          glutPostRedisplay( );
        }
          break;
        case 's': case 'S':
        {
          myCamera.forward( -2 ) ;
          glutPostRedisplay( );
        }
          break;
        case 'a': case 'A':
        {
          myCamera.strafe( -2 ) ;
          glutPostRedisplay( );
        }
          break;
        case 'd': case 'D':
        {
          myCamera.strafe( 2 ) ;
          glutPostRedisplay( );
        }
          break;
	case 27: // ESC
		std::exit( 0 );
		break;
	default:
break;
    } // end switch
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
  if( state == GLUT_DOWN )
    myCamera.setReference( x, y );
  else
    myCamera.setReference( 0, 0 );
}

// -------------------------------------------------------------------------
void mouseMoveCbk( int x, int y )
{
    int dx, dy;
    myCamera.getReference( dx, dy, x, y );
    myCamera.setReference( x, y );

	if(dx != 0)
		myCamera.rotH( -dx/20.0 );
	if(dy != 0)
		myCamera.rotV( -dy/20.0 );

	glutPostRedisplay( );
}
