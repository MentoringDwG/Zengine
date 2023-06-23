#pragma once

#include<iostream>
#include <SFML/Graphics.hpp>

using namespace std; 

class TextureAsset
{
public:
	sf::Texture TextureSFML;
	TextureAsset()
	{

	}

	TextureAsset(string Path, string Name) :TexturePath(Path), TextureName(Name)
	{
		TextureSFML.loadFromFile(TexturePath);
	}
	
private:
	string TextureName;
	string TexturePath;
};

