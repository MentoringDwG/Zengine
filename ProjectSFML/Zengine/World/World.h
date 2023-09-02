#pragma once

#include "../Character/Character.h"
#include "../ZenObject/ZenObject.h"
#include "../Physics2D/PhysicalZenObject2D.h"
#include "../Environment/Coin.h"
#include "../Environment/CoinCounter.h"
#include "Enemy.h"
#include <sstream>
#include "../UIinGame/HeartsPanel.h"

class Renderer;

class World
{
public:
	void Initialize(string PlayerName, string PlayerTexcurePath, float PlayerMoveSpeed);
	void MapInitialize(string pathToTexturesTxt, string pathToTileTxt);
	void PhysicalZenObject2DInitialize(string enemySpritePath);
	void EnvironmentInitialize(string CoinPath, sf::Vector2f position1, sf::Vector2f position2);
	void Draw(RenderingStack* renderStack);
	void ApplyForceToPhysicsObject();
	void UpdateObjects();
	Character* GetPlayer();
	CoinCounter* coinCounter;

private:
	class Map *map;
	Character* playerCharacter;
	Enemy* enemy;
	class Ground* ground;
	std::vector<Coin*> coins;
	HeartsPanel* heartPanel;
};

