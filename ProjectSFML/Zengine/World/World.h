#pragma once
#include "Map.h"
#include "../ZenObject/ZenObject.h"
#include "../Character/Character.h"

class World
{
public:
	void Initialize(string PlayerName, string PlayerTexcurePath);
	void MapInitialize(string pathToTexturesTxt, string pathToTileTxt);
	void DrawMap(sf::RenderWindow& windowIn);
	Character* GetPlayer();

private:
	Map *map;
	Character* playerCharacter;
};

