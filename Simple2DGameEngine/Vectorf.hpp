#pragma once

#include <cmath>

namespace GameEngine
{

  struct Vector4f
  {
  public:
    float x, y, z, k;
    Vector4f() : x(0.f), y(0.f), z(0.f), k(0.f) {};
    Vector4f(float x, float y, float z, float k) : x(x), y(y), z(z), k(k) {};
  };

  struct Vector2f
  {
  public:
    float x, y;
    Vector2f() : x(0.f), y(0.f) {};
    Vector2f(float x, float y) : x(x), y(y) {};

    Vector2f& operator+=(const Vector2f& right)
    {
      this->x += right.x;
      this->y += right.y;
      return *this;
    }
    Vector2f& operator-=(const Vector2f& right)
    {
      this->x -= right.x;
      this->y -= right.y;
      return *this;
    }
    Vector2f& operator*=(const float& right)
    {
      this->x *= right;
      this->y *= right;
      return *this;
    }
    Vector2f& operator/=(const float& right)
    {
      this->x /= right;
      this->y /= right;
      return *this;
    }

    static float ScalarPojection(const Vector2f& left, const Vector2f& right)
    {
      return left.x * right.x + left.y * right.y;
    }

    float Norma()
    {
      return sqrtf(x * x + y * y);
    }
    void Normalise()
    {
      float norma = Norma();
      *this /= norma;
    }
    
  };

  const Vector2f operator+(const Vector2f& left, const Vector2f& right);
  const Vector2f operator-(const Vector2f& left, const Vector2f& right);
  const Vector2f operator*(const Vector2f& left, const Vector2f& right);
  const Vector2f operator*(const Vector2f& left, const float& right);
  const Vector2f operator*(const float& left, const Vector2f& right);
  const Vector2f operator/(const Vector2f& left, const float& right);

  struct Vector4uc
  {
  public:
    unsigned char x, y, z, k;
    Vector4uc() : x(0), y(0), z(0), k(0) {};
    Vector4uc(unsigned char x, unsigned char y, unsigned char z, unsigned char k) : x(x), y(y), z(z), k(k) {};
  };

}