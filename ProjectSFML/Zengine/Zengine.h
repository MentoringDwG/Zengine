#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <chrono>
#include "Interfaces/IEngineModule.h"
#include "InputModule/CharacterInputHandler.h"
#include "Renderer/Renderer.h"
#include "ZenObject/ZenObject.h"
#include "Physics2D/ZenPhysics2D.h"
#include "ZenObject/ZenText.h"
#include "StateMachine/StateMachine.h"


class Zengine
{
public:
	static Zengine* CreateInstance();

	void Run();
	void MainLoop();
	void Shutdown();

private:
	void ProcessInput(sf::RenderWindow* inWindow);
	void ViewInitialize();
	void RenderingStackInitialize();
	void CharacterInputHandlerInitialize();
	void UIInitialize();
	void CountFrameTime(std::chrono::nanoseconds time);
	void CountFPS();
	void SetUI();
	void StateInitialize();
	void OnLoading(int id);

	static class Zengine* Engine;
	class InputProcessorModule* InputProcessor = nullptr;
	Renderer* RenderModule = nullptr;
	RenderingStack* renderStack = nullptr;
	CharacterInputHandler characterInputHandler;
	ZenText* fpsText;
	sf::RenderWindow* window = nullptr;
	sf::View mainView;
	sf::View playerView;
	std::vector<IEngineModule*> engineModules;
	std::stringstream fpsStringstream;
	bool engineRunning = false;

	class StateMachine* stateMachine = nullptr;
	class MainMenuState* mainMenuState = nullptr;
	class LoadingState* loadingState = nullptr;
	class GameplayState* gameplayState = nullptr;
	class WaitingRoomState* waitingRoomState = nullptr;
	class ControlsPanelState* controlsPanelState = nullptr;
	class AuthorsState* authorsState = nullptr;

	int frameTme = 1;
	float fps = 60;
};

