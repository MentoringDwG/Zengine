#include "Zengine.h"
#include <SFML/Graphics.hpp>

Zengine* Zengine::Engine = nullptr;

Zengine* Zengine::CreateInstance()
{
	Engine = new Zengine();
	return Engine;
}

void Zengine::Run()
{
	// Inicjalizacja silnika
	engineRunning = true;
	MainLoop();
}

void Zengine::MainLoop()
{
	// Kazda klatka bedzie obslugiwana w tym miejscu
	//ProcessInput();
	//ProcessGameLogic();
	//Render();

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
    sf::Texture image;
    image.loadFromFile("Graphics/World.png");
    sf::Sprite firstSprite;
    firstSprite.setTexture(image);
    firstSprite.setPosition(0, 0);
    //sf::CircleShape shape(100.f);
    //shape.setFillColor(sf::Color::Green);

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