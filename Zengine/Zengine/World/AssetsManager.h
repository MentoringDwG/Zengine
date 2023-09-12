#pragma once

#include <iostream>
#include<map>

using namespace std;
class TextureAsset;

class AssetsManager
{
public:
	std::map<string, TextureAsset*> Textures;
	TextureAsset* GetTextureAsset(string Name);

private:
	static class AssetsManager* assets;
};

