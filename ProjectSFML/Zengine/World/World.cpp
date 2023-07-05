#include "World.h"
#include "Map.h"
#include "../ZenObject/ZenObject.h"
#include <SFML/Graphics.hpp>

void World::Initialize(string PlayerName, string PlayerTexcurePath, float PlayerMoveSpeed)
{
	map = new Map();

	playerCharacter = new Character(PlayerName, PlayerTexcurePath, PlayerMoveSpeed);

	//And the rest of the objects of the world
}

void World::MapInitialize(string pathToTexturesTxt, string pathToTileTxt)
{
	map->TextureInitialization(pathToTexturesTxt);
	map->LoadMap(pathToTileTxt);
}

void World::Draw(RenderingStack* renderStack)
{
	map->Draw(renderStack);
	playerCharacter->Draw(renderStack);
}

Character* World::GetPlayer()
{
	return playerCharacter;
}


