#include "RenderText.hpp"
#include "Transform.hpp"


namespace GameEngine
{

  RenderText::~RenderText()
  {
    if (lastTexture)
    {
      SDL_DestroyTexture(lastTexture);
    }
  }

  void RenderText::ChangeString(std::string textString)
  {
    this->textString = textString;
    needTextureUpdate = true;
  }

  Vector2f RenderText::GetTextSize()
  {
    int w, h;
    TTF_SizeUTF8(font, textString.c_str(), &w, &h);
    return Vector2f(static_cast<float>(w), static_cast<float>(h));
  }

  RenderText::RenderText(bool enabled, const Transform& transform, RenderLayer layer, const std::string& textString, TTF_Font* font, Vector4uc color) : RenderObject(enabled, transform, layer)
  {
    this->textString = textString;
    lastTexture = nullptr;
    needTextureUpdate = true;
    this->font = font;
    this->color = color;
  }

  void RenderText::Draw(SDL_Renderer* renderer)
  {
    if (needTextureUpdate)
    {
      SDL_Surface* textSurface = TTF_RenderUTF8_Solid(font, textString.c_str(), SDL_Color{ color.x, color.y, color.z, color.k });
      if (lastTexture)
      {
        SDL_DestroyTexture(lastTexture);
        lastTexture = nullptr;
      }
      lastTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
      SDL_FreeSurface(textSurface);
      needTextureUpdate = false;
    }
    SDL_FRect rect = SDL_FRect{ transform.position.x, transform.position.y, transform.size.x, transform.size.y };
    SDL_RenderCopyF(renderer, lastTexture, NULL, &rect);
  }

}