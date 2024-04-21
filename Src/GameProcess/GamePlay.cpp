/**
 * @file
 *
 * @brief
 *
 * @author
 * Contact:
 *
 */

#include "GamePlay.h"
#include <sstream>
#include <ECS/UILabel.h>

GamePlay::GamePlay()
{
	voManager = new Manager(); 
	voPlayer1 = voManager->AddEntity_Pointer();
	voLabel   = voManager->AddEntity_Pointer();
	vbIsRunning = false;
	voGameWindow = new GameWindow();
	voAssets = new AssetManager(voManager);
	voCamera = { 0, 0, 800, 640 };
}

GamePlay::~GamePlay()
{
}

void GamePlay::Initialize(
	const char* title, 
	int vnXPosition, 
	int vnYPosition, 
	int vnWidth, 
	int vnHeight, 
	bool vbFullscreen
)
{
	voGameWindow = new GameWindow();
	if (voGameWindow->Initialize(title, vnXPosition, vnYPosition, vnWidth, vnHeight, vbFullscreen))
	{
		vbIsRunning = true;
	}
	else
	{
		vbIsRunning = false;
	}

	if (TTF_Init() == -1)
	{
		std::cout << "Error : SDL_TTF" << std::endl;
	}

	/* Map */
	
	voAssets->AddTexture("terrain", "Assets/terrain_ss.png", voGameWindow->voRenderer);
	voMap = new Map(
		"terrain", 
		3, 
		32, 
		voAssets, 
		voGameWindow->voRenderer, 
		&voCamera, 
		voManager
	);
	voMap->LoadMap("Assets/map.map", 25, 20);
	
	/* Player */
	voAssets->AddTexture("player", "Assets/player_animation3.png", voGameWindow->voRenderer);
	voPlayer1->AddComponent<TransformComponent>(800.0f, 640.0f, 64, 64, 1);
	voPlayer1->AddComponent<SpriteComponent>("player", true, voAssets, voGameWindow->voRenderer, &voCamera);
	voPlayer1->AddComponent<KeyboardController>();
	voPlayer1->AddComponent<ColliderComponent>("player", voGameWindow->voRenderer, &voCamera);
	voPlayer1->AddGroup(groupPlayers);

	/* Top Text */
	voAssets->AddFont("arial", "Assets/arial.ttf", 16);
	SDL_Color white = { 255, 255, 255, 255 };
	voLabel->AddComponent<UILabel>(10, 10, "Test String", "arial", white, voGameWindow->voRenderer, voAssets);

	/* Projectiles */
	voAssets->AddTexture("projectile", "Assets/proj.png", voGameWindow->voRenderer);
	voAssets->CreateProjectile(Vector2D(600, 600), Vector2D(2,  0), 200, 2, "projectile", voAssets, voGameWindow->voRenderer, &voCamera);
	voAssets->CreateProjectile(Vector2D(600, 620), Vector2D(2,  0), 200, 2, "projectile", voAssets, voGameWindow->voRenderer, &voCamera);
	voAssets->CreateProjectile(Vector2D(400, 600), Vector2D(2,  1), 200, 2, "projectile", voAssets, voGameWindow->voRenderer, &voCamera);
	voAssets->CreateProjectile(Vector2D(600, 600), Vector2D(2, -1), 200, 2, "projectile", voAssets, voGameWindow->voRenderer, &voCamera);

}



void GamePlay::HandleEvent()
{
	/*
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) 
	{
		case SDL_QUIT:
			vbIsRunning = false;
			break;
		default:
			break;
	}
	*/
}

void GamePlay::Update()
{
	


	SDL_Rect playerCol = voPlayer1->GetComponent<ColliderComponent>().voCollider;
	Vector2D playerPos = voPlayer1->GetComponent<TransformComponent>().voPosition;

	std::stringstream ss;
	ss << "Player position: " << playerPos;
	voLabel->GetComponent<UILabel>().SetLabelText(ss.str(), "arial");

	vnFrame++;
	
	voManager->Refresh();
	voManager->Update();
	
	voTiles         = voManager->GetGroup(GROUP_LABEL::groupMap);
	voPlayers		= voManager->GetGroup(GROUP_LABEL::groupPlayers);
	voColliders		= voManager->GetGroup(GROUP_LABEL::groupColliders);
	voProjectiles	= voManager->GetGroup(GROUP_LABEL::groupProjectiles);

	for (auto& c : voColliders)
	{
		SDL_Rect cCol = c->GetComponent<ColliderComponent>().voCollider;
		if (Collision::AABB(cCol, playerCol))
		{
			voPlayer1->GetComponent<TransformComponent>().voPosition = playerPos;
		}
	}

	/* Projectiles */
	for (auto& p : voProjectiles)
	{
		if (Collision::AABB(voPlayer1->GetComponent<ColliderComponent>().voCollider, p->GetComponent<ColliderComponent>().voCollider))
		{
			p->Destroy();
		}
	}
	
	/* Projectiles */

	
	voCamera.x = static_cast<int>(voPlayer1->GetComponent<TransformComponent>().voPosition.x - 400);
	voCamera.y = static_cast<int>(voPlayer1->GetComponent<TransformComponent>().voPosition.y - 320);

	if (voCamera.x < 0)
		voCamera.x = 0;
	if (voCamera.y < 0)
		voCamera.y = 0;
	if (voCamera.x > voCamera.w)
		voCamera.x = voCamera.w;
	if (voCamera.y > voCamera.h)
		voCamera.y = voCamera.h;
}

void GamePlay::Close()
{

}

void GamePlay::Render()
{
	SDL_RenderClear(voGameWindow->voRenderer);
	
	for (auto& t : voTiles)
	{
		t->Draw();
	}
	
	for (auto& c : voColliders)
	{
		c->Draw();
	}
	

	for (auto& p : voPlayers)
	{
		p->Draw();
	}

	for (auto& p : voProjectiles)
	{
		p->Draw();
	}

	voLabel->Draw();

	SDL_RenderPresent(voGameWindow->voRenderer);
}

bool GamePlay::Running()
{
	return vbIsRunning;
}


