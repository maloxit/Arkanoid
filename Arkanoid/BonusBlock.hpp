#pragma once
#include "SimpleBlock.hpp"


using namespace GameEngine;
using namespace std;

class Bonus;

class BonusBlock : public SimpleBlock
{
private:
  shared_ptr<Bonus> bonus;
public:
  BonusBlock(const Transform& transform, const shared_ptr<RenderManager>& renderManager, GameController& gameController, int pointsForHit, const shared_ptr<Bonus>& bonus);
  virtual void Destroy();
};
