#include "Map.h"
#include "TextureAsset.h"
#include "AssetsManager.h"
#include <iostream>
#include <fstream>
#include "../Renderer/Renderer.h"

using namespace std;

AssetsManager assetsManager;

void Map::TextureInitialization(string pathToTexturesTxt)
{
	ifstream file;
	file.open(pathToTexturesTxt);
	string path, name;

	while (!file.eof())
	{
		file >> path >> name;

        TextureAsset* textureAsset = new TextureAsset(path, name);
        assetsManager.Textures[name] = textureAsset;
	}

    file.close();
}

void Map::LoadMap(string pathToTileTxt)
{
    MemoryReleaseForLoadMap();

    ifstream file;
    file.open(pathToTileTxt);
    file >> dimension1;
    file >> dimension2;

    CreatingTwoDimensionalDynamicArray();

    LoadingTextureNumberIntoDynamicArray(&file);

    CreatingDynamicTileMap();

    file.close();
}

void Map::MemoryReleaseForLoadMap()
{
    for (int i = 0; i < dimension1; i++)
    {
        delete[] tab[i];
        delete[] tileMap[i];
    }
    delete[] tab;
    delete[] tileMap;
}

void Map::CreatingTwoDimensionalDynamicArray()
{
    tab = new string * [dimension1];
    for (int i = 0; i < dimension1; i++)
    {
        tab[i] = new string[dimension2];
    }
}

void Map::LoadingTextureNumberIntoDynamicArray(ifstream* file)
{
    for (int i = 0; i < dimension1; i++)
    {
        for (int j = 0; j < dimension2; j++)
        {
            *file >> tab[i][j];
        }
    }
}

void Map::CreatingDynamicTileMap()
{
    tileMap = new sf::RectangleShape * [dimension1];
    for (int i = 0; i < dimension1; i++)
    {
        tileMap[i] = new sf::RectangleShape[dimension2];
    }
}

void Map::AddMapToRenderStack(RenderingStack* renderStack)
{
    for (int i = 0; i < dimension1; i++)
    {
        for (int j = 0; j < dimension2; j++)
        {
            TextureAsset* textureAsset = assetsManager.GetTextureAsset(tab[i][j]);
            sf::Texture *texture = textureAsset->GetTexture();

            tileMap[i][j].setTexture(texture);
            tileMap[i][j].setSize(sf::Vector2f(32.0f, 32.0f));
            tileMap[i][j].setPosition(j * 32.f, i * 32.f);
            
            tileMapRenderObject = new RenderObject();
            tileMapRenderObject->drawable = &tileMap[i][j];
            tileMapRenderObject->zOrder = 0;
            tileMapRenderObject->layerId = 0;

            renderStack->renderQueue.push_back(tileMapRenderObject);
        }
    }
}

