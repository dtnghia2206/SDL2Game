#pragma once
#include <string>
#include <SDL.h>
#include "Components.h"
#include "TextureManager.h"

class ColliderComponent : public Component
{
public:
	SDL_Rect		voCollider;
	std::string		vsTag;

	SDL_Texture*	voTileTexture;
	SDL_Rect		voSrcRect, voDestRect;
	SDL_Rect*		voCamera;
	Vector2D		voPosition;
	SDL_Renderer*	voRenderer;

	TransformComponent* voTransform;

	ColliderComponent(std::string t, SDL_Renderer* ip_oRenderer, SDL_Rect* ip_oCamera)
	{
		vsTag = t;
		voRenderer = ip_oRenderer;
		voCamera = ip_oCamera;
	}

	ColliderComponent(std::string t, int xpos, int ypos, int size, SDL_Renderer* ip_oRenderer, SDL_Rect* ip_oCamera)
	{
		vsTag = t;
		voCollider.x = xpos;
		voCollider.y = ypos;
		voCollider.h = voCollider.w = size;
		
		voRenderer		= ip_oRenderer;
		voCamera		= ip_oCamera;
	}


	void Initialize() override
	{
		if (!entity->HasComponent<TransformComponent>())
		{
			entity->AddComponent<TransformComponent>();
		}

		voTransform = &entity->GetComponent<TransformComponent>();

		voTileTexture	= TextureManager::LoadTexture("Assets/ColTex.png", voRenderer);
		voSrcRect		= { 0, 0, 32, 32 };
		voDestRect		= { voCollider.x, voCollider.y, voCollider.w, voCollider.h };

	}

	void Update() override
	{
		if (vsTag != "terrain")
		{
			voCollider.x = static_cast<int>(voTransform->voPosition.x);
			voCollider.y = static_cast<int>(voTransform->voPosition.y);
			voCollider.w = voTransform->vnWidth  * voTransform->vnScale;
			voCollider.h = voTransform->vnHeight * voTransform->vnScale;
		}

		voDestRect.x = voCollider.x - voCamera->x;
		voDestRect.y = voCollider.y - voCamera->y;
	}

	void Draw() override
	{
		TextureManager::Draw(voTileTexture, voRenderer, voSrcRect, voDestRect, SDL_FLIP_NONE);
	}

};