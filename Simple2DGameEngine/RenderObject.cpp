#include "RenderObject.hpp"

namespace GameEngine
{
  RenderObject::RenderObject(bool enabled, const Transform& transform, RenderLayer layer) : enabled(enabled), transform(transform), layer(layer) { };
}