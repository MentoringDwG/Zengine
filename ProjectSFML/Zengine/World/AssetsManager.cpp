#include "AssetsManager.h"
#include "TextureAsset.h"

AssetsManager* AssetsManager::assets = nullptr;

TextureAsset AssetsManager::GetTextureAsset(string Name)
{
	return *Textures[Name];
}

