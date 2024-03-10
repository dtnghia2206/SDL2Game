#pragma once

#include "SDL_image.h"

class TextureManager 
{

public:
	static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* renderer);
	static void Draw(SDL_Texture* texture, SDL_Renderer* renderer, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip);
};
