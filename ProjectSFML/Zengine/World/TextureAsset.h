#pragma once

#include <SFML/Graphics.hpp>

class TextureAsset
{
public:
	TextureAsset() {};
	TextureAsset(std::string Path, std::string Name);

	sf::Texture* GetTexture();

	sf::Texture TextureSFML;

private:
	std::string TextureName;
	std::string TexturePath;
};

