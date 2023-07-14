#pragma once

#include "Map.h"
#include "../ZenObject/ZenObject.h"
#include "../Character/Character.h"
#include "../Physics2D/ZenPhysics2D.h"
#include "../Physics2D/PhysicalZenObject2D.h"

class Renderer;

class World
{
public:
	void Initialize(string PlayerName, string PlayerTexcurePath, float PlayerMoveSpeed);
	void MapInitialize(string pathToTexturesTxt, string pathToTileTxt);
	void PhysicalZenObject2DInitialize(ZenPhysics2D *zenPhysics2D, string enemySpritePath);
	void Draw(RenderingStack* renderStack, ZenPhysics2D* zenPhysics2D);
	void ApplyForceToPhysicsObject();
	Character* GetPlayer();

private:
	Map *map;
	Character* playerCharacter;
	PhysicalZenObject2D* enemy;
};

