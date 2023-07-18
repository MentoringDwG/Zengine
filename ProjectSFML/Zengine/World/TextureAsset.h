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
	
	sf::Texture* GetTexture();
	void SetPath(string Path);

private:
	string TextureName;
	string TexturePath;
};

