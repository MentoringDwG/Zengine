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
    //Memory release
    for (int i = 0; i < dimension1; i++)
    {
        delete [] tab[i];
    }
    delete [] tab;

    ifstream file;
    file.open(pathToTileTxt);

    //Downloading dimensions from a file and creating a two-dimensional dynamic array
    file >> dimension1;
    file >> dimension2;

    tab = new string * [dimension1];
    for (int i = 0; i < dimension1; i++)
    {
        tab[i] = new string[dimension2];
    }

    //Loading the texture number needed for the tilemap into a two-dimensional dynamic array
    for (int i = 0; i < dimension1; i++)
    {
        for (int j = 0; j < dimension2; j++)
        {
            file >>tab[i][j];
        }
    }

    //Creating a dynamic tile map
    tileMap = new sf::RectangleShape * [dimension1];
    for (int i = 0; i < dimension1; i++)
    {
        tileMap[i] = new sf::RectangleShape[dimension2];
    }

    file.close();
}

void Map::DrawMap(RenderingStack* renderStack)
{
    //Filling and drawing a dynamic tilemap

    for (int i = 0; i < dimension1; i++)
    {
        for (int j = 0; j < dimension2; j++)
        {
            const sf::Texture texcure = assetsManager.GetTextureAsset(tab[i][j]).TextureSFML;
            tileMap[i][j].setSize(sf::Vector2f(32.0f, 32.0f));
            tileMap[i][j].setTexture(&texcure);
            tileMap[i][j].setPosition(j * 32.f, i * 32.f);
            
            tileMapRenderObject = new RenderObject();
            tileMapRenderObject->drawable = &tileMap[i][j];
            tileMapRenderObject->zOrder = 0;
            tileMapRenderObject->layerId = 0;

            renderStack->renderQueue.push_back(tileMapRenderObject);
            //windowIn.draw(tileMap[i][j]);
        }
    }
}

