#pragma once
#include "../Interfaces/IEngineModule.h"
#include <vector> 
#include <SFML/Graphics.hpp>

struct RenderObject
{
	sf::RectangleShape* drawable;
	int zOrder = 0;
	int layerId = 0;
};

struct RenderingStack
{
public:
	void Clear();
	std::vector<RenderObject*> renderQueue;
	void DivisionOfObjectsIntoLayersByLayerId();

	std::vector<RenderObject*>* GetRenderQueueLayer0();
	std::vector<RenderObject*>* GetRenderQueueLayer1();
	std::vector<RenderObject*>* GetRenderQueueLayer2();

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
	void SortRenderLayers(RenderingStack* renderStack);

	virtual void Initialize() override {}
	virtual void UnInitialize() override {}

private:
	sf::RenderWindow* window=nullptr;
	void SortLayer(std::vector<RenderObject*> &layer);
	void DrawLayer(std::vector<RenderObject*> &layer);
};

