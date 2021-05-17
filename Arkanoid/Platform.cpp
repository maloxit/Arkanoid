#include "Platform.hpp"

Platform::Platform(const Transform& transform, const shared_ptr<RenderManager>& renderManager, const Vector2f& leftMaxPosition, const Vector2f& rightMaxPosition, float moveSpeed) : Updatable(true), EventListener(true), transform(transform), leftMaxPosition(leftMaxPosition), rightMaxPosition(rightMaxPosition)
{
	moveState = MoveState::IDLE;
	this->moveSpeed = moveSpeed;
	visuals = make_shared<RenderPrimitivesSet>(true, this->transform, RenderLayer::MIDDLE, 1);
	renderManager->AddRenderObject(static_pointer_cast<RenderObject, RenderPrimitivesSet>(visuals));
	visuals->AddPrimitive(RenderPrimitivesSet::PrimitiveType::FILL_RECT, Vector4uc(255, 50, 150, 255), Vector2f(0, 0), Vector2f(1, 1));
}

void Platform::Update(float deltaTime)
{
	switch (moveState)
	{
	case Platform::MoveState::IDLE:
		break;
	case Platform::MoveState::LEFT:
		transform.MoveLin(leftMaxPosition, deltaTime * moveSpeed);
		break;
	case Platform::MoveState::RIGHT:
		transform.MoveLin(rightMaxPosition, deltaTime * moveSpeed);
		break;
	default:
		break;
	}
}

void Platform::HandleEvent(const SDL_Event& event)
{
	const Uint8* keyboarnState = SDL_GetKeyboardState(NULL);
	switch (event.type)
	{
	case SDL_EventType::SDL_KEYDOWN:
		switch (event.key.keysym.scancode)
		{
		case SDL_SCANCODE_LEFT:
			moveState = MoveState::LEFT;
			break;
		case SDL_SCANCODE_RIGHT:
			moveState = MoveState::RIGHT;
			break;
		default:
			break;
		}
		break;
	case SDL_EventType::SDL_KEYUP:
		switch (event.key.keysym.scancode)
		{
		case SDL_SCANCODE_LEFT:
			if (keyboarnState[SDL_SCANCODE_RIGHT])
			{
				moveState = MoveState::RIGHT;
			}
			else
			{
				moveState = MoveState::IDLE;
			}
			break;
		case SDL_SCANCODE_RIGHT:
			if (keyboarnState[SDL_SCANCODE_LEFT])
			{
				moveState = MoveState::LEFT;
			}
			else
			{
				moveState = MoveState::IDLE;
			}
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}
