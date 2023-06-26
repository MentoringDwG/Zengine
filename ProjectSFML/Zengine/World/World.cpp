#include "World.h"
#include "Map.h"
#include "../ZenObject/ZenObject.h"
#include <SFML/Graphics.hpp>

void World::Initialize(string PlayerName, string PlayerTexcurePath)
{
	map = new Map();

	playerCharacter = new Character(PlayerName, PlayerTexcurePath);

	//And the rest of the objects of the world
}

void World::MapInitialize(string pathToTexturesTxt, string pathToTileTxt)
{
	map->TextureInitialization(pathToTexturesTxt);
	map->LoadMap(pathToTileTxt);
}

void World::DrawMap(sf::RenderWindow& windowIn)
{
	map->DrawMap(windowIn);
}

Character* World::GetPlayer()
{
	return playerCharacter;
}

void World::DrawPlayer(RenderingStack* renderStack)
{
	playerCharacter->DrawCharacter(renderStack);
}

