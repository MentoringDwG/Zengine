#include "World.h"
#include "Map.h"
#include "../ZenObject/ZenObject.h"
#include <SFML/Graphics.hpp>
#include "../Physics2D/ZenPhysics2D.h"

void World::Initialize(string PlayerName, string PlayerTexcurePathR, string PlayerTexcurePathL, float PlayerMoveSpeed)
{
	map = new Map();

	playerCharacter = new Character(PlayerName, PlayerTexcurePathR, PlayerTexcurePathL, PlayerMoveSpeed);

	coinCounter = new CoinCounter(1, "coinCounter", sf::Vector2f(0, 0));
}

void World::MapInitialize(string pathToTexturesTxt, string pathToTileTxt)
{
	map->TextureInitialization(pathToTexturesTxt);
	map->LoadMap(pathToTileTxt);
}

void World::PhysicalZenObject2DInitialize(ZenPhysics2D *zenPhysics2D, string enemySpritePath)
{
	enemy = new PhysicalZenObject2D(2, "Enemy", enemySpritePath, sf::Vector2f(512.0f, 288.0f), sf::Vector2f(32, 32));
	zenPhysics2D->RegisterPhysicalObject(enemy);
	enemy->AddForce(1.0f, -3.0f, 3.0f);

	playerCharacter->SetCollider(new Vector2(playerCharacter->zenShape->GetPosition().x, playerCharacter->zenShape->GetPosition().y), 35, zenPhysics2D);
}

void World::ApplyForceToPhysicsObject()
{
	if (enemy->GetTransposition() == 0)
	{
		if (enemy->GetVelocityX()<0)
		{
			enemy->AddForce(1.0f, 3.0f, 3.0f);
		}
		else
		{
			enemy->AddForce(1.0f, -3.0f, 3.0f);
		}
	}
}

void World::EnvironmentInitialize(string CoinPath, sf::Vector2f position1, sf::Vector2f position2, ZenPhysics2D* zenPhysics2D)
{
	coin1 = new Coin(4, "Coin", CoinPath, position1, coinCounter);
	coin1->SetCollider(new Vector2(position1.x, position1.y), 20, zenPhysics2D);

	coin2 = new Coin(5, "Coin", CoinPath, position2, coinCounter);
	coin2->SetCollider(new Vector2(position2.x, position2.y), 20, zenPhysics2D);
}

void World::Draw(RenderingStack* renderStack, ZenPhysics2D* zenPhysics2D)
{
	map->Draw(renderStack);
	playerCharacter->Draw(renderStack);
	zenPhysics2D->Draw(renderStack);
	coin1->Draw(renderStack);
	coin2->Draw(renderStack);
}

Character* World::GetPlayer()
{
	return playerCharacter;
}
