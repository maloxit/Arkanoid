#pragma once
#include "Simple2DGameEngine.hpp"

#include "Bonus.hpp"

using namespace GameEngine;
using namespace std;


class AddBallBonus : public Bonus
{
public:
  AddBallBonus(const Transform& transform, const shared_ptr<RenderManager>& renderManager, GameController& gameController, const Vector2f& direction, float speed, float enabled);
  virtual void Activate();
};

