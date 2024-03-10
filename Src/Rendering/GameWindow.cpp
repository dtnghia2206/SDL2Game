#include "GameWindow.h"

GameWindow::GameWindow()
{
}

GameWindow::~GameWindow()
{
}

bool GameWindow::Initialize(const char* title, int vnXPosition, int vnYPosition, int vnWidth, int vnHeight, bool vbFullscreen)
{
	int vnFlag = 0;
	if (vbFullscreen)
	{
		vnFlag = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		//std::cout << "SDL initialized" << std::endl;

		voWindow = SDL_CreateWindow(title, vnXPosition, vnYPosition, vnWidth, vnHeight, vnFlag);

		if (voWindow)
		{
			//std::cout << "Window created" << std::endl;
		}

		voRenderer = SDL_CreateRenderer(voWindow, -1, 0);
		if (voRenderer)
		{
			SDL_SetRenderDrawColor(voRenderer, 255, 255, 255, 255);
			//std::cout << "Renderer created" << std::endl;
		}

		return true;
	}
	else 
	{
		return false;
	}

}

void GameWindow::Update()
{
}

void GameWindow::PreRender()
{
	SDL_RenderClear(voRenderer);
}

void GameWindow::PostRender()
{
	SDL_RenderPresent(voRenderer);
}

void GameWindow::Clean()
{
	SDL_DestroyWindow(voWindow);
	SDL_DestroyRenderer(voRenderer);
	SDL_Quit();
	//std::cout << "Game closed!" << std::endl;
}
