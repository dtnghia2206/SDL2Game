#pragma once

/**
 * @file Image.h
 *
 * @brief
 *
 * @author
 * Contact:
 *
 */

#include <iostream>
#include <Windows.h>  
#include <vector>
#include "SDL_image.h"

 /**
  * Implementation of GameObject class
  *
  *
  */

class GameObject
{
public:
	
	int  vnSpeed;
	int* vaImage;
	int  vnWidth;
	int  vnHeight;

	bool vbIsMovingFreely; //FOr player/ enemies that move in a path that is not pre-determined by the game. Used to run colision detection.

public:
	//GameObject(int* vpImage, int ip_nXPosition, int ip_nYPosition, int ip_nSpeed);
	GameObject(const char* ip_voTexture, SDL_Renderer* ip_voRenderer, int ip_vnXPos, int ip_vnYpos);
	~GameObject();

	void Update();
	void Render();
	void LoadTexture(const char* ip_vsFileName);
	
	
	void SetSpeed(int ip_nSpeed);
	void MoveUp();
	void MoveDown();
	void MoveRight();
	void MoveLeft();

private:
	int  vnXPosition;
	int  vnYPosition;

	SDL_Renderer* voRenderer;
	SDL_Texture* voTexture;
	SDL_Rect voSrcRect, voDstRect;

};

