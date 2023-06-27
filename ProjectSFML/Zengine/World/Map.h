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
	void DrawMap(RenderingStack* renderStack);

private:
	string** tab;
	sf::RectangleShape** tileMap;
	int dimension1, dimension2;
	RenderObject* tileMapRenderObject = nullptr;
	sf::Texture* texture = nullptr;
};

