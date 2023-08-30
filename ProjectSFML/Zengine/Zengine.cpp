#include <SFML/Graphics.hpp>
#include "Zengine.h"
#include "World/World.h"
#include "InputModule/InputProcessorModule.h"
#include "Renderer/Renderer.h"
#include "Structs/Timer.h"
#include "InputModule/UIInputHandler.h"

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

	window = new sf::RenderWindow(sf::VideoMode(960, 544), "Zengine");
	window->setFramerateLimit(60);
	ViewInitialize();
	
	RenderModule->Initialize(window);

	stateMachine = new StateMachine();
	StateInitialize();
	stateMachine->TransitionTo(1);

	world.Initialize("Mario", "Graphics/Mario.png", 2.0f);
	world.MapInitialize("Textures/TexturesLevel1.txt", "Tiles/TxtFiles/Level1.txt");
	world.EnvironmentInitialize("Graphics/coin.png", sf::Vector2f(288, 352), sf::Vector2f(608, 192));
	world.PhysicalZenObject2DInitialize("Graphics/Enemy1.png");

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
	renderStack->DivisionOfObjectsIntoLayersByLayerId();
	RenderModule->SortRenderLayers(renderStack);
}

void Zengine::UIInitialize()
{
	fpsText = new ZenText(0, "fpsText", sf::Vector2f(600, 0));
	fpsText->SetPosition(sf::Vector2f(600, 0));
	fpsText->SetColor(sf::Color::White);
	fpsText->SetSize(20);
	fpsText->SetFont("Fonts/Super_Mario_Bros_/SuperMarioBros.ttf");
}

void Zengine::StateInitialize()
{
	MainMenuState* mainMenuState = new MainMenuState(1, renderStack, stateMachine);
	LoadingState* loadingState = new LoadingState(2, renderStack, stateMachine);
	GameplayState* gameplayState = new GameplayState(3);

	bool canAdd=false;

	canAdd = stateMachine->AddState(mainMenuState);

	canAdd = stateMachine->AddState(loadingState);

	canAdd = stateMachine->AddState(gameplayState);

	loadingState->OnEnterEvent = std::bind(&Zengine::OnLoading, this, std::placeholders::_1);
}

void Zengine::OnLoading(int id)
{
	world.Draw(renderStack);

	RenderingStackInitialize();
	CharacterInputHandlerInitialize();

	waitingRoomState = new WaitingRoomState(0, stateMachine, 3);
	stateMachine->DeleteState(0);
	stateMachine->AddState(waitingRoomState);
	stateMachine->TransitionTo(0);
}

void Zengine::ReplacementFunction(int id)
{

}

void Zengine::MainLoop()
{
	Timer* timerForPhysics = new Timer();
	while (window->isOpen())
	{
		int i = stateMachine->GetCurrentGameStateId();
		Timer* timerForFPSCounter = new Timer();

		ProcessInput(window);

		if (i==3)
		{
			characterInputHandler.ProcesMovement();
		}

		window->clear();

		timerForPhysics->TimerStop();
		if (timerForPhysics->timeMs >= ZenPhysics2D::Get()->GetPhysicsTimeStep())
		{
			if (i == 3)
			{
				world.ApplyForceToPhysicsObject();
				ZenPhysics2D::Get()->CalculatePhysics();
				world.UpdateObjects();
			}
			timerForPhysics->start_time = std::chrono::high_resolution_clock::now();
		}
		ZenPhysics2D::Get()->CalculateCollision();

		stateMachine->Update();

		//Render game elements
		window->setView(mainView);

		RenderModule->ProcessDrawingElements(renderStack);
		
		//ZenPhysics2D::Get()->DrawColliders(window);

		//Draw UI
		window->setView(window->getDefaultView());
		window->draw(fpsText->Draw());

		if (i == 3)
		{
			world.coinCounter->Draw(window);
		}

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
		InputProcessor->ProcessInput(event, window);
		UIInputHandler::Get()->ProcessInput(event, window);
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
	fpsStringstream << "Frame took: " << frameTme << " ms. FPS: " << fps;
	fpsText->SetText(fpsStringstream.str());
}

void Zengine::Shutdown()
{

}