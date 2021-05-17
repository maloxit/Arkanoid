#include "Ball.hpp"

#include "Wall.hpp"
#include "Block.hpp"
#include "Platform.hpp"
#include "GameController.hpp"
#include "Score.hpp"

void Ball::SpeedUp()
{
  speed *= 1.1f;
}

void Ball::SpeedDown()
{
  speed /= 1.1f;
}

Ball::Ball(const Transform& transform, const shared_ptr<RenderManager>& renderManager, GameController& gameController, const Vector2f& direction, float speed, float enabled) : Updatable(enabled), transform(transform), gameController(gameController)
{
  this->speed = speed;
  this->direction = direction;
  this->direction.Normalise();
  visuals = make_shared<RenderPrimitivesSet>(true, this->transform, RenderLayer::MIDDLE, 1);
  renderManager->AddRenderObject(static_pointer_cast<RenderObject, RenderPrimitivesSet>(visuals));
  visuals->AddPrimitive(RenderPrimitivesSet::PrimitiveType::FILL_RECT, Vector4uc(255, 0, 0, 255), Vector2f(0,0), Vector2f(1, 1));
}

void Ball::Destroy()
{
  visuals->enabled = false;
  transform.enableHit = false;
  enabled = false;
  gameController.AddScore(-10);
  Destroyable::Destroy();
}

void Ball::Update(float deltaTime)
{
  if (transform.position.y > 800.f)
  {
    Destroy();
  }
  else
  {
    float step = speed * deltaTime;
    while (step > 0.f)
    {
      weak_ptr<Wall> closestHitWall;
      weak_ptr<Ball> closestHitBall;
      weak_ptr<Platform> closestHitPlatform;
      weak_ptr<Block> closestHitBlock;
      enum class HitObjectType
      {
        NONE,
        WALL,
        BALL,
        PLATFORM,
        BLOCK
      } hitType = HitObjectType::NONE;
      Hit closestHit;
      Hit hit;
      if (gameController.TryHitWalls(transform, direction, step, closestHitWall, hit, nullptr) && (hitType == HitObjectType::NONE || hit.distance < closestHit.distance))
      {
        hitType = HitObjectType::WALL;
        closestHit = hit;
      }
      if (gameController.TryHitBalls(transform, direction, step, closestHitBall, hit, this) && (hitType == HitObjectType::NONE || hit.distance < closestHit.distance))
      {
        hitType = HitObjectType::BALL;
        closestHit = hit;
      }
      if (gameController.TryHitPlatforms(transform, direction, step, closestHitPlatform, hit, nullptr) && (hitType == HitObjectType::NONE || hit.distance < closestHit.distance))
      {
        hitType = HitObjectType::PLATFORM;
        closestHit = hit;
      }
      if (gameController.TryHitBlocks(transform, direction, step, closestHitBlock, hit, nullptr) && (hitType == HitObjectType::NONE || hit.distance < closestHit.distance))
      {
        hitType = HitObjectType::BLOCK;
        closestHit = hit;
      }

      float normalScalarProj;
      if (hitType != HitObjectType::NONE)
      {
        normalScalarProj = Vector2f::ScalarPojection(direction, closestHit.normalVec);
        transform.position += direction * closestHit.distance;
        step -= closestHit.distance;
      }
      switch (hitType)
      {
      case HitObjectType::WALL:
      {
        direction = direction - normalScalarProj * 2 * closestHit.normalVec;
        direction.Normalise();
      }
      break;
      case HitObjectType::BALL:
      {
        direction = direction - normalScalarProj * 2 * closestHit.normalVec;
        direction.Normalise();
        break;
      }
      case HitObjectType::PLATFORM:
      {
        direction = direction - normalScalarProj * 2 * closestHit.normalVec;
        auto platform = closestHitPlatform.lock();
        direction.x += ((transform.position.x + transform.size.x / 2) - (platform->transform.position.x + platform->transform.size.x / 2)) * 3 / platform->transform.size.x;
        direction.Normalise();
        break;
      }
      case HitObjectType::BLOCK:
      {
        direction = direction - normalScalarProj * 2 * closestHit.normalVec;
        direction.Normalise();
        closestHitBlock.lock()->GetHit(*this);
        break;
      }
      default:
      {
        transform.position += direction * step;
        step = 0.f;
        break;
      }
      }
    }
  }
}
