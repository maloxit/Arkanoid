#pragma once
#include <list>
#include <memory>
#include <ctime>



namespace GameEngine
{
  class Updatable;
  class EventManager;
  class RenderManager;

  class Scene
  {
  private:
    std::list<std::weak_ptr<Updatable>> updateList;
    void Update(float dtSeconds);
  public:
    const std::shared_ptr<EventManager> eventManager;
    const std::shared_ptr<RenderManager> renderManager;
    Scene(const std::shared_ptr<EventManager>& eventManager, const std::shared_ptr<RenderManager>& renderManager);
    void AddUpdatable(const std::shared_ptr<Updatable>& updatable);
    void Run();
  };

}