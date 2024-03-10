#include "GameObject.h"

/*GameObject::GameObject(int* ip_nImage, int ip_nXPosition, int ip_nYPosition, int ip_nSpeed)
{
	vaImage = ip_nImage;
	vnWidth = ip_nImage[0];
	vnHeight = ip_nImage[1];
	vnXPosition = ip_nXPosition;
	vnYPosition = ip_nYPosition;
	vnSpeed = ip_nSpeed;
	vbIsMovingFreely = FALSE;
}*/

GameObject::GameObject(const char* ip_voTexture, SDL_Renderer* ip_voRenderer, int ip_vnXPos, int ip_vnYpos)
{
	voRenderer	= ip_voRenderer;
	vnXPosition = ip_vnXPos;
	vnYPosition = ip_vnYpos;
	LoadTexture(ip_voTexture);
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
	vnXPosition ++;
	vnYPosition ++;

	voSrcRect.h = 32;
	voSrcRect.w = 32;
	voSrcRect.x = 0;
	voSrcRect.y = 0;

	voDstRect.h = voSrcRect.h;
	voDstRect.w = voSrcRect.w;
	voDstRect.x = vnXPosition;
	voDstRect.y = vnYPosition;
}

void GameObject::Render()
{
	SDL_RenderCopy(voRenderer, voTexture, &voSrcRect, &voDstRect);
}

void GameObject::LoadTexture(const char* ip_vsFileName)
{
	SDL_Surface* tempSurface = IMG_Load(ip_vsFileName);
	voTexture = SDL_CreateTextureFromSurface(voRenderer, tempSurface);
	SDL_FreeSurface(tempSurface);
}

void GameObject::SetSpeed(int ip_nSpeed)
{
	vnSpeed = ip_nSpeed;
}

void GameObject::MoveUp()
{
	vnYPosition = vnYPosition - vnSpeed;
}

void GameObject::MoveDown()
{
	vnYPosition = vnYPosition + vnSpeed;
}

void GameObject::MoveRight()
{
	vnXPosition = vnXPosition + vnSpeed;
}

void GameObject::MoveLeft()
{
	vnXPosition = vnXPosition - vnSpeed;
}
