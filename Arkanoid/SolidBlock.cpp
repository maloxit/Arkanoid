#include "SolidBlock.hpp"

#include "GameController.hpp"

SolidBlock::SolidBlock(const Transform& transform, const shared_ptr<RenderManager>& renderManager, GameController& gameController) : SimpleBlock(transform, renderManager, gameController, 0)
{
  visuals->ChangePrimitiveColor(0, Vector4uc(50, 50, 50, 255));
}

void SolidBlock::GetHit(Ball& ball)
{
}
