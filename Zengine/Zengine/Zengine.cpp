// Copyright Z.Z. Zengine (c)

#include "Zengine.h"
#include "World/World.h"
#include "InputModule/InputProcessorModule.h"
#include "Structs/Timer.h"
#include "InputModule/UIInputHandler.h"
#include "StateMachine/StateMachine.h"
#include "ZenObject/ZenText.h"
#include "Physics2D/ZenPhysics2D.h"
#include "Interfaces/IEngineModule.h"
#include "Animation/AnimationProcesor.h"
#include "Audio/AudioSystem.h"
#include "Core/App.h"

Zengine* Zengine::Engine = nullptr;

Zengine* Zengine::CreateInstance()
{
	Engine = new Zengine();
	return Engine;
}

void Zengine::Run(class App* inApp, class World* world)
{
	engineRunning = true;

	InputProcessor = new InputProcessorModule();
	RenderModule = new Renderer();
	renderStack = new RenderingStack();
	audioSystem = new AudioSystem();
	app = inApp;

	window = new sf::RenderWindow(sf::VideoMode(960, 544), "Zengine");
	window->setFramerateLimit(60);
	ViewInitialize();
	
	RenderModule->Initialize(window);

	Start();
	this->world = world;
	world->Initialize(audioSystem);
	world->MapInitialize();

	RenderingStackInitialize();

	UIInitialize();

	animationProcesor = AnimationProcesor::Get();

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

void Zengine::MainLoop()
{
	Timer* timerForPhysics = new Timer();
	Timer* timerForFPSCounter = new Timer();

	while (window->isOpen())
	{
		timerForFPSCounter->Reset();
		ProcessInput(window);

		window->clear();

		characterInputHandler.ProcesMovement();
		timerForPhysics->TimerStop();
		if (timerForPhysics->timeMs >= ZenPhysics2D::Get()->GetPhysicsTimeStep())
		{
			world->ApplyForceToPhysicsObject();
			ZenPhysics2D::Get()->CalculatePhysics();
			world->UpdateObjects();
			timerForPhysics->start_time = std::chrono::high_resolution_clock::now();
		}
		ZenPhysics2D::Get()->CalculateCollision();

		world->SetCamera(&mainView, Vector2((float)window->getSize().x, (float)window->getSize().y));

		app->Tick(-1);

		//Render game elements
		window->setView(mainView);

		animationProcesor->PlayAnimations();

		RenderModule->ProcessDrawingElements(renderStack);
		
		ZenPhysics2D::Get()->SetShouldShowDebug(gameMode);
		ZenPhysics2D::Get()->DrawColliders(window);

		//Draw UI
		window->setView(window->getDefaultView());
		window->draw(fpsText->GetText());
		RenderModule->ProcessDrawingUI(renderStack);

		window->display();

		CountFPS();
		SetUI();

		timerForFPSCounter->TimerStop();
		CountFrameTime(timerForFPSCounter->time);		
	}
}

void Zengine::CharacterInputHandlerInitialize()
{
	characterInputHandler = *world->GetCharacterInputHandler();
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
	delete audioSystem;
	delete fpsText;	 
	delete InputProcessor;
	delete audioSystem;
	delete app;
	delete world;
	delete window;
	delete RenderModule;
	delete renderStack;
}

RenderingStack* Zengine::GetRenderingStack()
{
	return renderStack;
}

Renderer* Zengine::GetRenderer()
{
	return RenderModule;
}

AudioSystem* Zengine::GetAudioSystem()
{
	return audioSystem;
}

void Zengine::ChangeWorld(class World* world)
{
	this->world = world;
}