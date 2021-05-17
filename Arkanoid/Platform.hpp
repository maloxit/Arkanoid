#pragma once
#include "Simple2DGameEngine.hpp"

using namespace GameEngine;
using namespace std;

class Platform : public Updatable, public EventListener
{
private:
  shared_ptr<RenderPrimitivesSet> visuals;
  float moveSpeed;
  Vector2f rightMaxPosition;
  Vector2f leftMaxPosition;
public:
  Transform transform;
  enum class MoveState
  {
    IDLE,
    LEFT,
    RIGHT
  } moveState;
  Platform(const Transform& transform, const shared_ptr<RenderManager>& renderManager, const Vector2f& leftMaxPosition, const Vector2f& rightMaxPosition, float moveSpeed);
  virtual void Update(float deltaTime);
  virtual void HandleEvent(const SDL_Event& event);
};

