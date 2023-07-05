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
    file >> rows;
    file >> columns;

    CreatingTwoDimensionalDynamicArray();

    LoadingTextureNumberIntoDynamicArray(&file);

    CreatingDynamicTileMap();

    file.close();
}

void Map::MemoryReleaseForLoadMap()
{
    for (int i = 0; i < rows; i++)
    {
        delete[] tab[i];
        delete[] tileMap[i];
    }
    delete[] tab;
    delete[] tileMap;
}

void Map::CreatingTwoDimensionalDynamicArray()
{
    tab = new string * [rows];
    for (int i = 0; i < rows; i++)
    {
        tab[i] = new string[columns];
    }
}

void Map::LoadingTextureNumberIntoDynamicArray(ifstream* file)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            *file >> tab[i][j];
        }
    }
}

void Map::CreatingDynamicTileMap()
{
    tileMap = new sf::RectangleShape * [rows];
    for (int i = 0; i < rows; i++)
    {
        tileMap[i] = new sf::RectangleShape[columns];
    }
}

void Map::Draw(RenderingStack* renderStack)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
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

