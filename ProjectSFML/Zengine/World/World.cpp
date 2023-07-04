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

void World::AddMapToRenderStack(RenderingStack* renderStack)
{
	map->AddMapToRenderStack(renderStack);
}

Character* World::GetPlayer()
{
	return playerCharacter;
}

void World::AddCharacterToRenderStack(RenderingStack* renderStack)
{
	playerCharacter->AddCharacterToRenderStack(renderStack);
}

