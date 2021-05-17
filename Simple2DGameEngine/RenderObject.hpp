#pragma once
#include "SDL.h"

namespace GameEngine
{
  class Transform;
  enum class RenderLayer;

  class RenderObject
  {
  protected:
    const Transform& transform;
  public:
    const RenderLayer layer;
    bool enabled;
    RenderObject() = delete;
    RenderObject(bool enabled, const Transform& transform, RenderLayer layer);
    virtual void Draw(SDL_Renderer* renderer) = 0;
  };

}