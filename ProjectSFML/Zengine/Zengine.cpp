#include "Zengine.h"
#include <SFML/Graphics.hpp>
#include "World/World.h"
#include "InputModule/InputProcessorModule.h"
#include "InputModule/CharacterInputHandler.h"

Zengine* Zengine::Engine = nullptr;

World world;

Zengine* Zengine::CreateInstance()
{
	Engine = new Zengine();
	return Engine;
}

void Zengine::Run()
{
	// Inicjalizacja silnika
	engineRunning = true;

	InputProcessor = new InputProcessorModule();

	window = new sf::RenderWindow(sf::VideoMode(960, 544), "Zengine");

	world.Initialize("Mario", "Graphics/Mario.png");

	MainLoop();
}

void Zengine::ViewInitialize()
{
	Zengine::mainView.setSize(960, 544);
	Zengine::mainView.setCenter(window->getSize().x / 2.f, window->getSize().y / 2.f);

	Zengine::playerView.setSize(960, 544);
	Zengine::playerView.setCenter(window->getSize().x / 2.f, window->getSize().y / 2.f);
}


void Zengine::MainLoop()
{
	CharacterInputHandler inputHandler = world.GetPlayer()->GetInputHandler();
	InputProcessor->RegisterInputHandler(reinterpret_cast<InputHandler*>(&inputHandler));

	world.MapInitialize("Textures/TexturesLevel1.txt", "Tiles/TxtFiles/Level1.txt");
	ViewInitialize();

	while (window->isOpen())
	{
		ProcessInput(window);
		window->clear();

		//Render game elements
		window->setView(mainView);

		world.DrawMap(*window);

		//render player 
		window->setView(playerView);

		//Draw UI
		window->setView(window->getDefaultView());

		window->display();

	}

	//ProcessGameLogic();
	//Render();
}

void Zengine::ProcessInput(sf::RenderWindow* inWindow)
{
	sf::Event event;
	while (inWindow->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			inWindow->close();
		}
		InputProcessor->ProcessInput(event);
	}
}

void Zengine::Shutdown()
{

}