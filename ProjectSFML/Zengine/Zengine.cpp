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
long long fib(long long n) 
{
	if (n < 2) 
	{
		return n;
	}
	else 
	{
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
	zenPhysics2D = new ZenPhysics2D();

	window = new sf::RenderWindow(sf::VideoMode(960, 544), "Zengine");
	window->setFramerateLimit(60);
	ViewInitialize();

	RenderModule->Initialize(window);
	world.Initialize("Mario", "Graphics/Mario.png", 2.0f);
	world.MapInitialize("Textures/TexturesLevel1.txt", "Tiles/TxtFiles/Level1.txt");
	world.PhysicalZenObject2DInitialize(zenPhysics2D, "Graphics/Enemy1.png");
	RenderingStackInitialize();

	UIInitialize();

	MainLoop();
}

void Zengine::ViewInitialize()
{
	mainView.setSize(960, 544);
	mainView.setCenter(window->getSize().x / 2.f, window->getSize().y / 2.f);
}

void Zengine::RenderingStackInitialize()
{
	world.Draw(renderStack);
	renderStack->DivisionOfObjectsIntoLayersByLayerId();
	RenderModule->SortRenderLayers(renderStack);
}

void Zengine::UIInitialize()
{
	fpsText = new ZenObject(0, "fpsText");
	fpsText->Position = sf::Vector2f(0, 0);
	fpsText->text.setPosition(fpsText->Position);
	fpsText->text.setFillColor(sf::Color::White);
	fpsText->text.setCharacterSize(20);
	fpsText->font.loadFromFile("Fonts/Super_Mario_Bros_/SuperMarioBros.ttf");
	fpsText->text.setFont(fpsText->font);
}

void Zengine::MainLoop()
{
	CharacterInputHandler inputHandler = world.GetPlayer()->GetInputHandler();
	InputProcessor->RegisterInputHandler(reinterpret_cast<InputHandler*>(&inputHandler));


	while (window->isOpen())
	{
		start_time = std::chrono::high_resolution_clock::now();

		ProcessInput(window);

		window->clear();

		//zenPhysics2D->CalculatePhysics();

		//Render game elements
		window->setView(mainView);
		RenderModule->ProcessDrawingElements(renderStack);

		//Draw UI
		window->setView(window->getDefaultView());
		window->draw(fpsText->text);
		//window->draw(*zenPhysics2D->PhysicalObjects[0]->rectangleShape);
		window->display();

		end_time = std::chrono::high_resolution_clock::now();

		CountFrameTime();
		CountFPS();

		SetUI();
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

void Zengine::CountFrameTime()
{
	time = end_time - start_time;

	frameTme = time / std::chrono::milliseconds(1);
	if (frameTme == 0)
	{
		frameTme = 1;
	}
}

void Zengine::CountFPS()
{
	fps = 1000 / frameTme;
}

void Zengine::SetUI()
{
	fpsStringstream.str(std::string());
	fpsStringstream << "Frame took: " << frameTme << " ms. FPS: " << fps;
	fpsText->text.setString(fpsStringstream.str());
}

void Zengine::Shutdown()
{

}