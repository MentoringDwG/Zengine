#pragma once

#include "Map.h"
#include "../ZenObject/ZenObject.h"
#include "../Character/Character.h"
#include "../Physics2D/ZenPhysics2D.h"
#include "../Physics2D/PhysicalZenObject2D.h"
#include "../Environment/Coin.h"
#include "../ZenObject/ZenText.h"
#include "../Environment/CoinCounter.h"
#include <sstream>

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
	Character* GetPlayer();
	CoinCounter* coinCounter;

private:
	Map *map;
	Character* playerCharacter;
	PhysicalZenObject2D* enemy;
	Coin* coin1;
	Coin* coin2;
};

