// Copyright Z.Z. Zengine (c)

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
        assetsManager.Textures[std::stoi(name)] = textureAsset;
	}

    file.close();
}

void Map::LoadMap(int rows, int columns, nlohmann::json tileMapData)
{
    MemoryReleaseForLoadMap();

    this->rows = rows;
    this->columns = columns;

    CreatingTwoDimensionalDynamicArray();

    LoadingTextureNumberIntoDynamicArray(tileMapData);

    CreatingDynamicTileMap();
}

void Map::MemoryReleaseForLoadMap()
{
    for (int i = 0; i < rows; i++)
    {
        delete[] textureNumberTab[i];
        delete[] tileMap[i];
    }
    delete[] textureNumberTab;
    delete[] tileMap;
}

void Map::CreatingTwoDimensionalDynamicArray()
{
    textureNumberTab = new int * [rows];
    for (int i = 0; i < rows; i++)
    {
        textureNumberTab[i] = new int[columns];
    }
}

void Map::LoadingTextureNumberIntoDynamicArray(nlohmann::json tileMapData)
{
    size_t idxTileMapData = 0;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            textureNumberTab[i][j] = tileMapData[idxTileMapData];
            idxTileMapData++;
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
            TextureAsset* textureAsset = assetsManager.GetTextureAsset(textureNumberTab[i][j]);
            sf::Texture *texture = textureAsset->GetTexture();

            tileMap[i][j].setTexture(texture);
            tileMap[i][j].setSize(sf::Vector2f(32.0f, 32.0f));
            tileMap[i][j].setPosition(j * 32.f, i * 32.f);
            
            tileMapRenderObject = new RenderObject(&tileMap[i][j], 0, 0);
            renderStack->renderQueue.push_back(tileMapRenderObject);
        }
    }
}

