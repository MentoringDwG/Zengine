#include "World.h"
#include "Map.h"
#include "../ZenObject/ZenObject.h"
#include <SFML/Graphics.hpp>
#include "../Physics2D/ZenPhysics2D.h"

#pragma optimize("", off)
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

void World::PhysicalZenObject2DInitialize(ZenPhysics2D *zenPhysics2D, string enemySpritePath)
{
	enemy = new PhysicalZenObject2D(2, "Bird", enemySpritePath, sf::Vector2f(512.0f, 288.0f));
	zenPhysics2D->RegisterPhysicalObject(enemy);
	enemy->AddForce(1.0f, 3.0f, 3.0f, -1);
}

void World::ForceToPhysicsObject()
{
	if (enemy->GetTransposition() == 0)
	{
		if (enemy->forceDirection == -1)
		{
			enemy->AddForce(1.0f, 3.0f, 3.0f, 1);
		}
		else
		{
			enemy->AddForce(1.0f, 3.0f, 3.0f, -1);
		}
	}
}

void World::Draw(RenderingStack* renderStack)
{
	map->Draw(renderStack);
	playerCharacter->Draw(renderStack);
	enemy->Draw(renderStack);
}

Character* World::GetPlayer()
{
	return playerCharacter;
}

#pragma optimize("", on)

