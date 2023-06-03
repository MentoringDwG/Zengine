#include "World.h"
#include "TextureAsset.h"
#include "AssetsManager.h"
#include <iostream>
#include <fstream>

using namespace std;

AssetsManager assetsManager;

void World::TextureInitialization(string pathToTexturesTxt)
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

void World::TileMapInitialization(string pathToTileTxt, sf::RenderWindow &windowIn)
{
    ifstream file;
    file.open(pathToTileTxt);

    //Downloading dimensions from a file and creating a two-dimensional dynamic array
    int dimension1, dimension2;
    file >> dimension1;
    file >> dimension2;

    string** Tab = new string * [dimension1];
    for (int i = 0; i < dimension1; i++)
    {
        Tab[i] = new string[dimension2];
    }

    //Loading the texture number needed for the tilemap into a two-dimensional dynamic array
    for (int i = 0; i < dimension1; i++)
    {
        for (int j = 0; j < dimension2; j++)
        {
            file >> Tab[i][j];
        }
    }

    //Creating a dynamic tile map
    sf::RectangleShape **tileMap = new sf::RectangleShape * [dimension1];
    for (int i = 0; i < dimension1; i++)
    {
        tileMap[i] = new sf::RectangleShape[dimension2];
    }

    //Filling and drawing a dynamic tilemap
    for (int i = 0; i < dimension1; i++)
    {
        for (int j = 0; j < dimension2; j++)
        {
            const sf::Texture texcure = assetsManager.GetTextureAsset(Tab[i][j]).TextureSFML;
            tileMap[i][j].setSize(sf::Vector2f(32.0f, 32.0f));
            tileMap[i][j].setTexture(&texcure);
            tileMap[i][j].setPosition(j * 32.f, i * 32.f);
            windowIn.draw(tileMap[i][j]);
        }
    }

    file.close();
}

void World::LoadWorld(string pathToTexturesTxt, string pathToTileTxt)
{
    World::TextureInitialization(pathToTexturesTxt);

    sf::RenderWindow window(sf::VideoMode(960,544), "SFML works!");

    sf::View mainView;
    mainView.setSize(960,544); 
    mainView.setCenter(window.getSize().x / 2.f, window.getSize().y / 2.f);

    sf::Sprite firstSprite;
    int x = 0, y = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        //Render game elements
        window.setView(mainView);

        World::TileMapInitialization(pathToTileTxt, window);

        //Draw UI
        window.setView(window.getDefaultView()); 


        window.display();
    }
}
