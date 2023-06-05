#pragma once

// G³ówna klasa silnika gry

#include "Interfaces/IEngineModule.h"
#include <vector>

namespace sf { class RenderWindow; }

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
};

