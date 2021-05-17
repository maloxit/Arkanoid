#include "ArkanoidScene.hpp"

#include "GameController.hpp"

ArkanoidScene::ArkanoidScene(shared_ptr<EventManager>& eventManager, shared_ptr<RenderManager>& renderManager) : Scene(eventManager, renderManager)
{
  font = TTF_OpenFont("Contra.ttf", 56);
  gameController = make_shared<GameController>(*this, font, string("MainLevel.txt"));
  AddUpdatable(static_pointer_cast<Updatable, GameController>(gameController));
}

ArkanoidScene::~ArkanoidScene()
{
  TTF_CloseFont(font);
}
