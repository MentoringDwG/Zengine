#include <SFML/Graphics.hpp>
#include "Zengine.h"
#include "World/World.h"
#include "InputModule/InputProcessorModule.h"
#include "Renderer/Renderer.h"
#include "Structs/Timer.h"

Zengine* Zengine::Engine = nullptr;
World world;

Zengine* Zengine::CreateInstance()
{
	Engine = new Zengine();
	return Engine;
}

void Zengine::Run()
{
	engineRunning = true;

	InputProcessor = new InputProcessorModule();
	RenderModule = new Renderer();
	renderStack = new RenderingStack();
	zenPhysics2D = new ZenPhysics2D();

	window = new sf::RenderWindow(sf::VideoMode(960, 544), "Zengine");
	window->setFramerateLimit(60);
	ViewInitialize();

	RenderModule->Initialize(window);
	world.Initialize("Mario", "Graphics/MarioR.png", "Graphics/MarioL.png", 2.0f);
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
	world.Draw(renderStack, zenPhysics2D);
	renderStack->DivisionOfObjectsIntoLayersByLayerId();
	RenderModule->SortRenderLayers(renderStack);
}

void Zengine::UIInitialize()
{
	fpsText = new ZenText(0, "fpsText");
	fpsText->SetPosition(sf::Vector2f(0, 0));
	fpsText->SetColor(sf::Color::White);
	fpsText->SetSize(20);
	fpsText->SetFont("Fonts/Super_Mario_Bros_/SuperMarioBros.ttf");
}

void Zengine::MainLoop()
{
	CharacterInputHandlerInitialize();

	Timer* timerForPhysics = new Timer();
	while (window->isOpen())
	{
		Timer* timerForFPSCounter = new Timer();

		ProcessInput(window);

		window->clear();

		timerForPhysics->TimerStop();
		if (timerForPhysics->timeMs >= zenPhysics2D->GetPhysicsTimeStep())
		{
			world.ApplyForceToPhysicsObject();
			zenPhysics2D->CalculatePhysics();
			timerForPhysics->start_time = std::chrono::high_resolution_clock::now();
		}

		//Render game elements
		window->setView(mainView);
		RenderModule->ProcessDrawingElements(renderStack);

		//Draw UI
		window->setView(window->getDefaultView());
		window->draw(fpsText->Draw());

		//Draw Colliders
		zenPhysics2D->DrawColliders(window);

		window->display();

		CountFPS();
		SetUI();

		timerForFPSCounter->TimerStop();
		CountFrameTime(timerForFPSCounter->time);
		delete timerForFPSCounter;
	}
}

void Zengine::CharacterInputHandlerInitialize()
{
	characterInputHandler = world.GetPlayer()->GetInputHandler();
	InputProcessor->RegisterInputHandler(reinterpret_cast<InputHandler*>(&characterInputHandler));
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

void Zengine::CountFrameTime(std::chrono::nanoseconds time)
{
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
	//fpsStringstream << "Frame took: " << frameTme << " ms. FPS: " << fps;
	fpsStringstream << "x: " << world.GetPlayer()->zenShape->GetPosition().x << " y: " << world.GetPlayer()->zenShape->GetPosition().y;
	fpsText->SetText(fpsStringstream.str());
}

void Zengine::Shutdown()
{

}