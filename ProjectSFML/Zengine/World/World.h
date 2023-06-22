#pragma once
#include <iostream>;
#include "Map.h"
#include "../ZenObject/ZenObject.h"

using namespace std;

class World
{
	public:
		void Initialize();
		void MapInitialize(string pathToTexturesTxt, string pathToTileTxt);
		void DrawMap(sf::RenderWindow& windowIn);

	private:
		Map *_map;

};

