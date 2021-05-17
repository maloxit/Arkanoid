#include "GameController.hpp"

#include <fstream>
#include "Wall.hpp"
#include "Ball.hpp"
#include "Platform.hpp"
#include "Block.hpp"
#include "Bonus.hpp"
#include "AddBallBonus.hpp"
#include "SimpleBlock.hpp"
#include "SpeedUpBlock.hpp"
#include "HealthBlock.hpp"
#include "MoveingBlock.hpp"
#include "SolidBlock.hpp"
#include "BonusBlock.hpp"
#include "Score.hpp"

void GameController::ClearListsFromDestroyed()
{
  auto block = blockList.begin();
  auto blockEnd = blockList.end();
  while (block != blockEnd)
  {
    if ((*block)->NeedDestruction())
    {
      block = blockList.erase(block);
      continue;
    }
    ++block;
  }
  auto ball = ballList.begin();
  auto ballEnd = ballList.end();
  while (ball != ballEnd)
  {
    if ((*ball)->NeedDestruction())
    {
      ball = ballList.erase(ball);
      continue;
    }
    ++ball;
  }
}

void GameController::LoadLevel(string& levelFile)
{
  ifstream level;
  string line;
  Vector2f blockSize = { 55, 25 };
  Vector2f blockIndent = { 15, 15 };
  solidBlocksCount = 0;
  level.open(levelFile);
  for (int y = 0; getline(level, line) && y < 30; y++)
  {
    for (int x = 0; x < 14 && x < line.size(); x++)
    {
      shared_ptr<Block> block;
      Vector2f blockPosition = blockIndent + blockSize * Vector2f(x, y);
      switch (line[x])
      {
      case 'S':
      {
        auto block = make_shared<SimpleBlock>(Transform(blockPosition, blockSize, true), scene.renderManager, *this, 10);
        blockList.push_back(static_pointer_cast<Block, SimpleBlock>(block));
      }
        break;
      case 'U':
      {
        auto block = make_shared<SpeedUpBlock>(Transform(blockPosition, blockSize, true), scene.renderManager, *this, 25);
        blockList.push_back(static_pointer_cast<Block, SpeedUpBlock>(block));
      }
        break;
      case 'M':
      {
        auto block = make_shared<MoveingBlock>(Transform(blockPosition + Vector2f(1,1), blockSize - Vector2f(2, 2), true), scene.renderManager, *this, 10, 3);
        scene.AddUpdatable(static_pointer_cast<Updatable, MoveingBlock>(block));
        blockList.push_back(static_pointer_cast<Block, MoveingBlock>(block));
      }
        break;
      case 'H':
      {
        auto block = make_shared<HealthBlock>(Transform(blockPosition, blockSize, true), scene.renderManager, *this, 10, 3);
        blockList.push_back(static_pointer_cast<Block, HealthBlock>(block));
      }
        break;
      case '#':
      {
        auto block = make_shared<SolidBlock>(Transform(blockPosition, blockSize, true), scene.renderManager, *this);
        blockList.push_back(static_pointer_cast<Block, SolidBlock>(block));
        solidBlocksCount++;
      }
        break;
      case 'B':
      {
        auto bonus = make_shared<AddBallBonus>(Transform(blockPosition, blockSize), scene.renderManager, *this, Vector2f(0, 1), 200.f, false);
        scene.AddUpdatable(static_pointer_cast<Updatable, AddBallBonus>(bonus));
        bonusList.push_back(static_pointer_cast<Bonus, AddBallBonus>(bonus));
        auto block = make_shared<BonusBlock>(Transform(blockPosition, blockSize, true), scene.renderManager, *this, 25, bonus);
        blockList.push_back(static_pointer_cast<Block, BonusBlock>(block));
      }
      break;
      case ' ':
      default:
        break;
      }
    }
  }
  level.close();
}

void GameController::ResetBallAndPlatform()
{
  auto ball = make_shared<Ball>(Transform({ (800 - 10) / 2, 650 }, { 10, 10 }, true), scene.renderManager, *this, Vector2f(1, -10), 400.f, false);
  scene.AddUpdatable(static_pointer_cast<Updatable, Ball>(ball));
  ballList.push_back(ball);

  auto platform = make_shared<Platform>(Transform({ 300, 800 - 60 }, { 200, 15 }, true), scene.renderManager, Vector2f(10, 800 - 60), Vector2f(800 - 210, 800 - 60), 800.f);
  scene.AddUpdatable(static_pointer_cast<Updatable, Platform>(platform));
  scene.eventManager->AddKeyboardEventListener(static_pointer_cast<EventListener, Platform>(platform));
  platformList.push_back(platform);
}

void GameController::AddScore(int points)
{
  score->Add(points);
}

void GameController::AddBall()
{
  auto ball = make_shared<Ball>(Transform({ (800 - 10) / 2, 650 }, { 10, 10 }, true), scene.renderManager, *this, Vector2f(1, -10), 300.f, true);
  scene.AddUpdatable(static_pointer_cast<Updatable, Ball>(ball));
  ballList.push_back(ball);
}

bool GameController::TryHitWalls(Transform& transform, const Vector2f& direction, float step, weak_ptr<Wall>& closestHitWall, Hit& closestHit, Wall* exceptSelf)
{
  bool isHit = false;
  Hit hit;
  for (auto& wall : wallList)
  {
    if (wall.get() != exceptSelf && transform.TryHit(direction, step, wall->transform, hit))
    {
      if (!isHit || hit.distance < closestHit.distance)
      {
        isHit = true;
        closestHitWall = wall;
        closestHit = hit;
      }
    }
  }
  return isHit;
}

bool GameController::TryHitBalls(Transform& transform, const Vector2f& direction, float step, weak_ptr<Ball>& closestHitBall, Hit& closestHit, Ball* exceptSelf)
{
  bool isHit = false;
  Hit hit;
  for (auto& ball : ballList)
  {
    if (ball.get() != exceptSelf && !ball->NeedDestruction() && transform.TryHit(direction, step, ball->transform, hit))
    {
      if (!isHit || hit.distance < closestHit.distance)
      {
        isHit = true;
        closestHitBall = ball;
        closestHit = hit;
      }
    }
  }
  return isHit;
}

bool GameController::TryHitPlatforms(Transform& transform, const Vector2f& direction, float step, weak_ptr<Platform>& closestHitPlatform, Hit& closestHit, Platform* exceptSelf)
{
  bool isHit = false;
  Hit hit;
  for (auto& platform : platformList)
  {
    if (platform.get() != exceptSelf && transform.TryHit(direction, step, platform->transform, hit))
    {
      if (!isHit || hit.distance < closestHit.distance)
      {
        isHit = true;
        closestHitPlatform = platform;
        closestHit = hit;
      }
    }
  }
  return isHit;
}

bool GameController::TryHitBlocks(Transform& transform, const Vector2f& direction, float step, weak_ptr<Block>& closestHitBlock, Hit& closestHit, Block* exceptSelf)
{
  bool isHit = false;
  Hit hit;
  for (auto& block : blockList)
  {
    if (block.get() != exceptSelf && !block->NeedDestruction() && transform.TryHit(direction, step, block->transform, hit))
    {
      if (!isHit || hit.distance < closestHit.distance)
      {
        isHit = true;
        closestHitBlock = block;
        closestHit = hit;
      }
    }
  }
  return isHit;
}

GameController::GameController(Scene& scene, TTF_Font* font, const string& levelFile) : Updatable(true), scene(scene), levelFile(levelFile)
{
  this->font = font;
  score = make_shared<Score>(Transform({ 15, 15 }, { 25, 25 }), scene.renderManager, 0, font, Vector4uc{ 255,255,255,255 });

  wallList.push_back(make_shared<Wall>(Transform({ 0, 0 }, { 800, 15 }, true) , scene.renderManager));
  wallList.push_back(make_shared<Wall>(Transform({ 0, 0 }, { 800, 10 }, true) , scene.renderManager));
  wallList.push_back(make_shared<Wall>(Transform({ 0, 0 }, { 15, 800 }, true) , scene.renderManager));
  wallList.push_back(make_shared<Wall>(Transform({ 0, 0 }, { 10, 800 }, true) , scene.renderManager));
  wallList.push_back(make_shared<Wall>(Transform({ 800 - 15, 0 }, { 15, 800 }, true) , scene.renderManager));
  wallList.push_back(make_shared<Wall>(Transform({ 800 - 10, 0 }, { 10, 800 }, true) , scene.renderManager));

  LoadLevel(this->levelFile);
  ResetBallAndPlatform();
  pauseTimer = 1.f;
  state = GameState::PAUSE_BEFORE_START;
}


void GameController::PauseBeforeStart()
{
  if (pauseTimer <= 0)
  {
    for (auto& ball : ballList)
    {
      ball->enabled = true;
      secondTimer = 1.f;
      state = GameState::PLAYING;
    }
  }
}
void GameController::Playing()
{
  if (secondTimer <= 0)
  {
    score->Add(-1);
    secondTimer += 1.f;
  }
  ClearListsFromDestroyed();
  if (ballList.empty())
  {
    platformList.clear();
    pauseTimer = 1.f;
    score->Add(-50);
    state = GameState::PAUSE_BEFORE_RETRY;
  }
  else if (blockList.size() <= solidBlocksCount)
  {
    ballList.clear();
    blockList.clear();
    bonusList.clear();
    platformList.clear();
    state = GameState::GAME_FINISHED;
  }

}
void GameController::PauseBeforeRetry()
{
  if (pauseTimer <= 0)
  {
    ResetBallAndPlatform();
    pauseTimer = 1.f;
    state = GameState::PAUSE_BEFORE_START;
  }
}

void GameController::GameFinished()
{

}



void GameController::Update(float deltaTime)
{
  secondTimer -= deltaTime;
  pauseTimer -= deltaTime;
  switch (state)
  {
  case GameState::PAUSE_BEFORE_START:
    PauseBeforeStart();
    break;
  case GameState::PLAYING:
    Playing();
    break;
  case GameState::PAUSE_BEFORE_RETRY:
    PauseBeforeRetry();
    break;
  case GameState::GAME_FINISHED:
    GameFinished();
    break;
  default:
    break;
  }
}
