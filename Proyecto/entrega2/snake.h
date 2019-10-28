#ifndef __SNAKE__H__
#define __SNAKE__H__


#include <chrono>
#include "camera.h"
#include "vector.h"
#include <GL/glu.h>

class Snake
{
private:
    // snake reqs:speed; tail
    float speed; //(unds/sec)
    //snake upd neds to know how much time
    std::chrono::time_point<std::chrono::high_resolution_clock> lastPosTime; //time when last pos


    //snake spatial data:: it does behave like a cam
    Vector s_position;
    Vector s_forward;
    Vector s_up;
    Vector s_right;

    int worldSize;
//nop    Vector s_rots;





public:
GLUquadric* tempquad;
     Snake(/* args */);
     Snake(int worldSize= 30, float speed = 1);

    ~ Snake();

    float getSpeed();
    Vector getPos();
    Vector getFwd ();
    Vector getUp ();
    Vector getRgt ();

    void setPos();
    void setFwd ();
    void setUp ();
    void setRgt ();

    void setSpeed(float s);
    void update();
    void rotate(char direction, float degree = 90);

};

#include "snake.hxx"

#endif
