#include "SDL.h"
#include "GamePlay.h"

GamePlay *game = nullptr;

int main(int argc, char *argv[])
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;

	game = new GamePlay();

	game->Initialize("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

	while (game->Running())
	{
		frameStart = SDL_GetTicks();

		game->HandleEvent();
		game->Update();
		game->Render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->Close();

	return 0;

}
