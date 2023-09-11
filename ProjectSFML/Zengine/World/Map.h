#pragma once

#include <SFML/Graphics.hpp>
#include "../Renderer/Renderer.h"

using namespace std; 

class Map
{
public:
	void TextureInitialization(string pathToTexturesTxt);
	void LoadMap(string pathToTileTxt);
	void Draw(RenderingStack* renderStack);

private:
	void MemoryReleaseForLoadMap();
	void CreatingTwoDimensionalDynamicArray();
	void LoadingTextureNumberIntoDynamicArray(ifstream *file);
	void CreatingDynamicTileMap();

	string** tab;
	sf::RectangleShape** tileMap;
	int rows = 0, columns = 0;
	RenderObject* tileMapRenderObject = nullptr;
};

