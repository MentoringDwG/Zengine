#include "Level1.h"
#include "Zengine/World/Map.h"
#include "Zengine/ZenObject/ZenObject.h"
#include <SFML/Graphics.hpp>
#include "Zengine/Physics2D/ZenPhysics2D.h"
#include "Zengine/Environment/Ground.h"
#include "../UIinGame/HeartsPanel.h"
#include "Zengine/Environment/CoinCounter.h"
#include "Zengine/Character/Character.h"
#include "Zengine/World/Enemy.h"
#include "Zengine/Environment/Coin.h"
#include "Zengine/Environment/Castle.h"
#include "Zengine/StateMachine/StateMachine.h"

Level1::~Level1()
{
	delete map;
	delete playerCharacter;
	delete enemy;
	delete ground;
	delete heartPanel;
	delete coinCounter;
	delete castle;

	coins.clear();
}

void Level1::Initialize(StateMachine* stateMachine)
{
	this->stateMachine = stateMachine;

	map = new Map();
	playerCharacter = new Character("Mario", "Graphics/Mario/Mario.png", 2);
	coinCounter = new CoinCounter(1, "coinCounter", sf::Vector2f(0, 0));
	heartPanel = new HeartsPanel(stateMachine);
	castle = new Castle(Vector2(160, 160), Vector2(768, 320), stateMachine);
}

void Level1::MapInitialize()
{
	map->TextureInitialization("Textures/TexturesLevel1.txt");
	map->LoadMap("Tiles/TxtFiles/Level1.txt");
}

void Level1::PhysicalZenObject2DInitialize()
{
	enemy = new Enemy(2, "Enemy", "Graphics/Enemy1.png", sf::Vector2f(512.0f, 288.0f), sf::Vector2f(32, 32), heartPanel);
	enemy->AddForce(1.0f, Vector2(-3.0f, 0.0f), 3.0f);

	ground = new Ground("Tiles/TxtFiles/Level1Ground.txt");
}

void Level1::ApplyForceToPhysicsObject()
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

void Level1::EnvironmentInitialize()
{
	coins.push_back(new Coin(4, "Coin", "Graphics/coin.png", sf::Vector2f(0,0), coinCounter));

	coins.push_back(new Coin(5, "Coin", "Graphics/coin.png", sf::Vector2f(0, 0), coinCounter));
}

void Level1::Draw(RenderingStack* renderStack)
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

void Level1::UpdateObjects()
{
	if (playerCharacter != nullptr)
	{
		playerCharacter->UpdateCharacter();
	}

	enemy->Update();
}

Character* Level1::GetPlayer()
{
	return playerCharacter;
}