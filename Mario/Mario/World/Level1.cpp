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
	delete ground;
	delete heartPanel;
	delete coinCounter;
	delete castle;

	coins.clear();
	enemys.clear();
}

void Level1::Initialize(StateMachine* stateMachine)
{
	this->stateMachine = stateMachine;

	map = new Map();
	playerCharacter = new Character("Mario", "Graphics/Mario/Mario.png", 3);
	coinCounter = new CoinCounter(1, "coinCounter", sf::Vector2f(0, 0));
	heartPanel = new HeartsPanel(stateMachine);
	castle = new Castle(Vector2(160, 160), Vector2(6432, 320), stateMachine);
	confiner = new Confiner(Vector2(32, 544), Vector2(0, 0), Vector2(6720, 0));
}

void Level1::MapInitialize()
{
	map->TextureInitialization("Textures/TexturesLevel_1.txt");
	map->LoadMap("Tiles/TxtFiles/Level_1.txt");
}

void Level1::PhysicalZenObject2DInitialize()
{
	enemys.push_back(new Enemy(2, "Enemy", "Graphics/Enemy1.png", sf::Vector2f(768.0f, 288.0f), sf::Vector2f(32, 32), heartPanel));
	enemys.push_back(new Enemy(16, "Enemy", "Graphics/Enemy1.png", sf::Vector2f(1408.0f, 448.0f), sf::Vector2f(32, 32), heartPanel));
	enemys.push_back(new Enemy(17, "Enemy", "Graphics/Enemy1.png", sf::Vector2f(3456.0f, 448.0f), sf::Vector2f(32, 32), heartPanel));
	enemys.push_back(new Enemy(18, "Enemy", "Graphics/Enemy1.png", sf::Vector2f(4704.0f, 448.0f), sf::Vector2f(32, 32), heartPanel));
	enemys.push_back(new Enemy(19, "Enemy", "Graphics/Enemy1.png", sf::Vector2f(5440.0f, 288.0f), sf::Vector2f(32, 32), heartPanel));

	for (int i = 0; i < enemys.size(); i++)
	{
		enemys[i]->AddForce(1.0f, Vector2(-4.0f, 0.0f), 3.0f);
	}
	
	ground = new Ground("Tiles/TxtFiles/Level1Ground.txt");
}

void Level1::ApplyForceToPhysicsObject()
{
	for (int i = 0; i < enemys.size(); i++)
	{
		if (enemys[i]->GetTransposition()->x == 0)
		{
			if (enemys[i]->GetVelocity()->x < 0)
			{
				enemys[i]->AddForce(1.0f, Vector2(4.0f, 0.0f), 3.0f);
			}
			else
			{
				enemys[i]->AddForce(1.0f, Vector2(-4.0f, 0.0f), 3.0f);
			}
		}
	}
}

void Level1::EnvironmentInitialize()
{
	coins.push_back(new Coin(4, "Coin", "Graphics/coin.png", sf::Vector2f(512, 288), coinCounter));
	coins.push_back(new Coin(5, "Coin", "Graphics/coin.png", sf::Vector2f(704, 160), coinCounter));
	coins.push_back(new Coin(6, "Coin", "Graphics/coin.png", sf::Vector2f(1504, 288), coinCounter));
	coins.push_back(new Coin(7, "Coin", "Graphics/coin.png", sf::Vector2f(2496, 320), coinCounter));
	coins.push_back(new Coin(8, "Coin", "Graphics/coin.png", sf::Vector2f(2720, 192), coinCounter));
	coins.push_back(new Coin(9, "Coin", "Graphics/coin.png", sf::Vector2f(2976, 320), coinCounter));
	coins.push_back(new Coin(10, "Coin", "Graphics/coin.png", sf::Vector2f(3456, 192), coinCounter));
	coins.push_back(new Coin(11, "Coin", "Graphics/coin.png", sf::Vector2f(3740, 320), coinCounter));
	coins.push_back(new Coin(12, "Coin", "Graphics/coin.png", sf::Vector2f(4064, 192), coinCounter));
	coins.push_back(new Coin(13, "Coin", "Graphics/coin.png", sf::Vector2f(4128, 320), coinCounter));
	coins.push_back(new Coin(14, "Coin", "Graphics/coin.png", sf::Vector2f(5376, 288), coinCounter));
	coins.push_back(new Coin(15, "Coin", "Graphics/coin.png", sf::Vector2f(6016, 192), coinCounter));
}

void Level1::Draw(RenderingStack* renderStack)
{
	confiner->SetPositionLeft(Vector2(0, 0));
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

	for (int i = 0; i < enemys.size(); i++)
	{
		enemys[i]->Update();
	}
}

CharacterInputHandler* Level1::GetCharacterInputHandler()
{
	return playerCharacter->GetInputHandler();
}

void Level1::SetCamera(sf::View* mainCamera)
{
	if (playerCharacter->physicalZenObject2D->zenShape->GetPosition().x > 480 && playerCharacter->physicalZenObject2D->zenShape->GetPosition().x> mainCamera->getCenter().x && playerCharacter->physicalZenObject2D->zenShape->GetPosition().x < 6240)
	{
		mainCamera->setCenter(sf::Vector2f(playerCharacter->physicalZenObject2D->zenShape->GetPosition().x, mainCamera->getCenter().y));
		confiner->SetPositionLeft(Vector2(playerCharacter->physicalZenObject2D->zenShape->GetPosition().x - 480, 0));
	}
}