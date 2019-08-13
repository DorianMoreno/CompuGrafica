//  data as in the plural nominative of datum.
//  compile as:: (?)
//  g++ -o try fancydata.cxx -lGL -lGLU -lglut 

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>


using namespace std;

struct WindowData
{
  unsigned long Width, Height;
  double XMin, XMax, YMin, YMax;
};

struct puntil {
  float x,y; //coord
  float gr;//grosor
  float r,g,b;

    puntil(float px, float py, float pgr, float pr, float pg, float pb)
    {
        x = px;
        y = py;
        gr = pgr;
        r = pr;
        g =pg;
        b = pb;
    }
    
    puntil()
    {
        x = y = gr = r = g = b = 0.0;
    }
    
    void color(float rr, float gg, float bb)
    {
        r = rr;
        g = gg;
        b = bb;
    }
  };

float sqrt3 = sqrt(3);
WindowData winData;
std::vector<puntil> backgr, laRama;
//----------------------data;; algs:


//circular degrade center in left edge
// coords >> colour value (as in degrade)
float bgcolourfunc(float x, float y){//, float h, float w){
   x = x/(480) -1;
   y = y/(320/2) -1;
   float k =1-((1.8*x*x + .5*y*y)/2) , aux = 0;
   
  return std::max(aux, k);
}


//secuencia decreciente de 3 circulos (grosor y coordenadas).
void tricircsq(float xi, float yi, float xe, float ye, float gant, float gi, float dec, std::vector<puntil> &mem){
    puntil p1,p2,p3;
    float gtot = gant+gi;
    float ang = atan((ye-yi)/(xe-xi));
    p1.x = xi + (gtot*0.4*cos(ang)) , p1.y = yi + (gtot*0.4*sin(ang))   , p1.gr = gi;
    p2.x = xi                       , p2.y = p1.y                       , p2.gr = gi/4;
    p3.x = p1.x                     , p3.y = yi                         , p3.gr = gi/4;
    
    mem.push_back(p1);
    mem.push_back(p2);
    mem.push_back(p3);
    

    float xn = p1.x;
    float yn = p1.y;
    
     if (xn<xe)
        tricircsq(xn, yn, xe, ye, gi, gi*dec, dec, mem);
}

void circloid(float x, float y, float gross, std::vector<puntil> mem){
  puntil pc;
  pc.x = x, pc.y = y, pc.gr = gross, pc.r=0, pc.g=0, pc.b=0;
  gross/=2;
  while(gross > 15){


  }
}

void fillbg(){

    int x=0,y=0;
    float gross = 8;
    for (float x= 0; x < 480  ; x+=gross){
      for(float y= 0; y < 320 ; y+=gross){
        puntil p;
        p.x = x + gross/2, p.y = y + gross/2;
        p.gr = gross;
        float clint = bgcolourfunc(p.x,p.y);
        p.r = 1*clint/2;
        p.g = 1*clint/2;
        p.b = bgcolourfunc(p.x,p.y);
        backgr.push_back(p);
      }
    }

}

void puntilPainter(puntil p){

  glPointSize(p.gr);
  
  glColor3f(p.r,p.g,p.b);
  
  glBegin (GL_POINTS);
  
  glVertex2i(p.x,p.y);
  
  glEnd();

}

puntil negativecol(puntil p){
  p.r = 1 - p.r ;
  p.g = 1 - p.g ;
  p.b = 1 - p.b ;
  return p;
}

// -------------------------------------------------------------------------
void SpecialKeyboardCbk( int key, int x, int y )
{
}


//-----------------------------|| painter data

void myInit (void) {  
    glClearColor(1.0,1.0,1.0,1.0); 
    glEnable( GL_POINT_SMOOTH );
    }


void myDisplay (void) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); 
    
    glViewport(0, 0, winData.Width/2, winData.Height); 
    
    fillbg();

    for (auto pbg : backgr ) 
      puntilPainter(pbg);
    
    
    //for (auto pr: laRama)
    //  puntilPainter(pr);
    std::vector<puntil> mem;
    tricircsq(0, 0, 370, 240, 10.0, 10.0, 0.99, mem);
    tricircsq(0, 10, 370, 240, 15.0, 15.0, 0.99, mem);
    tricircsq(0, 20, 200, 180, 15.0, 15.0, 0.99, mem);
    tricircsq(70, 60, 230, 140, 15.0, 15.0, 0.99, mem);
    tricircsq(0, 10, 370, 240, 15.0, 15.0, 0.99, mem);
    tricircsq(0, 10, 370, 240, 15.0, 15.0, 0.99, mem);
    puntil cabeza;
    cabeza.x = 350, cabeza.y = 285, cabeza.gr=20;
    puntilPainter(cabeza);

    for(int i=0 ; i<mem.size() ; ++i)
    {
        puntilPainter(mem[i]);
    }
    
    glViewport(winData.Width/2, 0, winData.Width, winData.Height);
    
    for (auto pbg : backgr ) 
      puntilPainter(negativecol( pbg ) );
    
  glutSwapBuffers( );
    
}


void myResize (int w, int h) {
    
    winData.Width = w;
    winData.Height = ( h > 0 )? h: 1;
    //fillbg();
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity();

    gluOrtho2D(0,240, 0, 320);    
    
    glMatrixMode( GL_MODELVIEW );

}



int main (int argc, char** argv) {
    winData.Width = std::atoi( argv[ 1 ] );
    winData.Height = std::atoi( argv[ 2 ] );
    
    glutInit(&argc, argv); 
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
    
    glutInitWindowSize(480, 320); 
    
    glutInitWindowPosition(100, 100); 

    glutCreateWindow("Fancy Puntillistic stuff");  
    
    glutDisplayFunc(myDisplay); 
    glutSpecialFunc( SpecialKeyboardCbk );
    glutReshapeFunc(myResize); 
    
    myInit(); 
    
    glutMainLoop(); 
    
    return 0;

}
