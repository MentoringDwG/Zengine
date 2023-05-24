#pragma once

#include<iostream>
#include <SFML/Graphics.hpp>
#include <map>

using namespace std; 

class TextureAsset
{
	string TexturePath;
	string TextureName;

	TextureAsset(string Path, string Name) :TexturePath(Path), TextureName(Name)
	{
		TextureSFML.loadFromFile(TexturePath);
	}

public:
	void TextureInitialize();
	sf::Texture TextureSFML;
	TextureAsset()
	{

	}
};

