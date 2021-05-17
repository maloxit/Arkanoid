#pragma once
#include "Simple2DGameEngine.hpp"


#include "SimpleBlock.hpp"

using namespace GameEngine;
using namespace std;

class SolidBlock : public SimpleBlock
{
public:
  SolidBlock(const Transform& transform, const shared_ptr<RenderManager>& renderManager, GameController& gameController);
  virtual void GetHit(Ball& ball);
};

