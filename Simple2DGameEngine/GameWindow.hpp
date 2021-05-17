#pragma once

#include "SDL.h"
#include "SDL_ttf.h"

namespace GameEngine
{

  class GameWindow
  {
  public:
    SDL_Window* window;
    SDL_Renderer* renderer;
    GameWindow();
    GameWindow(int w, int h);
    ~GameWindow();
  };

}