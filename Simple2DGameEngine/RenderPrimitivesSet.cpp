#include "RenderPrimitivesSet.hpp"

#include "Transform.hpp"

namespace GameEngine
{
  RenderPrimitivesSet::RenderPrimitivesSet(bool enabled, const Transform& transform, RenderLayer layer, int premetiveCopasity) : RenderObject(enabled, transform, layer)
  {
    primitives.reserve(premetiveCopasity);
  }
  void RenderPrimitivesSet::AddPrimitive(PrimitiveType type, const Vector4uc& color, const Vector2f& point1, const Vector2f& point2)
  {
    Primitive primitive = { type, color, point1, point2};
    primitives.push_back(primitive);
  }
  void RenderPrimitivesSet::ChangePrimitiveColor(int index, const Vector4uc& color)
  {
    primitives[index].color = color;
  }
  void RenderPrimitivesSet::Draw(SDL_Renderer* renderer)
  {
    for (auto& primitive : primitives)
    {
      SDL_SetRenderDrawColor(renderer, primitive.color.x, primitive.color.y, primitive.color.z, primitive.color.k);
      if (primitive.type == PrimitiveType::LINE)
      {
        Vector2f newPoint1 = transform.position + primitive.point1 * transform.size;
        Vector2f newPoint2 = transform.position + primitive.point2 * transform.size;
        SDL_RenderDrawLineF(renderer, newPoint1.x, newPoint1.y, newPoint2.x, newPoint2.y);
      }
      else
      {
        Vector2f newPoint1 = transform.position + primitive.point1 * transform.size;
        Vector2f newPoint2 = primitive.point2 * transform.size;
        SDL_FRect rect = SDL_FRect{ newPoint1.x, newPoint1.y, newPoint2.x, newPoint2.y };
        switch (primitive.type)
        {
        case PrimitiveType::RECT:
          SDL_RenderDrawRectF(renderer, &rect);
          break;
        case PrimitiveType::FILL_RECT:
          SDL_RenderFillRectF(renderer, &rect);
          break;
        default:
          break;
        }
      }
    }
  }
}