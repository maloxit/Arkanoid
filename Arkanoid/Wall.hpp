#pragma once
#include "Simple2DGameEngine.hpp"

using namespace GameEngine;
using namespace std;


class Wall
{
private:
  shared_ptr<RenderPrimitivesSet> visuals;
public:
  Transform transform;
  Wall(const Transform& transform, const shared_ptr<RenderManager>& renderManager);
};

