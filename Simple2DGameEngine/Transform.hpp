#pragma once

#include "Vectorf.hpp"

namespace GameEngine
{
  struct Hit
  {
    Vector2f normalVec;
    float distance;
  };
  class Transform
  {
  public:
    bool enableHit;
    Vector2f position;
    Vector2f size;
    Transform(const Vector2f& position, const Vector2f& size, bool enableHit = false);
    bool MoveLin(const Vector2f& target, float step);
    bool TryHit(const Vector2f& direction, float step, const Transform& hitTransform, Hit& hit);
  };

}