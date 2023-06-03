#include "Zengine.h"
#include <SFML/Graphics.hpp>
#include "World.h"

Zengine* Zengine::Engine = nullptr;

World world;

Zengine* Zengine::CreateInstance()
{
	Engine = new Zengine();
	return Engine;
}

void Zengine::Run()
{
	// Inicjalizacja silnika
	engineRunning = true;
    
	world.LoadWorld("Textures/TexturesLevel1.txt", "Tiles/TxtFiles/Level1.txt");

	//MainLoop();
}

void Zengine::MainLoop()
{
	// Kazda klatka bedzie obslugiwana w tym miejscu

	//ProcessInput();
	//ProcessGameLogic();
	//Render();
}

void Zengine::Shutdown()
{
}