#include "SpeedUpBlock.hpp"

#include "GameController.hpp"
#include "Ball.hpp"

SpeedUpBlock::SpeedUpBlock(const Transform& transform, const shared_ptr<RenderManager>& renderManager, GameController& gameController, int pointsForHit) : SimpleBlock(transform, renderManager, gameController, pointsForHit)
{
  visuals->ChangePrimitiveColor(0, Vector4uc(50, 255, 255, 255));
}

void SpeedUpBlock::GetHit(Ball& ball)
{
  ball.SpeedUp();
  SimpleBlock::GetHit(ball);
}
