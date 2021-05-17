#include "SimpleBlock.hpp"

#include "GameController.hpp"

SimpleBlock::SimpleBlock(const Transform& transform, const shared_ptr<RenderManager>& renderManager, GameController& gameController, int pointsForHit) : Block(transform, gameController)
{
  this->pointsForHit = pointsForHit;
  visuals = make_shared<RenderPrimitivesSet>(true, this->transform, RenderLayer::MIDDLE, 1);
  renderManager->AddRenderObject(static_pointer_cast<RenderObject, RenderPrimitivesSet>(visuals));
  visuals->AddPrimitive(RenderPrimitivesSet::PrimitiveType::FILL_RECT, Vector4uc(0, 255, 0, 255), Vector2f(0, 0), Vector2f(1, 1));
  visuals->AddPrimitive(RenderPrimitivesSet::PrimitiveType::RECT, Vector4uc(255, 255, 255, 255), Vector2f(0, 0), Vector2f(1, 1));
}

void SimpleBlock::GetHit(Ball& ball)
{
  gameController.AddScore(pointsForHit);
  Destroy();
}

void SimpleBlock::Destroy()
{
  Block::Destroy();
  visuals->enabled = false;
}