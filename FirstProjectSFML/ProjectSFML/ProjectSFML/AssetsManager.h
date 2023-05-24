#pragma once

#include <iostream>
#include<map>
#include "TextureAsset.h"

using namespace std;

class AssetsManager
{
public:
	std::map<string, TextureAsset*> Textures;

	TextureAsset* GetTextureAsset(string Name);
};

