#include "Bonus.hpp"

#include "GameController.hpp"

Bonus::Bonus(const Transform& transform, const shared_ptr<RenderManager>& renderManager, GameController& gameController, const Vector2f& direction, float speed, float enabled) : Updatable(enabled), transform(transform.position, transform.size, enabled), gameController(gameController)
{
  this->direction = direction;
  this->direction.Normalise();
  this->speed = speed;
  this->enabled = enabled;
  visuals = make_shared<RenderPrimitivesSet>(enabled, this->transform, RenderLayer::TOP, 1);
  renderManager->AddRenderObject(static_pointer_cast<RenderObject, RenderPrimitivesSet>(visuals));
}

void Bonus::Drop(const Vector2f& dropPoint)
{
  transform.position = dropPoint;
  transform.enableHit = true;
  visuals->enabled = true;
  enabled = true;
}

void Bonus::Destroy()
{
  transform.enableHit = false;
  visuals->enabled = false;
  enabled = false;
  Destroyable::Destroy();
}

void Bonus::Update(float deltaTime)
{
  if (transform.position.y > 800.f)
  {
    Destroy();
  }
  else
  {
    float step = speed * deltaTime;
    weak_ptr<Platform> closestHitPlatform;
    Hit hit;
    if (gameController.TryHitPlatforms(transform, direction, step, closestHitPlatform, hit, nullptr))
    {
      Activate();
      Destroy();
    }
    else
    {
      transform.position += direction * step;
    }
  }
}
