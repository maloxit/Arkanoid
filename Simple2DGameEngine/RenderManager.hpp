#pragma once
#include <list>
#include <memory>

#include "Vectorf.hpp"

namespace GameEngine
{
  class RenderObject;
  class GameWindow;

  enum class RenderLayer
  {
    BOTTOM,
    MIDDLE,
    TOP
  };

  class RenderManager
  {
  private:
    RenderLayer layers[3] = { RenderLayer::BOTTOM, RenderLayer::MIDDLE ,RenderLayer::TOP };
    std::list<std::weak_ptr<RenderObject>> renderObjectList;
    std::shared_ptr<GameWindow> gameWindow;
    Vector4uc clearColor;
  public:
    void AddRenderObject(const std::shared_ptr<RenderObject> rendObject);
    void DrawFrame();
    void ShowFrame();
    RenderManager(const std::shared_ptr<GameWindow>& gameWindow, Vector4uc clearColor);
  };

}




