#pragma once

#include "../Interfaces/IEngineModule.h"
#include <vector> 
#include <SFML/Graphics.hpp>
#include <map>

struct RenderObject
{
	RenderObject(sf::RectangleShape* drawable, int zOrder, int layerId);
	RenderObject(sf::Text* text, int zOrder, int layerId);

	int zOrder = 0;
	int layerId = 0;
	sf::RectangleShape* drawable = nullptr;
	sf::Text* text = nullptr;
};

struct RenderingStack
{
	void Clear();
	void DivisionOfObjectsIntoLayersByLayerId();
	void RemoveFromRenderLayers(RenderObject* renderObjectToRemove);

	std::vector<RenderObject*> renderQueue;
	std::vector<RenderObject*> renderQueueUI;
	std::map <int, std::vector<RenderObject*>> renderLayers;
};

class Renderer : IEngineModule
{
public:
	~Renderer();

	void Initialize(sf::RenderWindow* inWindow);
	void ProcessDrawingElements(RenderingStack* renderStack);
	void ProcessDrawingUI(RenderingStack* renderStack);
	void SortRenderLayers(RenderingStack* renderStack);

	virtual void Initialize() override {}
	virtual void UnInitialize() override {}

private:
	void SortLayer(std::vector<RenderObject*>& layer);
	void DrawLayer(std::vector<RenderObject*>& layer);

	sf::RenderWindow* window = nullptr;
};

