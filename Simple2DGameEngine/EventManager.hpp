#pragma once
#include <memory>
#include <list>
#include "SDL.h"

namespace GameEngine
{
  class EventListener;
  class GameWindow;

  class EventManager
  {
  private:
    std::shared_ptr<GameWindow> gameWindow;
    std::list<std::weak_ptr<EventListener>> mouseMoveEventLestenerList;
    std::list<std::weak_ptr<EventListener>> mouseClickEventLestenerList;
    std::list<std::weak_ptr<EventListener>> keyboardEventLestenerList;
    void SendEventToList(std::list<std::weak_ptr<EventListener>>& eventLestenerList, const SDL_Event& event);
  public:
    void AddMouseMoveEventListener(const std::shared_ptr<EventListener>& eventListener);
    void AddMouseClickEventListener(const std::shared_ptr<EventListener>& eventListener);
    void AddKeyboardEventListener(const std::shared_ptr<EventListener>& eventListener);
    bool CheckEvents();
    EventManager(const std::shared_ptr<GameWindow>& gameWindow);
  };

}