#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

typedef  std::pair<std::string, DtColour> pairNC; //par nombre color

struct DtCoord{
    float x,y;
};
struct DtColour{
    int r,g,b;
    //perhaps predefined colours
    //and 0<=r,g,b,<=255
    DtColour(){
        r = 128;
        g = 128;
        b = 128;
    }
    DtColour( int r, int g, int b){
        this -> r = r;
        this -> g = g;
        this -> b = b;
    }
};

//struct Element{
struct Component{

char type; // s,c,t >> square, circle,triangle
std::string name;
DtColour colour;
/*perhaps unneeded*/DtCoord pIni,pEnd;//as in the coords of the rectangle in which the shape fits
float bot,top,left,right;//\in (0,1) how much space of the element it takes
//as in if the prim is in a 0,1 square where does this element start/end

void calcCoords(DtCoord lb,DtCoord rt){ //left bottom ; right top
float dx = rt.x - lb.x, dy =rt.y - rt.y;
pIni.x = lb.x+dx*bot  ; pIni.y = lb.y + dy*left;
pEnd.x = lb.x+dx*top ; pEnd.y = lb.y + dy*right;
}

Component(){
    this->name = "";
    DtColour col;
    colour = col;
}

Component(std::string name){
    this->name = name;
    DtColour col;
    colour = col;
}
Component( float b, float t, float l, float r , DtColour col , std::string name){
    bot = b , top = t , left = l, right = r , colour = col, this->name = name;
}

bool operator<(const Component& oth){
    return this->name < oth.name;
}

};


struct Prim{
    std::vector<Component> components;

    void addcomp(float b, float t, float l, float r , DtColour defcol , std::string name){
        Component ncomp(b,t,l,r,defcol,name);
        components.push_back(ncomp);
    }
            //bottom-left ; delta   ;   
    void draw(DtCoord bl, DtCoord del , std::vector<pairNC> ColData ){
        std::sort(components.begin(), components.end() );

        std::sort(ColData.begin(), ColData.end(), /*lambda start */
            [] (pairNC f, pairNC s){ return (f.first) < (s.first); } /*lambda end */);
        std::vector<pairNC>::iterator colIt = ColData.begin();
        for (auto compIt: components)
        {
            compIt.draw();
            
        }
        
    }

};

//two ways to do this, min, max -> (init, dx , dy)
void defineTree(){//DtCoord min, DtCoord max,DtColour colCopa, DtColour colTrunk){
    Prim tree;

    /*/tree.addcomp(ratio , col , name);//...
    tree.draw(init , del|end , <pair>(id,col) );*/
    //...
    // -> luego tree.draw();

}


void DrawCircle( GLenum mode, unsigned int samples );
void DrawSquare( GLenum mode );
void DrawTriangle( GLenum mode );
void drawScaleTranslate ( float tx, float ty, float sx, float sy, int r, int g, int b, char tp);
void DrawBase( );
void Init( );
void ResizeCbk( int width, int height );
void DisplayCbk( );
