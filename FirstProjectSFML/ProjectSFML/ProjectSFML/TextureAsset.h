#pragma once

#include<iostream>
#include <SFML/Graphics.hpp>

using namespace std; 

class TextureAsset
{


public:
	sf::Texture TextureSFML;
	string TexturePath;
	string TextureName;
	TextureAsset()
	{

	}

	TextureAsset(string Path, string Name) :TexturePath(Path), TextureName(Name)
	{
		TextureSFML.loadFromFile(TexturePath);
	}
};

