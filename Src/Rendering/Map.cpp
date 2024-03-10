#include "Map.h"
#include <fstream>
#include "ECS/ECS.h"
#include "ECS/Components.h"

Map::Map(
	std::string		ip_sTextureID, 
	int				ip_nMapScale,
	int				ip_nTileSize,
	AssetManager*	ip_oAssetManager, 
	SDL_Renderer*	ip_oRenderer, 
	SDL_Rect*		ip_oCamera, 
	Manager*		ip_oManager 
)
{
	vsTextureID			= ip_sTextureID;
	vnMapScale			= ip_nMapScale;
	vnTileSize			= ip_nTileSize;
	vnScaledSize		= vnMapScale * vnTileSize;
	voMapAssetManager	= ip_oAssetManager;
	voMapRenderer		= ip_oRenderer;
	voMapCamera			= ip_oCamera;
	voManager			= ip_oManager;
}

Map::~Map()
{
}

void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
	char c;
	std::fstream mapFile;
	mapFile.open(path);

	int srcX, srcY;

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(c);
			srcY = atoi(&c) * vnTileSize;
			mapFile.get(c);
			srcX = atoi(&c) * vnTileSize;
			AddTile(srcX, srcY, x * vnScaledSize, y * vnScaledSize);
			mapFile.ignore();
		}
	}
	
	mapFile.ignore();

	
	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(c);
			if (c == '1')
			{
				auto& tcol(voManager->AddEntity());
				tcol.AddComponent<ColliderComponent>("terrain", x * vnScaledSize, y * vnScaledSize, vnScaledSize, voMapRenderer, voMapCamera);
				tcol.AddGroup(GROUP_LABEL::groupColliders);
			}
			mapFile.ignore();
		}
	}
	

	mapFile.close();
}

void Map::AddTile(int srcX, int srcY, int xpos, int ypos)
{
	auto& tile(voManager->AddEntity());
	tile.AddComponent<TileComponent>(srcX, srcY, xpos, ypos, vnTileSize, vnMapScale, vsTextureID, voMapAssetManager, voMapRenderer, voMapCamera);
	tile.AddGroup(GROUP_LABEL::groupMap);
}