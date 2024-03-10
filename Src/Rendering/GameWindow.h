#pragma once

#include "SDL_image.h"
//#include "TextureManager.h"
//#include "ECS/Components.h"
//#include "Movement/Vector2D.h"
//#include "AssetManager.h"

class GameWindow
{
public:
	SDL_Window* voWindow;
	SDL_Renderer* voRenderer;

	GameWindow();
	~GameWindow();


	bool Initialize(const char* title, int vnXPosition, int vnYPosition, int vnWidth, int vnHeight, bool vbFullscreen);
	void Update();
	void PreRender();
	void PostRender();
	void Clean();

private:
	

};