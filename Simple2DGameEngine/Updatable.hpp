#pragma once
#include <memory>
namespace GameEngine
{
  class Updatable
  {
  public:
    bool enabled;
    Updatable(bool enabled);
    virtual void Update(float deltaTime) = 0;
    virtual ~Updatable() {};
  };

}