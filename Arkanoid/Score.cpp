#include "Score.hpp"

Score::Score(const Transform& transform, const shared_ptr<RenderManager>& renderManager, int points, TTF_Font* font, Vector4uc color) : transform(transform)
{
  this->points = points;
  text = make_shared<RenderText>(true, this->transform, RenderLayer::TOP, to_string(this->points), font, color);
  renderManager->AddRenderObject(static_pointer_cast<RenderObject, RenderText>(text));
  this->transform.size = text->GetTextSize();
}

void Score::Add(int points)
{
  this->points += points;
  text->ChangeString(to_string(this->points));
  this->transform.size = text->GetTextSize();
}
