#pragma once

#include <vector>
#include <Zengine/World/World.h>
#include <Zengine/Renderer/Renderer.h>
#include <Zengine/Structs/Vector2.h>
#include "../../../nlohmann/json.hpp"

class Level1: public World
{
public:
	Level1(std::string levelJsonPath);
	~Level1();

	virtual void Initialize(StateMachine* stateMachine) override;
	virtual void MapInitialize() override;
	virtual void PhysicalZenObject2DInitialize() override;
	virtual void EnvironmentInitialize() override;
	virtual void ApplyForceToPhysicsObject() override;
	virtual void UpdateObjects() override;
	virtual class CharacterInputHandler* GetCharacterInputHandler() override;
	virtual void SetCamera(sf::View* mainCamera, struct Vector2 windowSize) override;

	void Draw(RenderingStack* renderStack);
	class CoinCounter* coinCounter = nullptr;

private:
	void PlayerRespawn();

	nlohmann::json jsonData;
	class StateMachine* stateMachine = nullptr;
	class Map* map = nullptr;
	class Character* playerCharacter = nullptr;
	std::vector<class Enemy*> enemys;
	class Ground* ground = nullptr;
	std::vector<class Coin*> coins;
	class HeartsPanel* heartPanel = nullptr;
	class Castle* castle = nullptr;
	class Confiner* confiner = nullptr;
	sf::View* mainCamera = nullptr;

	//graphics
	const std::string COIN_GRAPHIC_PATH = "Graphics/coin.png";
	const std::string ENEMY_GRAPHIC_PATH = "Graphics/Enemy1.png";

	//json
	const float TILE_SCALE = 2;
	const std::string COINS = "Coins";
	const std::string ENEMYS = "Enemys";

	//camera
	const int TILE_SIZE = 32;
	struct Vector2 windowSize = Vector2(0, 0);
};

