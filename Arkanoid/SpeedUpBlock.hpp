#pragma once

#include "SimpleBlock.hpp"

using namespace GameEngine;
using namespace std;

class SpeedUpBlock : public SimpleBlock
{
public:
  SpeedUpBlock(const Transform& transform, const shared_ptr<RenderManager>& renderManager, GameController& gameController, int pointsForHit);
  virtual void GetHit(Ball& ball);
};

