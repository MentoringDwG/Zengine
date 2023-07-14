#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Renderer/Renderer.h"

using namespace std; 

class Map
{
public:
	void TextureInitialization(string pathToTexturesTxt);
	void LoadMap(string pathToTileTxt);
	void Draw(RenderingStack* renderStack);

private:
	string** tab;
	sf::RectangleShape** tileMap;
	int rows, columns;
	RenderObject* tileMapRenderObject = nullptr;

	void MemoryReleaseForLoadMap();
	void CreatingTwoDimensionalDynamicArray();
	void LoadingTextureNumberIntoDynamicArray(ifstream *file);
	void CreatingDynamicTileMap();
};

