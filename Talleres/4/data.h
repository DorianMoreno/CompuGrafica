#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <algorithm>

struct DtCoord{
    float x,y;
};
struct DtColour{
    int r,g,b;
    //perhaps predefined colours
    //and 0<=r,g,b,<=255
};

//struct Element{
struct Component{

char type; // s,c,t >> square, circle,triangle
DtColour colour;
DtCoord pIni,pEnd;//as in the coords of the rectangle in which the shape fits
float low,high,left,right;//\in (0,1) how much space of the element it takes
//as in if the prim is in a 0,1 square where does this element start/end

void calcCoords(DtCoord lb,DtCoord rt){ //left bottom ; right top
float dx = rt.x - lb.x, dy =rt.y - rt.y;
pIni.x = lb.x+dx*low  ; pIni.y = lb.y + dy*left;
pEnd.x = lb.x+dx*high ; pEnd.y = lb.y + dy*right;
}

};

struct Prim{


};

void DrawCircle( GLenum mode, unsigned int samples );
void DrawSquare( GLenum mode );
void DrawTriangle( GLenum mode );
void drawScaleTranslate ( float tx, float ty, float sx, float sy, int r, int g, int b, char tp);
void DrawBase( );
void Init( );
void ResizeCbk( int width, int height );
void DisplayCbk( );
