#pragma once
#include "Simple2DGameEngine.hpp"

using namespace GameEngine;
using namespace std;
class Score
{
private:
  Transform transform;
  int points;
  shared_ptr<RenderText> text;
public:
  Score(const Transform& transform, const shared_ptr<RenderManager>& renderManager, int points, TTF_Font* font, Vector4uc color);
  void Add(int points);
};

