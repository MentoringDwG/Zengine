#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std; 

class World
{
	public:
		void TextureInitialization(string pathToTexturesTxt);
		void LoadWorld(string pathToTileTxt, sf::RenderWindow &windowIn);
};

