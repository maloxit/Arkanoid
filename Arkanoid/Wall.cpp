#include "Wall.hpp"

Wall::Wall(const Transform& transform, const shared_ptr<RenderManager>& renderManager) : transform(transform)
{
  visuals = make_shared<RenderPrimitivesSet>(true, this->transform, RenderLayer::MIDDLE, 1);
  renderManager->AddRenderObject(static_pointer_cast<RenderObject, RenderPrimitivesSet>(visuals));
  visuals->AddPrimitive(RenderPrimitivesSet::PrimitiveType::FILL_RECT, Vector4uc(150, 50, 150, 255), Vector2f(0,0), Vector2f(1,1));
}
