#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std; 

class World
{
	public:
	
		void LoadWorld(string pathToTexturesTxt, string pathToTileTxt);

	private:
		void TextureInitialization(string pathToTexturesTxt);
		void TileMapInitialization(string pathToTileTxt, sf::RenderWindow &windowIn);
};

