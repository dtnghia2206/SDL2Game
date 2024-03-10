#pragma once
#include <string>
#include <iostream>
#include "SDL.h"
#include "Resources/AssetManager.h"
#include "Enum.h"

class Map 
{
public:
	
	/*-------------------- Constructor --------------------*/
	Map(
		std::string		tID, 
		int				ms, 
		int				ts, 
		AssetManager*	ip_oAssetManager, 
		SDL_Renderer*	ip_oRenderer, 
		SDL_Rect*		ip_oCamera, 
		Manager*		ip_oManager 
	);
	
	~Map();

	void LoadMap(std::string path, int sizeX, int sizeY);
	void AddTile(int srcX, int srcY, int xpos, int ypos);

private:
	int				vnMapScale;
	int				vnTileSize;
	int				vnScaledSize;
	std::string		vsTextureID;
	AssetManager*	voMapAssetManager;
	SDL_Renderer*	voMapRenderer;
	SDL_Rect*		voMapCamera;
	Manager*		voManager;
};
