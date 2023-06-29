#include "Zengine.h"
#include <SFML/Graphics.hpp>
#include "World/World.h"
#include "InputModule/InputProcessorModule.h"
#include "InputModule/CharacterInputHandler.h"
#include "Renderer/Renderer.h"
#include <chrono>

Zengine* Zengine::Engine = nullptr;
World world;


// long operation to time
long long fib(long long n) {
	if (n < 2) {
		return n;
	}
	else {
		return fib(n - 1) + fib(n - 2);
	}
}

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

	world.Initialize("Mario", "Graphics/Mario.png", 2.0f);
	world.MapInitialize("Textures/TexturesLevel1.txt", "Tiles/TxtFiles/Level1.txt");

	world.DrawPlayer(renderStack);
	world.DrawMap(renderStack);
	RenderModule->SortRenderStack(renderStack);

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

	auto start_time = std::chrono::high_resolution_clock::now();
	auto end_time = std::chrono::high_resolution_clock::now();
	auto time = end_time - start_time;

	while (window->isOpen())
	{
		start_time = std::chrono::high_resolution_clock::now();
		ProcessInput(window);
		window->clear();

		//Render game elements
		window->setView(mainView);
		RenderModule->ProcessDrawingElements(renderStack);

		//Draw UI
		window->setView(window->getDefaultView());

		window->display();

		end_time = std::chrono::high_resolution_clock::now();
		time = end_time - start_time;

		int frameTme = time / std::chrono::milliseconds(1);
		if (frameTme == 0)
		{
			frameTme = 1;
		}

		float fps = 1000 / frameTme;
		std::cout << "Frame took:" << frameTme << "ms. FPS = " << fps << "\n";
	}

	//ProcessGameLogic();
}

void Zengine::ProcessInput(sf::RenderWindow* inWindow)
{
	sf::Event event;
	while (inWindow->pollEvent(event))
	{
		cout << "Pooling input event..." << endl;
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