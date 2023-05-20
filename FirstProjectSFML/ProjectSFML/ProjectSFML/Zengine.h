#pragma once

// G��wna klasa silnika gry

#include "IEngineModule.h"
#include <vector>

class Zengine
{
	public:

		static Zengine* CreateInstance();
		static Zengine* GetInstance();
		IEngineModule GetModule();

		void Run();
		void MainLoop();
		void Shutdown();

	private:
		static class Zengine* Engine;
		bool engineRunning = false;
		std::vector<IEngineModule> engineModules;

};

