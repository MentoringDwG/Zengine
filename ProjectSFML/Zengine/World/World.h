#pragma once
#include "Map.h"
#include "../ZenObject/ZenObject.h"
#include "../Character/Character.h"

class Renderer;

class World
{
public:
	void Initialize(string PlayerName, string PlayerTexcurePath, float PlayerMoveSpeed);
	void MapInitialize(string pathToTexturesTxt, string pathToTileTxt);
	void Draw(RenderingStack* renderStack);
	Character* GetPlayer();

private:
	Map *map;
	Character* playerCharacter;
	sf::RectangleShape player;
};

