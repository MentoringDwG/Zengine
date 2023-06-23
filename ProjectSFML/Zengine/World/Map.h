#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std; 

class Map
{
public:
	void TextureInitialization(string pathToTexturesTxt);
	void LoadMap(string pathToTileTxt);
	void DrawMap(sf::RenderWindow& windowIn);

private:
	string** Tab;
	sf::RectangleShape** tileMap;
	int dimension1, dimension2;
};

