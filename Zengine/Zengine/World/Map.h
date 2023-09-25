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

	string** textureNumberTab = nullptr;
	sf::RectangleShape** tileMap = nullptr;
	int rows = 0, columns = 0;
	RenderObject* tileMapRenderObject = nullptr;
};

