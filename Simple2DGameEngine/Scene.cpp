#include "Scene.hpp"

#include "SDL.h"
#include "EventManager.hpp"
#include "RenderManager.hpp"
#include "Updatable.hpp"

namespace GameEngine
{
  Scene::Scene(const std::shared_ptr<EventManager>& eventManager, const std::shared_ptr<RenderManager>& renderManager) : eventManager(eventManager), renderManager(renderManager)
  {
  }

  void Scene::AddUpdatable(const std::shared_ptr<Updatable>& updatable)
  {
    updateList.push_back(updatable);
  }

  void Scene::Update(float dtSeconds)
  {
    auto updatable = updateList.begin();
    auto setEnd = updateList.end();
    while (updatable != setEnd)
    {
      if (updatable->expired())
      {
        updatable = updateList.erase(updatable);
        continue;
      }
      auto upd = updatable->lock();
      if (upd->enabled)
      {
        upd->Update(dtSeconds);
      }
      ++updatable;
    }
  }

  void Scene::Run()
  {
    bool running = true;
    auto lastTimePoint = clock();
    while (running)
    {
      running = eventManager->CheckEvents();
      auto newTimePoint = clock();
      auto dtMsec = newTimePoint - lastTimePoint;
      lastTimePoint = newTimePoint;
      float dtSeconds = 0.001f * float(dtMsec);
      Update(dtSeconds);
      renderManager->DrawFrame();
      renderManager->ShowFrame();
      SDL_Delay(16);
    }
  }
}