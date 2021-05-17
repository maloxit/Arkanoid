#include "MoveingBlock.hpp"

#include "GameController.hpp"

MoveingBlock::MoveingBlock(const Transform& transform, const shared_ptr<RenderManager>& renderManager, GameController& gameController, int pointsForHit, int healthPoints, const Vector2f& direction, float speed, float enabled) : Updatable(enabled), HealthBlock(transform, renderManager, gameController, pointsForHit, healthPoints)
{
  this->speed = speed;
  this->direction = direction;
  this->direction.Normalise();
  visuals->ChangePrimitiveColor(0, Vector4uc(100, 150, 0, 255));
}

void MoveingBlock::Update(float deltaTime)
{
  float step = speed * deltaTime;
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
  if (gameController.TryHitBalls(transform, direction, step, closestHitBall, hit, nullptr) && (hitType == HitObjectType::NONE || hit.distance < closestHit.distance))
  {
    hitType = HitObjectType::BALL;
    closestHit = hit;
  }
  if (gameController.TryHitPlatforms(transform, direction, step, closestHitPlatform, hit, nullptr) && (hitType == HitObjectType::NONE || hit.distance < closestHit.distance))
  {
    hitType = HitObjectType::PLATFORM;
    closestHit = hit;
  }
  if (gameController.TryHitBlocks(transform, direction, step, closestHitBlock, hit, static_cast<Block*>(this)) && (hitType == HitObjectType::NONE || hit.distance < closestHit.distance))
  {
    hitType = HitObjectType::BLOCK;
    closestHit = hit;
  }

  if (hitType == HitObjectType::NONE)
  {
    transform.position += direction * step;
  }
  else
  {
    float normalScalarProj = Vector2f::ScalarPojection(direction, closestHit.normalVec);
    transform.position += direction * closestHit.distance;
    direction = direction - normalScalarProj * 2 * closestHit.normalVec;
    direction.Normalise();
  }
}
