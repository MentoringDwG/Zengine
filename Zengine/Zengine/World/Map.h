// Copyright Z.Z. Zengine (c)

#pragma once

#include <SFML/Graphics.hpp>
#include "../Renderer/Renderer.h"
#include "../../../nlohmann/json.hpp"

using namespace std; 

class Map
{
public:
	void TextureInitialization(string pathToTexturesTxt);
	void LoadMap(int rows, int columns, nlohmann::json tileMapData);
	void Draw(RenderingStack* renderStack);

private:
	void MemoryReleaseForLoadMap();
	void CreatingTwoDimensionalDynamicArray();
	void LoadingTextureNumberIntoDynamicArray(nlohmann::json tileMapData);
	void CreatingDynamicTileMap();

	int** textureNumberTab = nullptr;
	sf::RectangleShape** tileMap = nullptr;
	int rows = 0;
	int columns = 0;
	RenderObject* tileMapRenderObject = nullptr;
};

