#pragma once
#include "../Interfaces/IEngineModule.h"
#include <vector> 
#include <SFML/Graphics.hpp>

struct RenderObject
{
	sf::RectangleShape* drawable;
	int zOrder = 0;
	// Do przekminienia przez �anet� jak zrobi� dalej - layerowanie. :)
	int layerId = 0;
};

struct RenderingStack
{
public:
	std::vector<RenderObject*> renderQueue;
	void DivisionOfObjectsIntoLayersByLayerId();

private:
	std::vector<RenderObject*> renderQueueLayer0;
	std::vector<RenderObject*> renderQueueLayer1;
	std::vector<RenderObject*> renderQueueLayer2;
};

class Renderer : IEngineModule
{
public:
	void Initialize(sf::RenderWindow* inWindow);
	void ProcessDrawingElements(RenderingStack *renderStack);
	void SortRenderStack(RenderingStack* renderStack);

	virtual void Initialize() override {}
	virtual void UnInitialize() override {}

private:
	sf::RenderWindow* window=nullptr;
};

