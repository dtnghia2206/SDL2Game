#pragma once

#include "SDL.h"
#include <iostream>
#include <vector>
#include "Movement/Collision.h"
#include "GameWindow.h"
#include "GameObject.h"
#include "AssetManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Enum.h"

class GamePlay
{
public:
	GamePlay();
	~GamePlay();


	void Initialize(const char* title, int vnXPosition, int vnYPosition, int vnWidth, int vnHeight, bool vbFullscreen);
	void HandleEvent();
	void Update();
	void Close();
	void Render();
	bool Running();	
	enum groupLabels : std::size_t
	{
		groupMap,
		groupPlayers,
		groupColliders,
		groupProjectiles
	};

private:
	bool			vbIsRunning;
	int				vnFrame = 0;
	AssetManager*	voAssets;
	GameWindow*		voGameWindow;
	SDL_Rect		voCamera;
	
	
	Map*				 voMap;
	Manager*			 voManager;
	Entity*				 voPlayer1;
	Entity*				 voLabel;
	std::vector<Entity*> voColliders;
	std::vector<Entity*> voProjectiles;
	std::vector<Entity*> voTiles;
	std::vector<Entity*> voPlayers;


};