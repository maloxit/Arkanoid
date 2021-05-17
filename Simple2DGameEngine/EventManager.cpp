#include "EventManager.hpp"

#include "GameWindow.hpp"
#include "EventListener.hpp"

namespace GameEngine
{
  void EventManager::SendEventToList(std::list<std::weak_ptr<EventListener>>& eventLestenerList, const SDL_Event& event)
  {
    auto eventListener = eventLestenerList.begin();
    auto listEnd = eventLestenerList.end();
    while (eventListener != listEnd)
    {
      if (eventListener->expired())
      {
        eventListener = eventLestenerList.erase(eventListener);
        continue;
      }
      auto el = eventListener->lock();
      if (el->isListening)
      {
        el->HandleEvent(event);
      }
      ++eventListener;
    }
  }

  void EventManager::AddMouseMoveEventListener(const std::shared_ptr<EventListener>& eventListener)
  {
    mouseMoveEventLestenerList.push_back(eventListener);
  }

  void EventManager::AddMouseClickEventListener(const std::shared_ptr<EventListener>& eventListener)
  {
    mouseClickEventLestenerList.push_back(eventListener);
  }

  void EventManager::AddKeyboardEventListener(const std::shared_ptr<EventListener>& eventListener)
  {
    keyboardEventLestenerList.push_back(eventListener);
  }



  bool EventManager::CheckEvents()
  {
    bool running = true;
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
      switch (event.type)
      {
      case SDL_EventType::SDL_QUIT:
        running = false;
        break;
      case SDL_EventType::SDL_MOUSEBUTTONDOWN:
      case SDL_EventType::SDL_MOUSEBUTTONUP:
      case SDL_EventType::SDL_MOUSEWHEEL:
        SendEventToList(mouseClickEventLestenerList, event);
        break;
      case SDL_EventType::SDL_MOUSEMOTION:
        SendEventToList(mouseMoveEventLestenerList, event);
      break;
      case SDL_EventType::SDL_KEYDOWN:
      case SDL_EventType::SDL_KEYUP:
        SendEventToList(keyboardEventLestenerList, event);
        break;
      default:
        break;
      }
    }
    return running;
  }

  EventManager::EventManager(const std::shared_ptr<GameWindow>& gameWindow) : gameWindow(gameWindow) { };
}