#include "AssetsManager.h"
#include "TextureAsset.h"

TextureAsset* AssetsManager::GetTextureAsset(string Name)
{
	AssetsManager assetManager;
	cout << "Texture manager: " << assetManager.Textures["1"];
	return assetManager.Textures[Name];
}