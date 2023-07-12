#pragma once
#include "Interfaces/IEngineModule.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include "Renderer/Renderer.h"
#include <sstream>
#include "ZenObject/ZenObject.h"
#include <chrono>
#include "Physics2D/ZenPhysics2D.h"

struct Timer
{
	std::chrono::steady_clock::time_point start_time;
	std::chrono::steady_clock::time_point end_time;
	std::chrono::nanoseconds time;
	int timeMs;

	Timer()
	{
		start_time = std::chrono::high_resolution_clock::now();
	}

	void TimerStop()
	{
		end_time = std::chrono::high_resolution_clock::now();
		time = end_time - start_time;
		timeMs = time / std::chrono::milliseconds(1);
	}
};


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
	void UIInitialize();
	void CountFrameTime(std::chrono::nanoseconds time);
	void CountFPS();
	void SetUI();

	static class Zengine* Engine;
	class InputProcessorModule* InputProcessor = nullptr;
	Renderer* RenderModule = nullptr;
	RenderingStack* renderStack = nullptr;
	ZenPhysics2D* zenPhysics2D = nullptr;
	ZenObject* fpsText;
	sf::RenderWindow* window = nullptr;
	sf::View mainView;
	sf::View playerView;
	std::vector<IEngineModule*> engineModules;
	std::stringstream fpsStringstream;
	bool engineRunning = false;

	int frameTme = 1;
	float fps = 60;
};

