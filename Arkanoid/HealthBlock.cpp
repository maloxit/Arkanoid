#include "HealthBlock.hpp"

#include "GameController.hpp"

HealthBlock::HealthBlock(const Transform& transform, const shared_ptr<RenderManager>& renderManager, GameController& gameController, int pointsForHit, int healthPoints) : SimpleBlock(transform, renderManager, gameController, pointsForHit)
{
  this->healthPoints = healthPoints;
  visuals->ChangePrimitiveColor(0, Vector4uc(0, 150, 0, 255));
}

void HealthBlock::GetHit(Ball& ball)
{
  if (healthPoints > 0)
  {
    gameController.AddScore(pointsForHit);
    healthPoints--;
  }
  else
  {
    SimpleBlock::GetHit(ball);
  }
}
