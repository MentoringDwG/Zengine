#pragma once

#include "../Interfaces/IEngineModule.h"
#include <vector> 
#include <SFML/Graphics.hpp>
#include <map>

struct RenderObject
{
	RenderObject(sf::RectangleShape* drawable, int zOrder, int layerId);

	sf::RectangleShape* drawable;
	int zOrder = 0;
	int layerId = 0;
};

struct RenderingStack
{
	void Clear();
	void DivisionOfObjectsIntoLayersByLayerId();
	std::vector<RenderObject*> renderQueue;
	std::map <int, std::vector<RenderObject*>> renderLayers;
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

