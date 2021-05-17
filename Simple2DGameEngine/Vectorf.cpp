#include "Vectorf.hpp"
namespace GameEngine
{
  const Vector2f operator+(const Vector2f& left, const Vector2f& right)
  {
    return Vector2f(left.x + right.x, left.y + right.y);
  }
  const Vector2f operator-(const Vector2f& left, const Vector2f& right)
  {
    return Vector2f(left.x - right.x, left.y - right.y);
  }
  const Vector2f operator*(const Vector2f& left, const Vector2f& right)
  {
    return Vector2f(left.x * right.x, left.y * right.y);
  }
  const Vector2f operator*(const Vector2f& left, const float& right)
  {
    return Vector2f(left.x * right, left.y * right);
  }
  const Vector2f operator*(const float& left, const Vector2f& right)
  {
    return Vector2f(right.x * left, right.y * left);
  }
  const Vector2f operator/(const Vector2f& left, const float& right)
  {
    return Vector2f(left.x / right, left.y / right);
  }
}