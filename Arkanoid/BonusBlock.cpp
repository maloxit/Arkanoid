#include "BonusBlock.hpp"

#include "Bonus.hpp"

BonusBlock::BonusBlock(const Transform& transform, const shared_ptr<RenderManager>& renderManager, GameController& gameController, int pointsForHit, const shared_ptr<Bonus>& bonus) : SimpleBlock(transform, renderManager, gameController, pointsForHit), bonus(bonus)
{
  visuals->ChangePrimitiveColor(0, Vector4uc(255, 50, 150, 255));
}

void BonusBlock::Destroy()
{
  bonus->Drop(transform.position);
  SimpleBlock::Destroy();
}
