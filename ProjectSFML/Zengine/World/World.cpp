#include "World.h"
#include "Map.h"
#include "../ZenObject/ZenObject.h"

void World::Initialize()
{
	World::_map = new Map();

	//player initialization
	//And the rest of the objects of the world
}

void World::MapInitialize(string pathToTexturesTxt, string pathToTileTxt)
{
	World::_map->TextureInitialization(pathToTexturesTxt);
	World::_map->LoadMap(pathToTileTxt);
}

void World::DrawMap(sf::RenderWindow& windowIn)
{
	World::_map->DrawMap(windowIn);
}

