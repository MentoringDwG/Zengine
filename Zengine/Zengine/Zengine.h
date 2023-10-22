// Copyright Z.Z. Zengine (c)

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
	static Zengine* GetInstance(){ return Engine; }

	void Run(class App* inApp, class World* world);
	void MainLoop();
	void Shutdown();

	void CharacterInputHandlerInitialize();
	RenderingStack* GetRenderingStack();
	Renderer* GetRenderer();
	class AudioSystem* GetAudioSystem();
	void ChangeWorld(class World* world);

	std::function<void()> Start;
	bool gameMode = false;

private:
	void ProcessInput(sf::RenderWindow* inWindow);
	void ViewInitialize();
	void RenderingStackInitialize();
	void UIInitialize();
	void CountFrameTime(std::chrono::nanoseconds time);
	void CountFPS();
	void SetUI();

	std::stringstream fpsStringstream;

	// Engine rendering stack features.
	float fps = 60;
	int frameTme = 1;
	sf::View mainView;
	sf::View playerView;
	RenderingStack* renderStack = nullptr;
	sf::RenderWindow* window = nullptr;
	
	// Engine game context.
	CharacterInputHandler characterInputHandler;
	class World* world = nullptr;
	class App* app = nullptr;
	class ZenText* fpsText = nullptr; // to nie powinno byæ tutaj raczej. Jeœli ju¿ to w jakimœ debug module.									
	
	// Engine modules.
	std::vector<class IEngineModule*> engineModules;
	class Renderer* RenderModule = nullptr;
	class InputProcessorModule* InputProcessor = nullptr;
	class AnimationProcesor* animationProcesor = nullptr;
	class AudioSystem* audioSystem = nullptr;
	
	bool engineRunning = false;

	// Zengine instance.
	static class Zengine* Engine;
};
