#pragma once
#include <iostream>
#include "Map.h"
#include "../ZenObject/ZenObject.h"
#include "../Character/Character.h"

using namespace std;

class World
{
	public:
		void Initialize(string PlayerName);
		void MapInitialize(string pathToTexturesTxt, string pathToTileTxt);
		void DrawMap(sf::RenderWindow& windowIn);
		Character* GetPlayer();


	private:
		Map *_map;
		Character* playerCharacter;
};

