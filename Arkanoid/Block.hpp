#pragma once
#include "Simple2DGameEngine.hpp"

#include "Destroyable.hpp"

using namespace GameEngine;
using namespace std;

class GameController;
class Ball;

class Block : public Destroyable
{
protected:
  GameController& gameController;
public:
  Transform transform;
  Block(const Transform& transform, GameController& gameController);
  virtual void GetHit(Ball& ball) = 0;
  virtual void Destroy();
  virtual ~Block() {};
};

