#pragma once

#include "ECS.h"
#include "Components.h"
#include "Movement/Vector2D.h"

class ProjectileComponent : public Component
{
private:

	TransformComponent* transform;
	SDL_Rect* voGameCamera;

	int range = 0;
	int speed = 0;
	int distance = 0;
	Vector2D velocity;

public:
	ProjectileComponent(int rng, int sp, Vector2D vel, SDL_Rect* ip_oGameCameraAddr) : 
		range(rng), speed(sp), velocity(vel), voGameCamera(ip_oGameCameraAddr)
	{
	}

	~ProjectileComponent()
	{
	}

	void Initialize() override
	{
		transform = &entity->GetComponent<TransformComponent>();
		transform->voVelocity = velocity;
	}

	void Update() override
	{
		distance += speed;

		if (distance > range)
		{
			std::cout << "Out of Range" << std::endl;
			entity->Destroy();
		}
		else if (transform->voPosition.x > voGameCamera->x + voGameCamera->w ||
				 transform->voPosition.x < voGameCamera->x ||
				 transform->voPosition.y > voGameCamera->y + voGameCamera->h ||
				 transform->voPosition.y < voGameCamera->y)
		{
			std::cout << "Out of bounds!" << std::endl;
			entity->Destroy();
		}
	}



};
