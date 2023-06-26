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
	void DrawPlayer(sf::RenderWindow& windowIn);
	Character* GetPlayer();

private:
	Map *_map;
	Character* playerCharacter;
	sf::RectangleShape player;
};

