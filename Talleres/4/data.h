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

struct Element{
char type; // s,c,t >> square, circle,triangle
DtColour colour;
DtCoord pIni,pEnd;//as in the square in which the shape fits
};

struct Component{
Element element;

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
