#pragma once
#include "Simple2DGameEngine.hpp"


#include "Block.hpp"

using namespace GameEngine;
using namespace std;

class SimpleBlock : public Block
{
protected:
  int pointsForHit;
  shared_ptr<RenderPrimitivesSet> visuals;
public:
  SimpleBlock(const Transform& transform, const shared_ptr<RenderManager>& renderManager, GameController& gameController, int pointsForHit);
  virtual void GetHit(Ball& ball);
  virtual void Destroy();
};

