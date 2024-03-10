#include "AssetManager.h"
#include "ECS\Components.h"
#include "Enum.h"

AssetManager::AssetManager(Manager* man) : manager(man)
{}

AssetManager::~AssetManager()
{}

void AssetManager::CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id, AssetManager* ip_oAssetManager, SDL_Renderer* ip_oRenderer, SDL_Rect* ip_oGameCameraAddr)
{
	Entity* voProjectiles;
	voProjectiles = manager->AddEntity_Pointer();
	voProjectiles->AddComponent<TransformComponent>(pos.x, pos.y, 32, 32, 1);
	voProjectiles->AddComponent<SpriteComponent>(id, false, ip_oAssetManager, ip_oRenderer, ip_oGameCameraAddr);
	voProjectiles->AddComponent<ProjectileComponent>(range, speed, vel, ip_oGameCameraAddr);
	voProjectiles->AddComponent<ColliderComponent>("projectile", ip_oRenderer, ip_oGameCameraAddr);
	voProjectiles->AddGroup(GROUP_LABEL::groupProjectiles);
}

void AssetManager::AddTexture(std::string id, const char* path, SDL_Renderer* renderer)
{
	textures.emplace(id, TextureManager::LoadTexture(path, renderer));
}

SDL_Texture* AssetManager::GetTexture(std::string id)
{
	return textures[id];
}

void AssetManager::AddFont(std::string id, std::string path, int fontSize)
{
	fonts.emplace(id, TTF_OpenFont(path.c_str(), fontSize));
}
TTF_Font* AssetManager::GetFont(std::string id)
{
	return fonts[id];
}