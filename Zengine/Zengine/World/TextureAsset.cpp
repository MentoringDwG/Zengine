// Copyright Z.Z. Zengine (c)

#include "TextureAsset.h"

TextureAsset::TextureAsset(std::string Path, std::string Name) :TexturePath(Path), TextureName(Name)
{
	TextureSFML.loadFromFile(TexturePath);
}

sf::Texture* TextureAsset::GetTexture()
{
	return &TextureSFML;
}
