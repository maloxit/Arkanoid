#pragma once
#include <memory>
#include "SDL.h"


namespace GameEngine
{
  class EventListener
  {
  public:
    bool isListening;
    EventListener(bool isListening);
    virtual void HandleEvent(const SDL_Event& event) = 0;
  };
}