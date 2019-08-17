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
  unsigned long PortWidth, PortHeight;
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
   x = x/(winData.Width) -1;
   y = y/(winData.Height/2) -1;
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
    backgr.clear();
    int x=0,y=0;
    float gross = 8;
    for (float x= 0; x < 480 /*winData.Width*/  ; x+=2*gross/4){
      for(float y= 0; y < 360 /*winData.Height*/ ; y+=2*gross/4){
        puntil p;
        p.x = x + gross/2;//(2*480*x + gross*winData.Width)/(2*winData.Width) ;// 480x /width + grosor/2
        p.y = y + gross/2;//(2*360*y + gross*winData.Height)/(2*winData.Height);  
        p.gr = gross;
        float clint = bgcolourfunc(p.x,p.y);
        p.r = 1*clint/2;
        p.g = 1*clint/2;
        p.b = clint;
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

puntil puntilIdentidad(puntil p){
  return p;
}

// -------------------------------------------------------------------------
void SpecialKeyboardCbk( int key, int x, int y )
{

  switch(key){
    
    case GLUT_KEY_RIGHT:
      if(winData.XMax <= 480){
        winData.XMin+=1;
        winData.XMax+=1;
      }
      break;
      
    case GLUT_KEY_LEFT:
      if (winData.XMin >0){
        winData.XMin-=1;
        winData.XMax-=1;
      } 
        break;
    case GLUT_KEY_UP:
      if (winData.YMax < 360){
        winData.YMin+=1;
        winData.YMax+=1;
      }
        break;
    case GLUT_KEY_DOWN:
      if (winData.YMin > 0){
        winData.YMin-=1;
        winData.YMax-=1;
      }
        break;
    case GLUT_KEY_END:
      quick_exit(0);

  }
  glutPostRedisplay();
}


//-----------------------------|| painter data

void myInit (void) {  
    glEnable( GL_POINT_SMOOTH );
    glClearColor(1.0,1.0,1.0,1.0); 
    winData.XMin = 0;
    winData.YMin = 0;
    winData.XMax = 480 / 2;
    winData.YMax = 320 / 2;
    }

void dispPainter(puntil (*mod)(puntil) ){
     
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
    

    for (auto pbg : backgr ) 
      puntilPainter(mod (pbg) );
 
    for(auto it :  mem)
        puntilPainter( mod( it ) );
    
    puntilPainter(mod (cabeza) );
}


void myDisplay (void) {

    fillbg();


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); 
    
    
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity();
    
    unsigned long heightDif = (winData.Height-winData.PortHeight)/2;
    
    glViewport(winData.Width/2 - winData.PortWidth, heightDif, winData.PortWidth, winData.PortHeight); 
    gluOrtho2D(winData.XMin ,winData.XMax, winData.YMin, winData.YMax);    
    glMatrixMode( GL_MODELVIEW );
    
    dispPainter(puntilIdentidad);
    
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity();
    glViewport(winData.Width/2, heightDif, winData.PortWidth, winData.PortHeight); 
    gluOrtho2D(winData.XMin ,winData.XMax, winData.YMin, winData.YMax);    
    glMatrixMode( GL_MODELVIEW );
    
    dispPainter(negativecol);
    
  glutSwapBuffers( );
    
}


void myResize (int w, int h) {
    
    winData.Width = w;
    winData.Height = max(h, 1);
    float ratio = 480.0/320.0;
    if(winData.Height >= ratio*((float)winData.Width)/2.0)
    {
        winData.PortWidth = winData.Width/2;
        winData.PortHeight = ratio*winData.PortWidth;
    }
    else
    {
        winData.PortHeight = winData.Height;
        winData.PortWidth = winData.PortHeight/ratio;
    }
    
}



int main (int argc, char** argv) {
    winData.Width = 240; //std::atoi( argv[ 1 ] );
    winData.Height = 160; //std::atoi( argv[ 2 ] );
    
    glutInit(&argc, argv); 
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
    
    glutInitWindowSize(winData.Width, winData.Height); 
    
    glutInitWindowPosition(100, 100); 

    glutCreateWindow("Fancy Puntillistic stuff");  
    
    glutDisplayFunc(myDisplay); 
    glutSpecialFunc(SpecialKeyboardCbk );
    glutReshapeFunc(myResize); 
    
    myInit(); 
    
    glutMainLoop(); 
    
    return 0;

}
