#include "MapManager.h"
#include <Zengine/World/Map.h>
#include <Zengine/World/World.h>

void MapManager::AddMap(int id, Map* map, std::string pathToTexturesTxt, int rows, int columns, nlohmann::json tileMapData)
{
	maps[id] = map;	
	maps[id]->TextureInitialization(pathToTexturesTxt);
	maps[id]->LoadMap(rows, columns, tileMapData);
}

Map* MapManager::LoadMap(int id, RenderingStack* renderStack, class World* world)
{
	renderStack->Clear();
	world->EnvironmentClear();
	maps[id]->Draw(renderStack);
	world->EnvironmentInitialize();
	world->Draw(renderStack);

	return maps[id];
}