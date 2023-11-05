#include "Level.h"
#include <SFML/Graphics.hpp>

#include <Zengine/World/Map.h>
#include <Zengine/ZenObject/ZenObject.h>
#include <Zengine/Physics2D/ZenPhysics2D.h>
#include <Zengine/StateMachine/StateMachine.h>
#include <Zengine/Audio/AudioSystem.h>
#include <Zengine/Animation/AnimationDefinitionManager.h>

#include "../Environment/Ground.h"
#include "../UIinGame/HeartsPanel.h"
#include "../UIinGame/KeyPanel.h"
#include "../Environment/CoinCounter.h"
#include "../Character/Character.h"
#include "../Environment/Enemy.h"
#include "../Environment/Coin.h"
#include "../Environment/Castle.h"
#include "../Environment/QuestionMark.h"
#include "../UIinGame/UIScene.h"
#include "Confiner.h"
#include "MapLoader.h"
#include "../Environment/Key.h"

#include <fstream>

Level::Level(std::string levelJsonPath)
{
	std::ifstream jsonFileStream(levelJsonPath);
	jsonData = nlohmann::json::parse(jsonFileStream);

	AnimationDefinitionManager::Get()->AddAnimationDefinition("Json/Animations/enemyWalk.json", "EnemyWalk");
	AnimationDefinitionManager::Get()->AddAnimationDefinition("Json/Animations/coin.json", "Coin");
	AnimationDefinitionManager::Get()->AddAnimationDefinition("Json/Animations/key.json", "Key");
	AnimationDefinitionManager::Get()->AddAnimationDefinition("Json/Animations/questionmark.json", "QuestionMark");
}

Level::~Level()
{
	delete currentMap;
	delete playerCharacter;
	delete ground;
	delete uiScene;
	delete castle;

	coins.clear();
	enemys.clear();
	keys.clear();
	questionMarks.clear();
}

void Level::Initialize(AudioSystem* audioSystem)
{
	this->audioSystem = audioSystem;

	confiner = new Confiner(Vector2(32, 544), Vector2(0, 0), Vector2((float)jsonData["width"]*32-32, 0));
	ground = new Ground();
	isMapLoaded = false;
}

void Level::SetPlayer(class Character* playerCharacter)
{
	this->playerCharacter = playerCharacter;
}

void Level::MapInitialize()
{
	nlohmann::json tileMapData = jsonData["data"];
	
	currentMap = new Map();
}

void Level::ApplyForceToPhysicsObject()
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

void Level::EnvironmentClear()
{
	for (int i = 0; i < coins.size(); i++)
	{
		coins[i]->~Coin();
	}
	coins.clear();

	for (int i = 0; i < keys.size(); i++)
	{
		keys[i]->~Key();
	}
	keys.clear();

	for (int i = 0; i < questionMarks.size(); i++)
	{
		questionMarks[i]->~QuestionMark();
	}
	questionMarks.clear();

	for (int i = 0; i < enemys.size(); i++)
	{
		enemys[i]->~Enemy();
	}
	enemys.clear();

	if (playerCharacter != nullptr)
	{
		playerCharacter->ClearCollisionColliders();
	}

	if (ground != nullptr)
	{
		ground->~Ground();
	}

	for (int i = 0; i < mapLoaders.size(); i++)
	{
		mapLoaders[i]->~MapLoader();
	}
	mapLoaders.clear();

	playerPositions.clear();
}

void Level::EnvironmentInitialize()
{
	if (enemys.size() == 0)
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
	}

	if (coins.size() == 0)
	{
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

	if (questionMarks.size() == 0)
	{
		if (jsonData.contains(QUESTION_MARKS))
		{
			nlohmann::json questionMarksJson = jsonData[QUESTION_MARKS];

			for (size_t idx = 0; idx < questionMarksJson.size(); idx++)
			{
				nlohmann::json questionMark = questionMarksJson.at(idx);

				questionMarks.push_back(new QuestionMark(questionMark["id"], questionMark["name"], QUESTION_MARK_GRAPHIC_PATH, sf::Vector2f(questionMark["x"] * TILE_SCALE, questionMark["y"] * TILE_SCALE), this));
			}
		}
	}

	if (keys.size() == 0)
	{
		if (jsonData.contains(KEYS))
		{
			nlohmann::json keysJson = jsonData[KEYS];
			hasKey = true;

			for (size_t idx = 0; idx < keysJson.size(); idx++)
			{
				nlohmann::json key = keysJson.at(idx);

				keys.push_back(new Key(key["id"], key["name"], KEY_GRAPHIC_PATH, sf::Vector2f(key["x"] * TILE_SCALE, key["y"] * TILE_SCALE), uiScene->GetKeyPanel()));
			}
		}
		else
		{
			hasKey = false;
		}
	}

	if (mapLoaders.size() == 0)
	{
		if (jsonData.contains(MAP_LOADER))
		{
			nlohmann::json mapLoadersJson = jsonData[MAP_LOADER];

			for (size_t idx = 0; idx < mapLoadersJson.size(); idx++)
			{
				nlohmann::json mapLoader = mapLoadersJson.at(idx);
				mapLoaders.push_back(new MapLoader(mapLoader["id"], mapLoader["name"], Vector2(mapLoader["width"]*TILE_SCALE, mapLoader["height"]*TILE_SCALE), Vector2(mapLoader["x"]*TILE_SCALE, mapLoader["y"]*TILE_SCALE), mapLoader["tag"], playerCharacter));
				mapLoaders[mapLoaders.size() - 1]->SetMapToLoad(mapLoader["textureFilePath"], mapLoader["mapJsonPath"], this, mapLoader["playerPositionId"]);
			}
		}
	}

	if (ground->CollidersVectorSize() == 0)
	{
		ground->SetBoxColliders(jsonData["Ground"]);
	}


	if (jsonData.contains(PLAYER_POSITIONS))
	{
		nlohmann::json playerPositionsJson = jsonData[PLAYER_POSITIONS];

		for (size_t idx = 0; idx < playerPositionsJson.size(); idx++)
		{
			nlohmann::json playerPosition = playerPositionsJson.at(idx);

			playerPositions[playerPosition["id"]] = new Vector2(playerPosition["x"], playerPosition["y"]);
		}
	}
}

void Level::Draw(RenderingStack* renderStack)
{
	confiner->SetPositionLeft(Vector2(0, 0));
	playerCharacter->Draw(renderStack);
	ZenPhysics2D::Get()->Draw(renderStack);

	for (int i = 0; i < coins.size(); i++)
	{
		coins[i]->Draw(renderStack);
	}

	for (int i = 0; i < keys.size(); i++)
	{
		keys[i]->Draw(renderStack);
	}

	for (int i = 0; i < questionMarks.size(); i++)
	{
		questionMarks[i]->Draw(renderStack);
	}

	uiScene->Draw(renderStack);
}

void Level::UpdateObjects()
{
	if (!IsWorldLoaded())
	{
		return;
	}
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

void Level::PlayerRespawn()
{
	audioSystem->PlaySingleShot("die");
	playerCharacter->physicalZenObject2D->zenShape->SetPosition(sf::Vector2f(playerPositions[0]->x * TILE_SCALE, playerPositions[0]->y * TILE_SCALE));
	uiScene->GetHeartPanel()->UpdateHeartsState();
	mainCamera->setCenter(sf::Vector2f(windowSize.x / 2, mainCamera->getCenter().y));
	confiner->SetPositionLeft(Vector2(0, 0));
}

CharacterInputHandler* Level::GetCharacterInputHandler()
{
	return playerCharacter->GetInputHandler();
}

void Level::SetCamera(sf::View* mainCamera, Vector2 windowSize)
{
	this->mainCamera = mainCamera;
	this->windowSize = windowSize;

	float playerPositionX = playerCharacter->physicalZenObject2D->zenShape->GetPosition().x;

	if (gameStateId == 3)
	{
		if (playerPositionX > windowSize.x / 2 && playerPositionX > mainCamera->getCenter().x && playerPositionX < jsonData["width"]*TILE_SIZE - windowSize.x / 2)
		{
			mainCamera->setCenter(sf::Vector2f(playerPositionX, mainCamera->getCenter().y));
			confiner->SetPositionLeft(Vector2(playerPositionX - windowSize.x / 2, 0));
		}
	}
	else
	{
		mainCamera->setCenter(windowSize.x / 2.f, windowSize.y / 2.f);
	}
}

void Level::SetUIScene(UIScene* uiScene)
{
	this->uiScene = uiScene;
}

void Level::SetRendering(RenderingStack* renderStack, Renderer* renderModule)
{
	this->renderStack = renderStack;
	this->renderModule = renderModule;
}

void Level::LoadMap(std::string textureFilePath, std::string levelJsonPath, int playerPositionId)
{
	
	if (isFirstMap == false)
	{
		if (hasKey && uiScene->GetKeyPanel()->allKeyCollected == false && canCheckKays)
		{
			playerCharacter->physicalZenObject2D->zenShape->SetPosition(sf::Vector2f(playerPositions[0]->x * TILE_SCALE, playerPositions[0]->y * TILE_SCALE));
			mainCamera->setCenter(sf::Vector2f(windowSize.x / 2, mainCamera->getCenter().y));
			confiner->SetPositionLeft(Vector2(0, 0));

			return;
		}

		audioSystem->PlaySingleShot("stageclear");

		if(canCheckKays && hasKey)
		uiScene->GetKeyPanel()->Clear();
	}

	renderStack->Clear();

	std::ifstream jsonFileStream(levelJsonPath);
	jsonData = nlohmann::json::parse(jsonFileStream);

	nlohmann::json tileMapData = jsonData["data"];

	EnvironmentClear();
	currentMap->TextureInitialization(textureFilePath);
	currentMap->LoadMap(jsonData["height"], jsonData["width"], tileMapData);
	currentMap->Draw(renderStack);
	EnvironmentInitialize();

	playerCharacter->physicalZenObject2D->zenShape->SetPosition(sf::Vector2f(playerPositions[playerPositionId]->x*TILE_SCALE, playerPositions[playerPositionId]->y * TILE_SCALE));

	if (mainCamera != nullptr && confiner != nullptr)
	{
		mainCamera->setCenter(sf::Vector2f(windowSize.x / 2, mainCamera->getCenter().y));
	}

	Draw(renderStack);

	renderStack->DivisionOfObjectsIntoLayersByLayerId();
	renderModule->SortRenderLayers(renderStack);

	isFirstMap = false;
	isMapLoaded = true;
}

bool Level::IsWorldLoaded()
{
	return isMapLoaded;
}

void Level::AddCoin(sf::Vector2f position)
{
	coins.push_back(new Coin(coins.size(), "NewCoin", COIN_GRAPHIC_PATH, position, uiScene->GetCoinCounter()));
	coins[coins.size() - 1]->DrawOverQuestionMark(renderStack);
}
