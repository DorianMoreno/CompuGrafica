
#include <GL/glut.h>
#include <iostream>
#include <sstream>
#include "Camera.h"
#include "Mesh.h"
#include <unordered_map>
#include <deque>
#include <chrono>
#include "Quatx.h"
#include "Snake.h"

Camera cam;
Mesh* mesh;
GLenum mode = GL_POLYGON;
std::chrono::time_point< std::chrono::high_resolution_clock > lastTime; //last fps report
ulong   frames;
GLuint  dispList;

Snake* snk = new Snake(5, 0);

void init( int argc, char* argv[] );//siempre init nunca ininit
void ininit( );


void displayCbk( );
void idleCbk( );
void resizeCbk( int w, int h );
void keydown( unsigned char key, int x, int y );
void keyup( unsigned char key, int x, int y );
void spcdown(int k, int x, int y );
void spcup(int k, int x, int y );
void mouseClickCbk( int button, int state, int x, int y );
void mouseMoveCbk( int x, int y );
int fpsHelper();



void init(int argc, char* argv[]){
    cam.setFOV( 45 );
    cam.setPlanes( 1e-2, 10000 );
    cam.move( Vector( 0, 0, 15 ) );
    cam.lookAt( Vector( 0, 0, 0 ) );
    glClearColor(0,0,0,0);
    frames =0;
    lastTime = std::chrono::high_resolution_clock::now();
    if( argc < 2 )
        throw std::runtime_error(
        std::string( "Usage: " ) + argv[ 0 ] + "<mesh name>"
    );
    mesh = new Mesh(argv[1]);
    dispList = glGenLists(2);
    glNewList(dispList, GL_COMPILE);
    {
      mesh->drawInOpenGLContext(mode);
    }
    glNewList(dispList+1, GL_COMPILE);
    {
      glColor3f(1,0,1);
      glBegin(GL_LINE);
      {
        glVertex3f ( -100, 0, 0 );
        glVertex3f (  100, 0, 0 );
      }
      glEnd();
      glBegin(GL_LINE);
      {
        glVertex3f ( 0, -100, 0 );
        glVertex3f ( 0,  100, 0 );
      }
      glEnd();
      glBegin(GL_LINE);
      {
        glVertex3f ( 0, 0, -100 );
        glVertex3f ( 0, 0,  100 );
      }
      glEnd();
    }
    glEndList();
} 

void ininit(){
    delete mesh;
}

void displayCbk( )
{
  frames++;
  int fps = fpsHelper(); 
    if ( fps > 0  ) {std::cout<<"fps:"<<fps<<std::endl;}

  glutWarpPointer(
    glutGet(GLUT_WINDOW_WIDTH) / 2, 
    glutGet(GLUT_WINDOW_HEIGHT) / 2 );


  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity( );

  // Prepare model matrix
  float dist = (cam.getPos() - snk->getPos()).getNorm();
  //cam.forward ( dist);  
  //std::cout<<"c2S::"<<dist<<std::endl;
  //std::cout<<"speed::"<<snk->getSpeed()<<std::endl;
  cam.loadCameraMatrix( );
  glPushMatrix();
 
  snk->update();
  
  // Draw the scene
  //mesh->drawInOpenGLContext(mode); 
  //glCallList(dispList);
  //glCallList(dispList+1);
  glPopMatrix();
  glPushMatrix();
 
 
  glutSwapBuffers( );
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
//------------------------------
void idleCbk( )
{
    
    
  glutPostRedisplay( );
}

// -------------------------------------------------------------------------
void resizeCbk( int w, int h )
{
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity( );
  cam.setWindow( w, h );
  cam.loadProjectionMatrix( );
}
// -------------------------------------------------------------------------
void mouseClickCbk( int button, int state, int x, int y )
{
  if( state == GLUT_DOWN )
    cam.setReference( x, y );
  else
    cam.setReference( 0, 0 );
}

// -------------------------------------------------------------------------
void mouseMoveCbk( int x, int y )
{
  float rotx = (float)(x - glutGet(GLUT_WINDOW_WIDTH)/2); 
  float roty = (float)(y - glutGet(GLUT_WINDOW_HEIGHT)/2);
  static float f =15;
  int dx, dy;
  cam.rotX( -roty/f );
  cam.rotY( -rotx/f );

}

void keydown( unsigned char key, int x, int y )
{
  float speed = 0.7f; 
  Quaternion rQuat;
  
  switch( key ) 
  {
  
  case 'w': case 'W':
  {
    cam.forward( speed ) ;
    glutPostRedisplay( );
  }
    break;
  case 's': case 'S':
  {
    cam.forward( -speed) ;
    glutPostRedisplay( );
  }
    break;
  case 'a': case 'A':
  {
    cam.strafe( -speed ) ;
    glutPostRedisplay( );
  }
    break;
  case 'd': case 'D':
  {
    cam.strafe( speed ) ;
    glutPostRedisplay( );
  }
    break;

  case 'r': case 'R':
    cam.upward(speed);
    glutPostRedisplay( );
    break;
  
  case 'f': case 'F':
    cam.upward(-speed);
    glutPostRedisplay( );
    break;

  case 'q':case 'Q':
    cam.rotZ(- speed/10);
    glutPostRedisplay( );
    break;

  case 'e':case 'E':
    cam.rotZ(speed/10);
    glutPostRedisplay( );
    break;   
  case 'v':case 'V':
    snk->setSpeed(0);
    break; 
  case 'p':case 'P':
    snk->setSpeed(snk->getSpeed()+0.01);
    break; 
  case 'i':
    snk->rotate('u');
    break; 
  case 'k':
    snk->rotate('d');
    break; 
  case 'j':
    snk->rotate('l');
    break; 
  case 'l':
    snk->rotate('r');
    break; 
  
  case 27: // ESC
    std::exit( 0 );
    break;
  default:
    break;
  } // end switch
}


int main( int argc, char* argv[] )
{
  // Init OpenGL context
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
  glutInitWindowPosition( 50, 50 );
  glutInitWindowSize( 1024, 768 );
  glutCreateWindow( "fancy ball and arm (non)game." );

  // Init world
  try
  {

    init( argc, argv );//assigns primum and some other stuff

    //glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
    glutDisplayFunc( displayCbk );
    glutIdleFunc( idleCbk );
    glutReshapeFunc( resizeCbk );

    glutKeyboardFunc( keydown );
    //glutKeyboardUpFunc(keyup);
    //glutSpecialFunc(spcdown );
    //glutSpecialUpFunc(spcup);

    glutMouseFunc( mouseClickCbk );
    glutPassiveMotionFunc( mouseMoveCbk );
    glutSetCursor( GLUT_CURSOR_CROSSHAIR );
    glutMainLoop( );

    ininit(  );
    return( 0 );
  }
  catch( std::exception& err )
  {
    std::cerr << err.what( ) <<"this is an error."<< std::endl;
    return( 1 );
  } // end if
}