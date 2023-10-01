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
#include "../UIinGame/UIScene.h"
#include "Confiner.h"

#include <fstream>

Level1::Level1(std::string levelJsonPath)
{
	std::ifstream jsonFileStream(levelJsonPath);
	jsonData = nlohmann::json::parse(jsonFileStream);
}

Level1::~Level1()
{
	delete currentMap;
	delete playerCharacter;
	delete ground;
	delete uiScene;
	delete castle;

	coins.clear();
	enemys.clear();
}

void Level1::Initialize(StateMachine* stateMachine)
{
	this->stateMachine = stateMachine;

	castle = new Castle(Vector2(160, 160), Vector2(6432, 320), stateMachine);
	confiner = new Confiner(Vector2(32, 544), Vector2(0, 0), Vector2(jsonData["width"]*32-32, 0));
}

void Level1::SetPlayer(class Character* playerCharacter)
{
	this->playerCharacter = playerCharacter;
}

void Level1::MapInitialize()
{
	currentMap = new Map();
	nlohmann::json tileMapData = jsonData["data"];
	mapManager.AddMap(0, currentMap, "Textures/TexturesLevel_1.txt", jsonData["height"], jsonData["width"], tileMapData);
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

void Level1::EnvironmentClear()
{
	coins.clear();
	enemys.clear();
}

void Level1::EnvironmentInitialize()
{
	if (jsonData.contains(ENEMYS))
	{
		nlohmann::json enemysJson = jsonData[ENEMYS];

		for (size_t idx = 0; idx < enemysJson.size(); idx++)
		{
			nlohmann::json enemy = enemysJson.at(idx);

			enemys.push_back(new Enemy(enemy["id"], enemy["name"], ENEMY_GRAPHIC_PATH, sf::Vector2f(enemy["x"] * TILE_SCALE, enemy["y"] * TILE_SCALE), sf::Vector2f(32, 32), uiScene->GetHeartPanel()));
		}
	}

	for (int i = 0; i < enemys.size(); i++)
	{
		enemys[i]->AddForce(1.0f, Vector2(-4.0f, 0.0f), 3.0f);
	}

	ground = new Ground(jsonData["Ground"]);

	if (jsonData.contains(COINS))
	{
		nlohmann::json coinsJson = jsonData[COINS];

		for (size_t idx = 0; idx < coinsJson.size(); idx++)
		{
			nlohmann::json coin = coinsJson.at(idx);

			coins.push_back(new Coin(coin["id"], coin["name"], COIN_GRAPHIC_PATH, sf::Vector2f(coin["x"]*TILE_SCALE, coin["y"]*TILE_SCALE), uiScene->GetCoinCounter()));
		}
	}
}

void Level1::Draw(RenderingStack* renderStack)
{
	confiner->SetPositionLeft(Vector2(0, 0));
	playerCharacter->Draw(renderStack);
	ZenPhysics2D::Get()->Draw(renderStack);

	for (int i = 0; i < coins.size(); i++)
	{
		coins[i]->Draw(renderStack);
	}

	uiScene->Draw(renderStack);
}

void Level1::UpdateObjects()
{
	if (playerCharacter != nullptr)
	{
		playerCharacter->UpdateCharacter();

		if (playerCharacter->physicalZenObject2D->zenShape->GetPosition().y > windowSize.y)
		{
			PlayerRespawn();
		}
	}

	for (int i = 0; i < enemys.size(); i++)
	{
		enemys[i]->Update();
	}
}

void Level1::PlayerRespawn()
{
	playerCharacter->Respawn();
	uiScene->GetHeartPanel()->UpdateHeartsState();
	mainCamera->setCenter(sf::Vector2f(windowSize.x / 2, mainCamera->getCenter().y));
	confiner->SetPositionLeft(Vector2(0, 0));
}

CharacterInputHandler* Level1::GetCharacterInputHandler()
{
	return playerCharacter->GetInputHandler();
}

void Level1::SetCamera(sf::View* mainCamera, Vector2 windowSize)
{
	this->mainCamera = mainCamera;
	this->windowSize = windowSize;

	float playerPositionX = playerCharacter->physicalZenObject2D->zenShape->GetPosition().x;

	if (playerPositionX > windowSize.x / 2 && playerPositionX > mainCamera->getCenter().x && playerPositionX < jsonData["width"]*TILE_SIZE - windowSize.x / 2)
	{
		mainCamera->setCenter(sf::Vector2f(playerPositionX, mainCamera->getCenter().y));
		confiner->SetPositionLeft(Vector2(playerPositionX - windowSize.x / 2, 0));
	}
}

void Level1::SetUIScene(UIScene* uiScene)
{
	this->uiScene = uiScene;
}

void Level1::LoadMap(int id, RenderingStack* renderStack, World* world)
{
	currentMap = mapManager.LoadMap(0, renderStack, world);
}