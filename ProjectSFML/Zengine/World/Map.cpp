#include "Map.h"
#include "TextureAsset.h"
#include "AssetsManager.h"
#include <iostream>
#include <fstream>

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
        delete [] Map::Tab[i];
    }
    delete [] Map::Tab;


    ifstream file;
    file.open(pathToTileTxt);

    //Downloading dimensions from a file and creating a two-dimensional dynamic array
    file >> dimension1;
    file >> dimension2;

    Map::Tab = new string * [dimension1];
    for (int i = 0; i < dimension1; i++)
    {
        Map::Tab[i] = new string[dimension2];
    }

    //Loading the texture number needed for the tilemap into a two-dimensional dynamic array
    for (int i = 0; i < dimension1; i++)
    {
        for (int j = 0; j < dimension2; j++)
        {
            file >> Map::Tab[i][j];
        }
    }

    //Creating a dynamic tile map
    Map::tileMap = new sf::RectangleShape * [dimension1];
    for (int i = 0; i < dimension1; i++)
    {
        Map::tileMap[i] = new sf::RectangleShape[dimension2];
    }

    file.close();
}

void Map::DrawMap(sf::RenderWindow& windowIn)
{
    //Filling and drawing a dynamic tilemap

    for (int i = 0; i < dimension1; i++)
    {
        for (int j = 0; j < dimension2; j++)
        {
            const sf::Texture texcure = assetsManager.GetTextureAsset(Map::Tab[i][j]).TextureSFML;
            Map::tileMap[i][j].setSize(sf::Vector2f(32.0f, 32.0f));
            Map::tileMap[i][j].setTexture(&texcure);
            Map::tileMap[i][j].setPosition(j * 32.f, i * 32.f);
            windowIn.draw(Map::tileMap[i][j]);
        }
    }
}

