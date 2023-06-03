#include "World.h"
#include "TextureAsset.h"
#include "AssetsManager.h"
#include <iostream>
#include <fstream>

using namespace std;

AssetsManager assetsManager;

string Tab[17][30];

void World::TextureInitialization()
{
	ifstream file;
	file.open("Textures/TexturesLevel1.txt");
	string path, name;


	while (!file.eof())
	{
		file >> path >> name;

        TextureAsset* textureAsset = new TextureAsset(path, name);
        assetsManager.Textures[name] = textureAsset;
	}

    file.close();
}

void World::TileMapInitialization()
{
    cout << "xd" << endl;
    ifstream file;
    file.open("Tiles/TxtFiles/Level1.txt");

    for (int i = 0; i < 17; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            file >> Tab[i][j];
        }
    }

    file.close();
}

void World::LoadWorld()
{
    World::TextureInitialization();
    World::TileMapInitialization();

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
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
        firstSprite.setTexture(assetsManager.GetTextureAsset(Tab[1][0])->TextureSFML);
        firstSprite.setPosition(x, y);
        window.draw(firstSprite);
        int i = 0;

        window.display();
    }
}
