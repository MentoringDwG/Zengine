#pragma once

#include <vector>
#include <map>
#include <Zengine/World/World.h>
#include <Zengine/Renderer/Renderer.h>
#include <Zengine/Structs/Vector2.h>
#include "../../../nlohmann/json.hpp"
#include "MapManager.h"

class Level: public World
{
public:
	Level(std::string levelJsonPath);
	~Level();

	virtual void Initialize(class AudioSystem* audioSystem) override;
	virtual void MapInitialize() override;
	virtual void EnvironmentClear() override;
	virtual void EnvironmentInitialize() override;
	virtual void ApplyForceToPhysicsObject() override;
	virtual void UpdateObjects() override;
	virtual class CharacterInputHandler* GetCharacterInputHandler() override;
	virtual void SetCamera(sf::View* mainCamera, struct Vector2 windowSize) override;
	virtual void Draw(RenderingStack* renderStack) override;
	virtual void SetRendering(RenderingStack* renderStack, Renderer* renderModule) override;
	virtual void LoadMap(std::string textureFilePath, std::string levelJsonPath, int playerPositionId) override;
	virtual bool IsWorldLoaded() override;

	void SetPlayer(class Character* playerCharacter);
	void SetUIScene(class UIScene* uiScene);
	void PlayerRespawn();

	int gameStateId = 0;
	bool canCheckKays = true;

private:
	nlohmann::json jsonData;
	class AudioSystem* audioSystem = nullptr;
	class Map* currentMap = nullptr;
	class Character* playerCharacter = nullptr;
	std::vector<class Enemy*> enemys;
	class Ground* ground = nullptr;
	std::vector<class Coin*> coins;
	std::vector<class MapLoader*> mapLoaders;
	std::vector<class Key*> keys;
	std::vector<class QuestionMark*> questionMarks;
	std::map<int, struct Vector2*> playerPositions;
	class Castle* castle = nullptr;
	class Confiner* confiner = nullptr;
	sf::View* mainCamera = nullptr;
	class UIScene* uiScene = nullptr;
	RenderingStack* renderStack = nullptr;
	Renderer* renderModule = nullptr;

	bool isFirstMap = true;
	bool hasKey = false;

	//graphics
	const std::string COIN_GRAPHIC_PATH = "Graphics/coin.png";
	const std::string ENEMY_GRAPHIC_PATH = "Graphics/Enemy1.png";
	const std::string KEY_GRAPHIC_PATH = "Graphics/Key/key1.png";
	const std::string QUESTION_MARK_GRAPHIC_PATH = "Graphics/Map/67.png";

	//json
	const float TILE_SCALE = 2;
	const std::string COINS = "Coins";
	const std::string ENEMYS = "Enemys";
	const std::string MAP_LOADER = "MapLoader";
	const std::string PLAYER_POSITIONS = "PlayerPositions";
	const std::string KEYS = "Keys";
	const std::string QUESTION_MARKS = "QuestionMark";

	//camera
	const int TILE_SIZE = 32;
	struct Vector2 windowSize = Vector2(0, 0);

	bool isMapLoaded = false;
};

