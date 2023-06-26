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
	renderStack = new RenderingStack();

	window = new sf::RenderWindow(sf::VideoMode(960, 544), "Zengine");
	ViewInitialize();

	RenderModule->Initialize(window);

	world.Initialize("Mario", "Graphics/Mario.png");
	world.MapInitialize("Textures/TexturesLevel1.txt", "Tiles/TxtFiles/Level1.txt");
	//world.DrawPlayer(renderStack);
	world.DrawMap(renderStack);

	MainLoop();
}

void Zengine::ViewInitialize()
{
	mainView.setSize(960, 544);
	mainView.setCenter(window->getSize().x / 2.f, window->getSize().y / 2.f);
}


void Zengine::MainLoop()
{
	CharacterInputHandler inputHandler = world.GetPlayer()->GetInputHandler();
	InputProcessor->RegisterInputHandler(reinterpret_cast<InputHandler*>(&inputHandler));

	while (window->isOpen())
	{
		//renderStack.renderQueue.clear();

		ProcessInput(window);
		window->clear();

		//Render game elements
		window->setView(mainView);

		//world.DrawMap(*window);
		RenderModule->ProcessDrawingElements(renderStack);

		//Draw UI
		window->setView(window->getDefaultView());

		window->display();
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