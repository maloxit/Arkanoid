#pragma once
#include "Simple2DGameEngine.hpp"

using namespace GameEngine;
using namespace std;

class GameController;

class ArkanoidScene : public Scene
{
private:
  TTF_Font* font;
  shared_ptr<GameController> gameController;
public:
  ArkanoidScene(shared_ptr<EventManager>& eventManager, shared_ptr<RenderManager>& renderManager);
  ~ArkanoidScene();
};

