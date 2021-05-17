#pragma once
#include "SDL.h"
#include <vector>

#include "Vectorf.hpp"
#include "RenderObject.hpp"

namespace GameEngine
{
  class RenderPrimitivesSet : public RenderObject
  {
  public:
    enum class PrimitiveType : char
    {
      LINE,
      RECT,
      FILL_RECT
    };
    RenderPrimitivesSet() = delete;
    RenderPrimitivesSet(bool enabled, const Transform& transform, RenderLayer layer, int premetiveCopasity);
    void AddPrimitive(PrimitiveType type, const Vector4uc& color, const Vector2f& point1, const Vector2f& point2);
    void ChangePrimitiveColor(int index, const Vector4uc& color);
    virtual void Draw(SDL_Renderer* renderer);

  private:
    struct Primitive
    {
    public:
      PrimitiveType type;
      Vector4uc color;
      Vector2f point1;
      Vector2f point2;
    };
    std::vector<Primitive> primitives;
  };
}