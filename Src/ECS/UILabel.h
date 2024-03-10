#pragma once

#include "ECS.h"
#include "AssetManager.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class UILabel : public Component
{
public:
	UILabel(int ip_XPos, 
			int ip_YPos, 
			std::string ip_sText, 
			std::string ip_sFont, 
			SDL_Color& ip_oColour, 
			SDL_Renderer* ip_oRenderer, 
			AssetManager* ip_oAsset)
	{
		voPosition.x	= ip_XPos;
		voPosition.y	= ip_YPos;
		vsLabelText		= ip_sText;
		vsLabelFont		= ip_sFont;
		voTextColour	= ip_oColour;
		voRenderer		= ip_oRenderer;
		voAsset			= ip_oAsset;

		SetLabelText(vsLabelText, vsLabelFont);
	}

	~UILabel() {}

	void SetLabelText(std::string text, std::string font)
	{
		SDL_Surface* surf	= TTF_RenderText_Blended(voAsset->GetFont(font), text.c_str(), voTextColour);
		voLabelTexture		= SDL_CreateTextureFromSurface(voRenderer, surf);
		
		SDL_FreeSurface(surf);
		SDL_QueryTexture(voLabelTexture, nullptr, nullptr, &voPosition.w, &voPosition.h);
	}

	void Draw() override
	{
		SDL_RenderCopy(voRenderer, voLabelTexture, nullptr, &voPosition);
	}

private:
	SDL_Rect      voPosition;
	std::string   vsLabelText;
	std::string   vsLabelFont;
	SDL_Color	  voTextColour;
	SDL_Texture*  voLabelTexture;
	SDL_Renderer* voRenderer;
	AssetManager* voAsset;
};
