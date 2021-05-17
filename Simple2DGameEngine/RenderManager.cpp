#include "RenderManager.hpp"

#include "GameWindow.hpp"
#include "Transform.hpp"
#include "RenderObject.hpp"

namespace GameEngine
{
  
  void RenderManager::AddRenderObject(const std::shared_ptr<RenderObject> rendObject)
  {
    renderObjectList.push_back(rendObject);
  }
  void RenderManager::DrawFrame()
  {
    SDL_SetRenderDrawColor(gameWindow->renderer, clearColor.x, clearColor.y, clearColor.z, clearColor.k);
    SDL_RenderClear(gameWindow->renderer);
    for (auto& layer : layers)
    {
      std::list<std::weak_ptr<RenderObject>>::iterator renderObject = renderObjectList.begin();
      std::list<std::weak_ptr<RenderObject>>::iterator setEnd = renderObjectList.end();
      while (renderObject != setEnd)
      {
        if (renderObject->expired())
        {
          renderObject = renderObjectList.erase(renderObject);
          continue;
        }
        std::shared_ptr<RenderObject> ro = renderObject->lock();
        if (ro->enabled && ro->layer == layer)
        {
          ro->Draw(gameWindow->renderer);
        }
        ++renderObject;
      }
    }
  }
  void RenderManager::ShowFrame()
  {
    SDL_RenderPresent(gameWindow->renderer);
  }

  RenderManager::RenderManager(const std::shared_ptr<GameWindow>& gameWindow, Vector4uc clearColor) : clearColor(clearColor)
  {
    this->gameWindow = gameWindow;
    renderObjectList = std::list<std::weak_ptr<RenderObject>>();
  }
}