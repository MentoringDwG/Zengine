#pragma once

#include "../Physics2D/PhysicalZenObject2D.h"
#include <sstream>

class World
{
public:
	~World();

	void Initialize(string PlayerName, string PlayerTexcurePath, float PlayerMoveSpeed);
	void MapInitialize(string pathToTexturesTxt, string pathToTileTxt);
	void PhysicalZenObject2DInitialize(string enemySpritePath);
	void EnvironmentInitialize(string CoinPath, sf::Vector2f position1, sf::Vector2f position2);
	void Draw(RenderingStack* renderStack);
	void ApplyForceToPhysicsObject();
	void UpdateObjects();

	class Character* GetPlayer();

	class CoinCounter* coinCounter = nullptr;

private:
	class Map *map = nullptr;
	class Character* playerCharacter = nullptr;
	class Enemy* enemy = nullptr;
	class Ground* ground = nullptr;
	std::vector<class Coin*> coins;
	class HeartsPanel* heartPanel = nullptr;
	class Castle* castle = nullptr;
};
