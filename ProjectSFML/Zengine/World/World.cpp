#include "World.h"
#include "Map.h"
#include "../ZenObject/ZenObject.h"
#include <SFML/Graphics.hpp>

void World::Initialize(string PlayerName, string PlayerTexcurePath)
{
	World::_map = new Map();

	World::playerCharacter = new Character(PlayerName, PlayerTexcurePath);

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

Character* World::GetPlayer()
{
	return World::playerCharacter;
}

