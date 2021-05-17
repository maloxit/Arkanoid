#pragma once
#include "Simple2DGameEngine.hpp"

#include "Destroyable.hpp"

using namespace GameEngine;
using namespace std;

class GameController;

class Bonus: public Updatable, public Destroyable
{
protected:
  GameController& gameController;
  shared_ptr<RenderPrimitivesSet> visuals;
  Vector2f direction;
  float speed;
public:
  Transform transform;
  Bonus(const Transform& transform, const shared_ptr<RenderManager>& renderManager, GameController& gameController, const Vector2f& direction, float speed, float enabled);
  void Drop(const Vector2f& dropPoint);
  virtual void Destroy();
  virtual void Activate() = 0;
  virtual void Update(float deltaTime);
};