// -------------------------------------------------------------------------
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// -------------------------------------------------------------------------
#ifndef __Camera__h__
#define __Camera__h__

#include "vector.h"

/**
 */
class Camera
{
public:
  //! Memory management
  //@{
  Camera( );
  virtual ~Camera( );
  //@}

  void move( const Vector& dir );
  void lookAt( const Vector& pnt );
  void rotV( float a );
  void rotH( float a );

  void forward( float d );
  void upward( float d );
  void strafe( float d );

  void getReference( int& dx, int& dy, int x, int y );
  void setReference( int x, int y );
  void setPosition( const Vector& position);

  void loadCameraMatrix( );

  void setFOV( float a );
  void setPlanes( float n, float f );
  void setWindow( int w, int h );
  void loadProjectionMatrix( );

protected:
  float m_FOV;
  float m_Near;
  float m_Far;
  int m_WindowWidth;
  int m_WindowHeight;

  Vector m_Focus;
  Vector m_RightVector;
  Vector m_UpVector;
  Vector m_Position;

  int m_RefX;
  int m_RefY;
};

#include "camera.hxx"

#endif // __Camera__h__

// eof - Camera.h
