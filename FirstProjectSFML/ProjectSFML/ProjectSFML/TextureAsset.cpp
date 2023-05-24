#include "TextureAsset.h"
#include <iostream>
#include "AssetsManager.h"

using namespace std;
AssetsManager assetManager;

void TextureAsset::TextureInitialize()
{
	TextureAsset Ground("Graphics/Map/1.png", "1");
	assetManager.Textures[Ground.TextureName]=&Ground; 

	cout << "Texcure asset: " << assetManager.Textures["1"] << endl;
}


