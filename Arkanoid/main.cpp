#include "Simple2DGameEngine.hpp"

#include "ArkanoidScene.hpp"

using namespace GameEngine;
using namespace std;

int main(int c, char* v[]) {
  SDL_Init(SDL_INIT_EVERYTHING);
  TTF_Init();
  {
    auto window = make_shared<GameWindow>(800, 800);
    auto eventManager = make_shared<EventManager>(window);
    auto renderManager = make_shared<RenderManager>(window, Vector4uc(0, 0, 0, 255));
    auto scene = make_shared<ArkanoidScene>(eventManager, renderManager);

    scene->Run();
  }
  TTF_Quit();
  SDL_Quit();
  return 0;
};