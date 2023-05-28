#include "AssetsManager.h"
#include "TextureAsset.h"

AssetsManager* AssetsManager::Assets = nullptr;

TextureAsset* AssetsManager::GetTextureAsset(string Name)
{
	return Textures[Name];
}

