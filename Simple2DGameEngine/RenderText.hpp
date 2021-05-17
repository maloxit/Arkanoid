#pragma once
#include "SDL.h"
#include "SDL_ttf.h"

#include <string>
#include "Vectorf.hpp"
#include "RenderObject.hpp"

namespace GameEngine
{
  class RenderText : public RenderObject
  {
  private:
    bool needTextureUpdate;
    SDL_Texture* lastTexture;
    Vector4uc color;
    TTF_Font* font;
    std::string textString;
  public:
    void ChangeString(std::string textString);
    Vector2f GetTextSize();
    RenderText(bool enabled, const Transform& transform, RenderLayer layer, const std::string& textString, TTF_Font* font, Vector4uc color);
    virtual void Draw(SDL_Renderer* renderer);
    ~RenderText();
  };

}