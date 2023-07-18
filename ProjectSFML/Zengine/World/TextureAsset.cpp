#include "TextureAsset.h"
#include <iostream>
#include "AssetsManager.h"

using namespace std;

sf::Texture* TextureAsset::GetTexture()
{
	return &TextureSFML;
}

void TextureAsset::SetPath(string Path)
{
	TexturePath = Path;
	TextureSFML.loadFromFile(TexturePath);
}