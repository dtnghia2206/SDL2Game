#pragma once

#include <map>
#include <string>
#include "TextureManager.h"
#include "Movement/Vector2D.h"
#include "ECS\ECS.h"
#include "SDL_ttf.h"

class AssetManager
{
public:
	AssetManager(Manager* man);
	~AssetManager();

	// Game Objects
	void CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id, AssetManager* ip_oAssetManager, SDL_Renderer* ip_oRenderer, SDL_Rect* ip_oGameCamera);

	// Texture Management
	void AddTexture(std::string id, const char* path, SDL_Renderer* renderer);
	SDL_Texture* GetTexture(std::string id);

	void AddFont(std::string id, std::string path, int fontSize);
	TTF_Font* GetFont(std::string id);

private:

	Manager* manager;
	std::map<std::string, SDL_Texture*> textures;
	std::map<std::string, TTF_Font*> fonts;
};