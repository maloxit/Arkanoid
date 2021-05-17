#include "GameWindow.hpp"

#include "SDL.h"

namespace GameEngine
{
  GameWindow::GameWindow() :GameWindow(1000, 800)
  {
  }

  GameWindow::GameWindow(int w, int h)
  {
    window = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RendererFlags::SDL_RENDERER_ACCELERATED);
  }

  GameWindow::~GameWindow()
  {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
  }
}