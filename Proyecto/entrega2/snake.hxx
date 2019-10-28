#ifndef __SNAKE__HXX__
#define __SNAKE__HXX__

#include "snake.h"
#include <cmath>
#include <GL/glu.h>
#include <iostream>

Snake::
Snake(int wS, float s){

    tempquad = gluNewQuadric();
    GLfloat tempradii = 2;

    this->worldSize = wS;
    this->speed = s;
    this->lastPosTime = std::chrono::high_resolution_clock::now();
    s_position  = Vector( 0.5, 0.5, 0.5 );
    s_forward   = Vector( 0 , 0 , -1 );
    s_up        = Vector( 0 , 1 );
    s_right     = s_forward*s_up;
}


void Snake::
update(){
    float dx;
    double dt =
      std::chrono::duration_cast< std::chrono::milliseconds >(
        std::chrono::high_resolution_clock::now( ) - this->lastPosTime
        ).count( );
    dt /= 1000; //from mill to sec
    this->lastPosTime = std::chrono::high_resolution_clock::now();
    s_position += (s_forward * speed * dt);

    //if(pos > wS)-> wrap + add diff
    for (int i = 0; i<3;++i){
        // float temp = s_position[i];
        // temp-= worldSize/2.0;
        s_position[i] = fmod(worldSize + s_position[i], worldSize);
        // s_position[i] += temp;

      // if (abs(s_position[ i ]) > worldSize)
      // {
      //     std::cout<<"from: "<<s_position[i];
      //     dx = abs(s_position[ i ]) - (float)worldSize;
      //     s_position[ i ] *= -s_position[ i ]/s_position[ i ];
      //
      //     std::cout<<" to:: "<<s_position[i]<<" dx: "<<dx<<std::endl;
      //
      // }
    }

    // glPushMatrix();
    // glColor3f(1,0,0);
    // glTranslatef(s_position[0],s_position[1],s_position[2]);
    // gluSphere(tempquad,2,10,10);
    // glPopMatrix();

 }

Vector Snake::getPos(){
    return s_position;
}

void Snake::
rotate(char dir, float deg){
    float o = deg * _PI_180;

    this->s_position[0] = (int)this->s_position[0];
    this->s_position[0] += 0.5;
    this->s_position[1] = (int)this->s_position[1];
    this->s_position[1] += 0.5;
    this->s_position[2] = (int)this->s_position[2];
    this->s_position[2] += 0.5;

    switch (dir)
    {
    case 'u':
        this->s_forward =
          ( this->s_forward * std::cos( o ) ) +
          ( this->s_up * std::sin( o ) );
        this->s_forward.normalize( );

        this->s_up = ( this->s_forward * this->s_right ) * -1.0;
        break;
    case 'd':
        o*=-1;
        this->s_forward =
          ( this->s_forward * std::cos( o ) ) +
          ( this->s_up * std::sin( o ) );
        this->s_forward.normalize( );

        this->s_up = ( this->s_forward * this->s_right ) * -1.0;
        break;

    case 'r':
        o*=-1;
        this->s_forward =
          ( this->s_forward * std::cos( o ) ) -
          ( this->s_right * std::sin( o ) );
        this->s_forward.normalize( );

        this->s_right = this->s_forward * this->s_up;
        break;

    case 'l':

        this->s_forward =
          ( this->s_forward * std::cos( o ) ) -
          ( this->s_right * std::sin( o ) );
        this->s_forward.normalize( );

        this->s_right = this->s_forward * this->s_up;
        break;


    default:
        break;
    }
}


void Snake::
setSpeed(float s){
this->speed = s;
}

float Snake::
getSpeed(){
  return this->speed;
}

#endif // __SNAKE__HXX__
