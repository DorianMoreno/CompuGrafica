#ifndef __GAME__H__
#define __GAME__H__

#include <chrono>
#include <GL/glu.h>
#include <map>
#include <random>
#include <vector>
#include "vector.h"
#include "camera.h"
#include "snake.h"
#include "grid.h"
#include "block.h"

#define SNAKE 0
#define OBSTACLE 1

class Game
{
public:
  //! Memory management
  //@{
  Game(  const int& gridSize = 7, const float& initialSpeed = 2.5f, const float& speedIncrease = 0.8f, const float& FOV = 90);
  virtual ~Game( );
  //@}

  void resetGame(  );
  void staticCameraRotation( const float& dx, const float& dy, const float& sensibH = 1.0, const float& sensibV = 1.0 );
  void resizeCamera(const int& w, const int& h);

  void keyPress(const char& key);
  void specialKeyPress(const int& key);

  void draw(  );
  void draw6Directions(  );
  void draw18Directions(  );
  void draw26Directions(  );
  void draw30Directions(  );
  void draw54Directions(  );

  void generateFood(  );
  int collision(const Vector& position);
protected:
    Snake* m_Snake;
    Camera* m_Camera;
    Grid* m_Grid;
    Grid* m_ExternalGrid;

    int m_Score;
    bool m_GameStarted;

    GLuint m_List;

    FoodBlock* m_Food;
    std::vector<FoodBlock*> m_Obstacles;
    std::map<Vector, int> m_Blocks;

    float m_InitialSpeed;
    float m_GridSize;
    float m_FOV;
};

#include "game.hxx"

#endif // __GAME__H__

// eof - game.h
