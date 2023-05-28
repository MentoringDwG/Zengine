#include "Zengine.h"
#include <SFML/Graphics.hpp>
#include "TextureAsset.h"
#include "AssetsManager.h"

Zengine* Zengine::Engine = nullptr;
AssetsManager assetsManager;

Zengine* Zengine::CreateInstance()
{
	Engine = new Zengine();
	return Engine;
}

void Zengine::Run()
{
	// Inicjalizacja silnika
	engineRunning = true;

    TextureAsset texturAsset("Graphics/Map/1.png", "1");
    assetsManager.Textures["1"] = &texturAsset;
    

	MainLoop();
}

void Zengine::MainLoop()
{
	// Kazda klatka bedzie obslugiwana w tym miejscu

	//ProcessInput();
	//ProcessGameLogic();
	//Render();

    sf::RenderWindow window(sf::VideoMode(100, 100), "SFML works!");
    sf::Sprite firstSprite;
    firstSprite.setTexture(assetsManager.GetTextureAsset("1")->TextureSFML);
    firstSprite.setPosition(0, 0);

    while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();
            window.draw(firstSprite);
            window.display();
        }
}

void Zengine::Shutdown()
{
}