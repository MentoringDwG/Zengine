#include "Level1.h"
#include <SFML/Graphics.hpp>

#include <Zengine/World/Map.h>
#include <Zengine/ZenObject/ZenObject.h>
#include <Zengine/Physics2D/ZenPhysics2D.h>
#include <Zengine/StateMachine/StateMachine.h>

#include "../Environment/Ground.h"
#include "../UIinGame/HeartsPanel.h"
#include "../Environment/CoinCounter.h"
#include "../Character/Character.h"
#include "../Environment/Enemy.h"
#include "../Environment/Coin.h"
#include "../Environment/Castle.h"
#include "Confiner.h"

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
	confiner = new Confiner(Vector2(32, 544), Vector2(0, 0), Vector2(928, 0));
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
	coins.push_back(new Coin(4, "Coin", "Graphics/coin.png", sf::Vector2f(288, 192), coinCounter));

	coins.push_back(new Coin(5, "Coin", "Graphics/coin.png", sf::Vector2f(608, 192), coinCounter));
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

CharacterInputHandler* Level1::GetCharacterInputHandler()
{
	return playerCharacter->GetInputHandler();
}

void Level1::SetCamera(sf::View* mainCamera)
{
	if (playerCharacter->physicalZenObject2D->zenShape->GetPosition().x > 480)
	{
		mainCamera->setCenter(sf::Vector2f(playerCharacter->physicalZenObject2D->zenShape->GetPosition().x, mainCamera->getCenter().y));
	}
}