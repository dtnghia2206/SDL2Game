#pragma once

#include "ECS.h"
#include "Movement/Vector2D.h"
#include "TextureManager.h"

class TileComponent : public Component
{
public:

	SDL_Texture*	voTileTexture;
	SDL_Rect		voSrcRect, voDestRect;
	SDL_Rect*		voCamera;
	Vector2D		voPosition;
	SDL_Renderer*	voRenderer;

	TileComponent() = default;

	~TileComponent()
	{
		SDL_DestroyTexture(voTileTexture);
	}

	TileComponent(int srcX, int srcY, int xpos, int ypos, int tsize, int tscale, std::string id, AssetManager* ip_oAssetManager, SDL_Renderer* ip_oRenderer, SDL_Rect* ip_oCamera)
	{
		voTileTexture = ip_oAssetManager->GetTexture(id);
		voRenderer	  = ip_oRenderer;
		voCamera	  = ip_oCamera;

		voSrcRect.x  = srcX;
		voSrcRect.y  = srcY;
		voSrcRect.w	 = voSrcRect.h = tsize;
		voPosition.x = static_cast<float>(xpos);
		voPosition.y = static_cast<float>(ypos);
		voDestRect.w = voDestRect.h = tsize * tscale;
	}

	void Update() override
	{
		voDestRect.x = static_cast<int>(voPosition.x - voCamera->x);
		voDestRect.y = static_cast<int>(voPosition.y - voCamera->y);
	}
	void Draw() override
	{
		TextureManager::Draw(voTileTexture, voRenderer, voSrcRect, voDestRect, SDL_FLIP_NONE);
	}
};