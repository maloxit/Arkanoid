#include "Transform.hpp"
namespace GameEngine
{
  Transform::Transform(const Vector2f& position, const Vector2f& size, bool enableHit) : position(position), size(size), enableHit(enableHit)
  {
  }
  bool Transform::MoveLin(const Vector2f& target, float step)
  {
    Vector2f diff = target - position;
    if (diff.Norma() <= step)
    {
      position = target;
      return true;
    }
    else
    {
      diff.Normalise();
      diff *= step;
      position += diff;
      return false;
    }
  }

  bool Transform::IsIntersect(const Transform& intersectTransform)
  {
    Vector2f minDist = (size + intersectTransform.size) / 2;
    Vector2f center = position + size / 2;
    Vector2f hitTransformCenter = intersectTransform.position + intersectTransform.size / 2;
    Vector2f delta = center - hitTransformCenter;
    return (minDist.x - fabs(delta.x) > 0.0001f && minDist.y - fabs(delta.y) > 0.0001f);
  }

  bool Transform::TryHit(const Vector2f& direction, float step, const Transform& hitTransform, Hit& hit)
  {
    if (!hitTransform.enableHit)
    {
      return false;
    }
    bool isHit = false;
    Vector2f normalizedDiff = direction;
    normalizedDiff.Normalise();
    if (IsIntersect(hitTransform))
    {
      Vector2f center = position + size / 2;
      Vector2f hitTransformCenter = hitTransform.position + hitTransform.size / 2;
      Vector2f minDist = (size + hitTransform.size) / 2;
      Vector2f delta = center - hitTransformCenter;
      Vector2f move = -1 * delta;
      if (delta.x < 0)
      {
        move.x -= minDist.x;
      }
      else
      {
        move.x += minDist.x;
      }
      if (delta.y < 0)
      {
        move.y -= minDist.y;
      }
      else
      {
        move.y += minDist.y;
      }

      if (fabs(move.x) < fabs(move.y))
      {
        if (move.x < 0)
        {
          hit.normalVec = Vector2f(-1, 0);
          hit.distance = move.x;
        }
        else
        {
          hit.normalVec = Vector2f(1, 0);
          hit.distance = -move.x;
        }
      }
      else
      {
        if (move.y < 0)
        {
          hit.normalVec = Vector2f(0, -1);
          hit.distance = move.y;
        }
        else
        {
          hit.normalVec = Vector2f(0, 1);
          hit.distance = -move.y;
        }
      }
      return true;
    }
    if (normalizedDiff.x > 0 && position.x + size.x < hitTransform.position.x)
    {
      float dist = (hitTransform.position.x - position.x - size.x) / normalizedDiff.x;
      float newY = dist * normalizedDiff.y + position.y;

      if (dist < step && !(newY + size.y < hitTransform.position.y || newY > hitTransform.position.y + hitTransform.size.y))
      {
        if (!isHit || hit.distance > dist)
        {
          isHit = true;
          hit.distance = dist;
          hit.normalVec = Vector2f(-1, 0);
        }
      }
    }
    if (normalizedDiff.x < 0 && position.x > hitTransform.position.x + hitTransform.size.x)
    {
      float dist = (position.x - hitTransform.position.x - hitTransform.size.x) / -normalizedDiff.x;
      float newY = dist * normalizedDiff.y + position.y;

      if (dist < step && !(newY + size.y < hitTransform.position.y || newY > hitTransform.position.y + hitTransform.size.y))
      {
        if (!isHit || hit.distance > dist)
        {
          isHit = true;
          hit.distance = dist;
          hit.normalVec = Vector2f(1, 0);
        }
      }
    }
    if (normalizedDiff.y > 0 && position.y + size.y < hitTransform.position.y)
    {
      float dist = (hitTransform.position.y - position.y - size.y) / normalizedDiff.y;
      float newX = dist * normalizedDiff.x + position.x;

      if (dist < step && !(newX + size.x < hitTransform.position.x || newX > hitTransform.position.x + hitTransform.size.x))
      {
        if (!isHit || hit.distance > dist)
        {
          isHit = true;
          hit.distance = dist;
          hit.normalVec = Vector2f(0, -1);
        }
      }
    }
    if (normalizedDiff.y < 0 && position.y > hitTransform.position.y + hitTransform.size.y)
    {
      float dist = (position.y - hitTransform.position.y - hitTransform.size.y) / -normalizedDiff.y;
      float newX = dist * normalizedDiff.x + position.x;

      if (dist < step && !(newX + size.x < hitTransform.position.x || newX > hitTransform.position.x + hitTransform.size.x))
      {
        if (!isHit || hit.distance > dist)
        {
          isHit = true;
          hit.distance = dist;
          hit.normalVec = Vector2f(0, 1);
        }
      }
    }
    return isHit;
  }
}