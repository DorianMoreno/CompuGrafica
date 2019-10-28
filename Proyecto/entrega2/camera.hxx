// -------------------------------------------------------------------------
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// -------------------------------------------------------------------------

#include "camera.h"
#include "vector.h"
#include <cmath>
#include <GL/glu.h>

// -------------------------------------------------------------------------
Camera::
Camera( )
{
  this->setFOV( 45 );
  this->setWindow( 1, 1 );
  this->setPlanes( 1e-2, 10000 );

  this->m_Position = Vector( );
  this->m_Focus = Vector( 0, 0, -1 );
  this->m_RightVector = Vector ( 1 );
  this->m_UpVector = Vector( 0, 1 );
  this->m_RefX = this->m_RefY = 0;
}

// -------------------------------------------------------------------------
Camera::
~Camera( )
{
}

// -------------------------------------------------------------------------
void Camera::
move( const Vector& dir )
{
  this->m_Position += dir;
}

// -------------------------------------------------------------------------
void Camera::
lookAt( const Vector& pnt )
{
  this->m_Focus = pnt - this->m_Position;
  this->m_Focus.normalize( );
}

// -------------------------------------------------------------------------
void Camera::
rotV( float a )
{
    float o = a * _PI_180;
    this->m_Focus =
        ( this->m_Focus * std::cos( o ) ) +
        ( this->m_UpVector * std::sin( o ) );
    this->m_Focus.normalize( );

    this->m_UpVector = this->m_RightVector * this->m_Focus;
}

// -------------------------------------------------------------------------
void Camera::
rotH( float a )
{
  float o = a * _PI_180;

  this->m_Focus =
    ( this->m_Focus * std::cos( o ) ) -
    ( this->m_RightVector * std::sin( o ) );
  this->m_Focus.normalize( );

  this->m_RightVector = this->m_Focus * this->m_UpVector;
}

// -------------------------------------------------------------------------
void Camera::
forward( float d )
{
  this->m_Position += this->m_Focus * d;
}

// -------------------------------------------------------------------------
void Camera::
upward( float d )
{
  this->m_Position += this->m_UpVector * d;
}

// -------------------------------------------------------------------------
void Camera::
strafe( float d )
{
  this->m_Position += this->m_RightVector * d;
}

// -------------------------------------------------------------------------
void Camera::
getReference( int& dx, int& dy, int x, int y )
{
  dx = x - this->m_RefX;
  dy = y - this->m_RefY;
}

// -------------------------------------------------------------------------
void Camera::
setReference( int x, int y )
{
  this->m_RefX = x;
  this->m_RefY = y;
}

// -------------------------------------------------------------------------
void Camera::
setPosition( const Vector& position )
{
    this->m_Position = position;
}

// -------------------------------------------------------------------------
void Camera::
loadCameraMatrix( )
{
  Vector f = this->m_Position + this->m_Focus;

  gluLookAt(
    this->m_Position[ 0 ], this->m_Position[ 1 ], this->m_Position[ 2 ],
    f[ 0 ], f[ 1 ], f[ 2 ],
    this->m_UpVector[ 0 ], this->m_UpVector[ 1 ], this->m_UpVector[ 2 ]
    );
}

// -------------------------------------------------------------------------
void Camera::
setFOV( float a )
{
  this->m_FOV = std::fmod( a, 360 );
}

// -------------------------------------------------------------------------
void Camera::
setPlanes( float n, float f )
{
  this->m_Near = n;
  this->m_Far = f;
}

// -------------------------------------------------------------------------
void Camera::
setWindow( int w, int h )
{
  this->m_WindowWidth = ( w > 0 )? w: 1;
  this->m_WindowHeight = ( h > 0 )? h: 1;
}

// -------------------------------------------------------------------------
void Camera::
loadProjectionMatrix( )
{
  glViewport( 0, 0, this->m_WindowWidth, this->m_WindowHeight );
  gluPerspective(
    this->m_FOV,
    float( this->m_WindowWidth ) / float( this->m_WindowHeight ),
    this->m_Near,
    this->m_Far
    );
}

// eof - Camera.cxx
