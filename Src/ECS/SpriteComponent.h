#pragma once

#include "Components.h"
#include "SDL.h"
#include "Rendering/TextureManager.h"
#include "Animation.h"
#include <map>
#include "Resources/AssetManager.h"

class SpriteComponent : public Component
{
private:
	TransformComponent * transform;
	SDL_Texture *texture;
	SDL_Renderer* renderer;
	SDL_Rect srcRect, destRect;
	SDL_Rect *voGameCameraAddr;

	bool animated	= false;
	int  frames		= 0;
	int  speed		= 100;

public:

	int animIndex = 0;
	std::map<const char*, Animation> animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;

	SpriteComponent(std::string id, bool ip_bIsAnimated, AssetManager* ip_oAssetManager, SDL_Renderer* ip_oRenderer, SDL_Rect* ip_oGameCameraAddr)
	{
		animated = ip_bIsAnimated;

		Animation idle = Animation(0, 4, 100);
		Animation walk = Animation(0, 4, 100);

		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);

		Play("Idle");

		setTexture(id, ip_oAssetManager);
		renderer = ip_oRenderer;
		voGameCameraAddr = ip_oGameCameraAddr;
	}

	~SpriteComponent()
	{
	}

	void setTexture(std::string id, AssetManager* ip_oAssetManager)
	{
		texture = ip_oAssetManager->GetTexture(id);
	}

	void Initialize() override
	{

		transform = &entity->GetComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->vnWidth;
		srcRect.h = transform->vnHeight;
	}

	void Update() override
	{
		SDL_Rect voGameCamera;
		voGameCamera = *voGameCameraAddr;

		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		srcRect.y = animIndex * transform->vnHeight;

		destRect.x = static_cast<int>(transform->voPosition.x - voGameCamera.x);
		destRect.y = static_cast<int>(transform->voPosition.y - voGameCamera.y);
		destRect.w = transform->vnWidth  * transform->vnScale;
		destRect.h = transform->vnHeight * transform->vnScale;
	}

	void Draw() override
	{
		TextureManager::Draw(texture, renderer, srcRect, destRect, spriteFlip);
	}

	void Play(const char* animName)
	{
		frames		= animations[animName].frames;
		animIndex	= animations[animName].index;
		speed		= animations[animName].speed;
	}

};