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
    s_Position  = Vector( 0.5, 0.5, 0.5 );
    s_Forward   = Vector( 0 , 0 , -1 );
    s_Up        = Vector( 0 , 1 );
    s_Right     = s_Forward*s_Up;
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
    s_Position += (s_Forward * speed * dt);

    //if(pos > wS)-> wrap + add diff
    for (int i = 0; i<3;++i){
        // float temp = s_Position[i];
        // temp-= worldSize/2.0;
        s_Position[i] = fmod(worldSize + s_Position[i], worldSize);
        // s_Position[i] += temp;

      // if (abs(s_Position[ i ]) > worldSize)
      // {
      //     std::cout<<"from: "<<s_Position[i];
      //     dx = abs(s_Position[ i ]) - (float)worldSize;
      //     s_Position[ i ] *= -s_Position[ i ]/s_Position[ i ];
      //
      //     std::cout<<" to:: "<<s_Position[i]<<" dx: "<<dx<<std::endl;
      //
      // }
    }

    // glPushMatrix();
    // glColor3f(1,0,0);
    // glTranslatef(s_Position[0],s_Position[1],s_Position[2]);
    // gluSphere(tempquad,2,10,10);
    // glPopMatrix();

 }

Vector Snake::getPosition(){
    return s_Position;
}

Vector Snake::
rotate(char dir, float deg){
    float o = deg * _PI_180;

    this->s_Position[0] = (int)this->s_Position[0];
    this->s_Position[0] += 0.5;
    this->s_Position[1] = (int)this->s_Position[1];
    this->s_Position[1] += 0.5;
    this->s_Position[2] = (int)this->s_Position[2];
    this->s_Position[2] += 0.5;

    switch (dir)
    {
    case 'u':
        this->s_Forward =
          ( this->s_Forward * std::cos( o ) ) +
          ( this->s_Up * std::sin( o ) );
        this->s_Forward.normalize( );

        this->s_Up = ( this->s_Forward * this->s_Right ) * -1.0;
        return  this->s_Forward*this->s_Up;
    case 'd':
        o*=-1;
        this->s_Forward =
          ( this->s_Forward * std::cos( o ) ) +
          ( this->s_Up * std::sin( o ) );
        this->s_Forward.normalize( );

        this->s_Up = ( this->s_Forward * this->s_Right ) * -1.0;
        return this->s_Up*this->s_Forward;
        break;

    case 'r':
        o*=-1;
        this->s_Forward =
          ( this->s_Forward * std::cos( o ) ) -
          ( this->s_Right * std::sin( o ) );
        this->s_Forward.normalize( );

        this->s_Right = this->s_Forward * this->s_Up;
        return this->s_Forward*this->s_Right;

    case 'l':

        this->s_Forward =
          ( this->s_Forward * std::cos( o ) ) -
          ( this->s_Right * std::sin( o ) );
        this->s_Forward.normalize( );

        this->s_Right = this->s_Forward * this->s_Up;
        return this->s_Right*this->s_Forward;


    default:
        return Vector(0, 0, 0);
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

void Snake::
setForward(const Vector& forward){
    this->s_Forward = forward;
}

Vector Snake::
getForward(){
    return this->s_Forward;
}

#endif // __SNAKE__HXX__
