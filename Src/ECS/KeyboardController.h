#pragma once
#include "SDL.h"
#include "ECS.h"
#include "Components.h"
#include <iostream>
#include <vector>

class KeyboardController : public Component
{
public:
	TransformComponent*	voTransform;
	SpriteComponent*	voSprite;
	SDL_Event			voEvent;

	void Initialize() override
	{
		voTransform = &entity->GetComponent<TransformComponent>();
		voSprite	= &entity->GetComponent<SpriteComponent>();
	}

	void Update() override
	{
		SDL_PollEvent(&voEvent);
		if (voEvent.type == SDL_KEYDOWN)
		{
			switch (voEvent.key.keysym.sym)
			{
			case SDLK_w:
				voTransform->voVelocity.y = -1;
				voSprite->Play("Walk");
				break;
			case SDLK_a:
				voTransform->voVelocity.x = -1;
				voSprite->Play("Walk");
				voSprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				break;
			case SDLK_d:
				voTransform->voVelocity.x = 1;
				voSprite->Play("Walk");
				break;
			case SDLK_s:
				voTransform->voVelocity.y = 1;
				voSprite->Play("Walk");
				break;
			default:
				break;
			}
		}
	
		if (voEvent.type == SDL_KEYUP)
		{
			switch (voEvent.key.keysym.sym)
			{
			case SDLK_w:
				voTransform->voVelocity.y = 0;
				voSprite->Play("Idle");
				break;
			case SDLK_a:
				voTransform->voVelocity.x = 0;
				voSprite->Play("Idle");
				voSprite->spriteFlip = SDL_FLIP_NONE;
				break;
			case SDLK_d:
				voTransform->voVelocity.x = 0;
				voSprite->Play("Idle");
				break;
			case SDLK_s:
				voTransform->voVelocity.y = 0;
				voSprite->Play("Idle");
				break;
			//case SDLK_ESCAPE:
				//Game::isRunning = false;
			default:
				break;
			}
		}
	}
};