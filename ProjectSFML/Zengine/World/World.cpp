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

void World::PhysicalZenObject2DInitialize(ZenPhysics2D* zenPhysics2D, string enemySpritePath)
{
	PhysicalZenObject2D* enemy = new PhysicalZenObject2D(2, "Bird");
	
	sf::Texture* texture = new sf::Texture;
	texture->loadFromFile(enemySpritePath);

	enemy->rectangleShape = new sf::RectangleShape;
	enemy->rectangleShape->setPosition(sf::Vector2f(10.0f, 10.0f));
	enemy->rectangleShape->setSize(sf::Vector2f(32.0f, 32.0f));
	enemy->rectangleShape->setTexture(texture);

	zenPhysics2D->RegisterPhysicalObject(enemy);
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


