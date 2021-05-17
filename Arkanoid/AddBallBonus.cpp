#include "AddBallBonus.hpp"

#include "GameController.hpp"

AddBallBonus::AddBallBonus(const Transform& transform, const shared_ptr<RenderManager>& renderManager, GameController& gameController, const Vector2f& direction, float speed, float enabled) : 
  Bonus(transform, renderManager, gameController, direction, speed, enabled)
{
  visuals->AddPrimitive(RenderPrimitivesSet::PrimitiveType::FILL_RECT, Vector4uc(255, 255, 255, 255), Vector2f(0.1f, 0.1f), Vector2f(0.8f, 0.8f));
}

void AddBallBonus::Activate()
{
  gameController.AddBall();
}
