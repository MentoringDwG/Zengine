#include "Zengine.h"
#include "World/World.h"
#include "InputModule/InputProcessorModule.h"
#include "Structs/Timer.h"

// To musimy przenieœæ do innej klasy.
#include "StateMachine/MainMenuState.h"
#include "StateMachine/LoadingState.h"
#include "StateMachine/GameplayState.h"
#include "StateMachine/ControlsPanelState.h"
#include "StateMachine/AuthorsState.h"
// To w sumie te¿.
#include "Character/Character.h"

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
	stateMachine->TransitionTo(State::MainMenuState);

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
	mainMenuState = new MainMenuState(State::MainMenuState, renderStack, stateMachine, RenderModule);
	loadingState = new LoadingState(State::LoadingState, stateMachine);
	gameplayState = new GameplayState(State::GameplayState);
	controlsPanelState = new ControlsPanelState(State::ControlsPanelState, renderStack, stateMachine);
	authorsState = new AuthorsState(State::AuthorsState, renderStack, stateMachine);

	stateMachine->AddState(mainMenuState);
	stateMachine->AddState(loadingState);
	stateMachine->AddState(gameplayState);
	stateMachine->AddState(controlsPanelState);
	stateMachine->AddState(authorsState);

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

void Zengine::MainLoop()
{
	Timer* timerForPhysics = new Timer();
	Timer* timerForFPSCounter = new Timer();

	while (window->isOpen())
	{
		int stateId = stateMachine->GetCurrentGameStateId();
		
		timerForFPSCounter->Reset();
		ProcessInput(window);

		window->clear();

		if (stateId==State::GameplayState)
		{
			characterInputHandler.ProcesMovement();
			timerForPhysics->TimerStop();
			if (timerForPhysics->timeMs >= ZenPhysics2D::Get()->GetPhysicsTimeStep())
			{
				world.ApplyForceToPhysicsObject();
				ZenPhysics2D::Get()->CalculatePhysics();
				world.UpdateObjects();
				timerForPhysics->start_time = std::chrono::high_resolution_clock::now();
			}
			ZenPhysics2D::Get()->CalculateCollision();
		}

		stateMachine->Update();

		//Render game elements
		window->setView(mainView);

		RenderModule->ProcessDrawingElements(renderStack);
		
		ZenPhysics2D::Get()->SetShouldShowDebug(stateId == State::GameplayState);
		ZenPhysics2D::Get()->DrawColliders(window);

		//Draw UI
		window->setView(window->getDefaultView());
		window->draw(fpsText->GetText());

		if (stateId == State::GameplayState)
		{
			//world.coinCounter->Draw(window);
		}

		window->display();

		CountFPS();
		SetUI();

		timerForFPSCounter->TimerStop();
		CountFrameTime(timerForFPSCounter->time);
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
	frameTme = (int)(time / std::chrono::milliseconds(1));
	if (frameTme == 0)
	{
		frameTme = 1;
	}
}

void Zengine::CountFPS()
{
	fps = (float)(1000 / frameTme);
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