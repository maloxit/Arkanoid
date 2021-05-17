#pragma once
#include "Simple2DGameEngine.hpp"


#include "SimpleBlock.hpp"

using namespace GameEngine;
using namespace std;

class HealthBlock : public SimpleBlock
{
protected:
  int healthPoints;
public:
  HealthBlock(const Transform& transform, const shared_ptr<RenderManager>& renderManager, GameController& gameController, int pointsForHit, int healthPoints);
  virtual void GetHit(Ball& ball);
};

