#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* ip_sTexture, SDL_Renderer* ip_oRenderer)
{
	SDL_Surface* tempSurface = IMG_Load(ip_sTexture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(ip_oRenderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	
	return tex;
}

void TextureManager::Draw(SDL_Texture * texture, SDL_Renderer* renderer, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(renderer, texture, &src, &dest, NULL, NULL, flip);
}
