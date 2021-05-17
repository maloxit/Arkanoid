#pragma once
#include "Simple2DGameEngine.hpp"

using namespace GameEngine;
using namespace std;

class Block;
class Ball;
class Bonus;
class Platform;
class Wall;
class Score;

class GameController : public Updatable
{
private:
  enum class GameState
  {
    PAUSE_BEFORE_START,
    PLAYING,
    PAUSE_BEFORE_RETRY,
    GAME_FINISHED
  } state;
  float pauseTimer;
  float secondTimer;
  string levelFile;
  Scene& scene;
  TTF_Font* font;
  shared_ptr<Score> score;
  list<shared_ptr<Block>> blockList;
  list<shared_ptr<Ball>> ballList;
  list<shared_ptr<Platform>> platformList;
  list<shared_ptr<Wall>> wallList;
  list<shared_ptr<Bonus>> bonusList;
  int solidBlocksCount;
  void ClearListsFromDestroyed();
  void LoadLevel(string& levelFile);
  void ResetBallAndPlatform();

  void PauseBeforeStart();
  void Playing();
  void PauseBeforeRetry();
  void GameFinished();
public:
  void AddBall();
  void AddScore(int points);
  bool TryHitWalls(Transform& transform, const Vector2f& direction, float step, weak_ptr<Wall>& closestHitWall, Hit& closestHit, Wall* exceptSelf);
  bool TryHitBalls(Transform& transform, const Vector2f& direction, float step, weak_ptr<Ball>& closestHitBall, Hit& closestHit, Ball* exceptSelf);
  bool TryHitPlatforms(Transform& transform, const Vector2f& direction, float step, weak_ptr<Platform>& closestHitPlatform, Hit& closestHit, Platform* exceptSelf);
  bool TryHitBlocks(Transform& transform, const Vector2f& direction, float step, weak_ptr<Block>& closestHitBlock, Hit& closestHit, Block* exceptSelf);
  GameController(Scene& scene, TTF_Font* font, const string& levelFile);
  virtual void Update(float deltaTime);
};
