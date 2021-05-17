#pragma once
#include "Simple2DGameEngine.hpp"

#include "Destroyable.hpp"

using namespace GameEngine;
using namespace std;

class Wall;
class Platform;
class GameController;

class Ball : public Updatable, public Destroyable
{
private:
  GameController& gameController;
  shared_ptr<RenderPrimitivesSet> visuals;
  Vector2f direction;
  float speed;
public:
  void SpeedUp();
  void SpeedDown();
  Transform transform;
  Ball(const Transform& transform, const shared_ptr<RenderManager>& renderManager, GameController& gameController, const Vector2f& direction, float speed, float enabled);
  virtual void Destroy();
  virtual void Update(float deltaTime);
};

