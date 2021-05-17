#include "Block.hpp"

#include "GameController.hpp"

Block::Block(const Transform& transform, GameController& gameController) : transform(transform), gameController(gameController) { }

void Block::Destroy()
{
  Destroyable::Destroy();
  transform.enableHit = false;
}
