#include "AssetsManager.h"
#include "TextureAsset.h"

AssetsManager* AssetsManager::assets = nullptr;

TextureAsset* AssetsManager::GetTextureAsset(int Name)
{
	return Textures[Name];
}

