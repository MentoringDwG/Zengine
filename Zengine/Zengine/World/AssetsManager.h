// Copyright Z.Z. Zengine (c)

#pragma once

#include <iostream>
#include<map>

using namespace std;
class TextureAsset;

class AssetsManager
{
public:
	std::map<int, TextureAsset*> Textures;
	TextureAsset* GetTextureAsset(int Name);

private:
	static class AssetsManager* assets;
};

