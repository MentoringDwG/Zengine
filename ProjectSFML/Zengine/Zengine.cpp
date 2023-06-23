#include "Zengine.h"
#include <SFML/Graphics.hpp>
#include "World/World.h"
#include "InputModule/InputProcessorModule.h"
#include "InputModule/CharacterInputHandler.h"
#include "Renderer/Renderer.h"

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
	RenderModule = new Renderer();

	window = new sf::RenderWindow(sf::VideoMode(960, 544), "Zengine");

	RenderModule->Initialize(window);
	world.Initialize();

	MainLoop();
}

void Zengine::MainLoop()
{
	// Kazda klatka bedzie obslugiwana w tym miejscu

	Character mario("mario");
	Character luigi("luigi");
	InputProcessor->RegisterInputHandler(reinterpret_cast<InputHandler*>(&mario.InputHandler));
	InputProcessor->RegisterInputHandler(reinterpret_cast<InputHandler*>(&luigi.InputHandler));

	sf::View mainView;
	mainView.setSize(960, 544);
	mainView.setCenter(window->getSize().x / 2.f, window->getSize().y / 2.f);

	world.MapInitialize("Textures/TexturesLevel1.txt", "Tiles/TxtFiles/Level1.txt");

	RenderingStack renderStack;
	while (window->isOpen())
	{
		renderStack.renderQueue.clear();

		ProcessInput(window);
		window->clear();

		//Render game elements
		window->setView(mainView);

		world.DrawMap(*window);

		//Draw UI
		window->setView(window->getDefaultView());

		window->display();
		RenderModule->ProcessDrawingElements(&renderStack);
	}

	//ProcessGameLogic();
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