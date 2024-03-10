#pragma once
#include "Components.h"
#include "Movement/Vector2D.h"

class TransformComponent : public Component
{
public:
	Vector2D voPosition;
	Vector2D voVelocity;

	int vnHeight = 32;
	int vnWidth  = 32;
	int vnScale  = 1;
	int vnSpeed  = 3;

	bool blocked = false;

	TransformComponent()
	{
		voPosition.Zero();
	}

	TransformComponent(int sc)
	{
		voPosition.Zero();
		vnScale = sc;
	}

	TransformComponent(float ip_nXPos, float ip_nYPos, int ip_nHeight, int ip_nWidth, int ip_nScale)
	{
		voPosition.x	= ip_nXPos;
		voPosition.y	= ip_nYPos;
		vnHeight		= ip_nHeight;
		vnWidth			= ip_nWidth;
		vnScale			= ip_nScale;
	}

	void Initialize() override
	{
		voVelocity.Zero();
	}
	void Update() override
	{
		voPosition.x += static_cast<int>(voVelocity.x * vnSpeed);
		voPosition.y += static_cast<int>(voVelocity.y * vnSpeed);
	}

};