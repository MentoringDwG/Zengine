#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <chrono>
#include <functional>
#include "InputModule/CharacterInputHandler.h"
#include "Renderer/Renderer.h"

class Zengine
{
public:
	static Zengine* CreateInstance();

	void Run();
	void MainLoop();
	void Shutdown();

	void CharacterInputHandlerInitialize();
	class StateMachine* GetStateMachine();
	RenderingStack* GetRenderingStack();
	Renderer* GetRenderer();
	class World* GetWorld();

	std::function<void(int)> Start;

private:
	void ProcessInput(sf::RenderWindow* inWindow);
	void ViewInitialize();
	void RenderingStackInitialize();
	void UIInitialize();
	void CountFrameTime(std::chrono::nanoseconds time);
	void CountFPS();
	void SetUI();

	CharacterInputHandler characterInputHandler;
	std::stringstream fpsStringstream;
	sf::View mainView;
	sf::View playerView;
	std::vector<class IEngineModule*> engineModules;
	float fps = 60;
	int frameTme = 1;
	static class Zengine* Engine;
	class InputProcessorModule* InputProcessor = nullptr;
	Renderer* RenderModule = nullptr;
	RenderingStack* renderStack = nullptr;
	class ZenText* fpsText = nullptr;
	sf::RenderWindow* window = nullptr;
	class StateMachine* stateMachine = nullptr;
	bool engineRunning = false;
};

