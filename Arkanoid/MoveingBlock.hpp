#pragma once
#include "Simple2DGameEngine.hpp"


#include "HealthBlock.hpp"

using namespace GameEngine;
using namespace std;

class MoveingBlock : public HealthBlock, public Updatable
{
private:
  Vector2f direction;
  float speed;
public:
  MoveingBlock(const Transform& transform, const shared_ptr<RenderManager>& renderManager, GameController& gameController, int pointsForHit, int healthPoints, const Vector2f& direction = Vector2f(1, 0), float speed = 100.f, float enabled = true);
  virtual void Update(float deltaTime);
};

