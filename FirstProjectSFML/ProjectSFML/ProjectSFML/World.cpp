#include "World.h"
#include "TextureAsset.h"
#include "AssetsManager.h"
#include <iostream>
#include <fstream>

using namespace std;

AssetsManager assetsManager;

string Tab[17][30];
sf::RectangleShape tileMap[17][30];

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
    ifstream file;
    file.open("Tiles/TxtFiles/Level1.txt");

    for (int i = 0; i < 17; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            file >> Tab[i][j];
            cout << Tab[i][j] << " ";
        }
        cout << endl;
    }

    file.close();
}

void World::LoadWorld()
{
    World::TextureInitialization();
    World::TileMapInitialization();

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

        for (int i = 0; i < 17; i++)
        {
            for (int j = 0; j < 30; j++)
            {
                const sf::Texture texcure = assetsManager.GetTextureAsset(Tab[i][j]).TextureSFML;
                tileMap[i][j].setSize(sf::Vector2f(32.0f, 32.0f));
                tileMap[i][j].setTexture(&texcure);
                tileMap[i][j].setPosition(j * 32.f, i * 32.f);
                window.draw(tileMap[i][j]);
            }
        }

        //Draw UI
        window.setView(window.getDefaultView()); 


        window.display();
    }
}
