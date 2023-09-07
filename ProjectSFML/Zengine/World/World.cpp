#include "World.h"
#include "Map.h"
#include "../ZenObject/ZenObject.h"
#include <SFML/Graphics.hpp>
#include "../Physics2D/ZenPhysics2D.h"
#include "../Environment/Ground.h"
#include "../UIinGame/HeartsPanel.h"
#include "../Environment/CoinCounter.h"
#include "../Character/Character.h"
#include "Enemy.h"
#include "../Environment/Coin.h"

void World::Initialize(string PlayerName, string PlayerTexcurePath, float PlayerMoveSpeed)
{
	map = new Map();
	playerCharacter = new Character(PlayerName, PlayerTexcurePath, PlayerMoveSpeed);
	coinCounter = new CoinCounter(1, "coinCounter", sf::Vector2f(0, 0));
	heartPanel = new HeartsPanel();
}

void World::MapInitialize(string pathToTexturesTxt, string pathToTileTxt)
{
	map->TextureInitialization(pathToTexturesTxt);
	map->LoadMap(pathToTileTxt);
}

void World::PhysicalZenObject2DInitialize(string enemySpritePath)
{
	enemy = new Enemy(2, "Enemy", enemySpritePath, sf::Vector2f(512.0f, 288.0f), sf::Vector2f(32, 32), heartPanel);
	enemy->AddForce(1.0f, Vector2(-3.0f, 0.0f), 3.0f);

	ground = new Ground("Tiles/TxtFiles/Level1Ground.txt");
}

void World::ApplyForceToPhysicsObject()
{
	if (enemy->GetTransposition()->x == 0)
	{
		if (enemy->GetVelocity()->x < 0)
		{
			enemy->AddForce(1.0f, Vector2(3.0f, 0.0f), 3.0f);
		}
		else
		{
			enemy->AddForce(1.0f, Vector2(-3.0f, 0.0f), 3.0f);
		}
	}
}

void World::EnvironmentInitialize(string CoinPath, sf::Vector2f position1, sf::Vector2f position2)
{
	coins.push_back(new Coin(4, "Coin", CoinPath, position1, coinCounter));

	coins.push_back(new Coin(5, "Coin", CoinPath, position2, coinCounter));
}

void World::Draw(RenderingStack* renderStack)
{
	map->Draw(renderStack);
	playerCharacter->Draw(renderStack);
	ZenPhysics2D::Get()->Draw(renderStack);

	for (int i = 0; i < coins.size(); i++)
	{
		coins[i]->Draw(renderStack);
	}

	heartPanel->Draw(renderStack);
	coinCounter->Draw(renderStack);
}

void World::UpdateObjects()
{
	playerCharacter->UpdateCharacter();
	enemy->Update();
}

Character* World::GetPlayer()
{
	return playerCharacter;
}
