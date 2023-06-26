#pragma once
#include "Interfaces/IEngineModule.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include "Renderer/Renderer.h"

class Zengine
{
public:

	static Zengine* CreateInstance();
	//static Zengine* GetInstance();
	//IEngineModule GetModule();

	void Run();
	void MainLoop();
	void Shutdown();

private:
	void ProcessInput(sf::RenderWindow* inWindow);

	static class Zengine* Engine;
	bool engineRunning = false;
	std::vector<IEngineModule*> engineModules;
	class InputProcessorModule* InputProcessor = nullptr;

	sf::RenderWindow* window = nullptr;
	sf::View mainView;
	void ViewInitialize();
	class Renderer* RenderModule = nullptr;
	RenderingStack renderStack;
};

