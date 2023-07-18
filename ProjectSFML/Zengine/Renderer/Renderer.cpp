#include "Renderer.h"
#include <SFML/Graphics.hpp>

#pragma optimize("", off)
void Renderer::Initialize(sf::RenderWindow* inWindow)
{
	window = inWindow;
}

RenderObject::RenderObject(sf::RectangleShape* drawable, int zOrder, int layerId)
{
	this->drawable = drawable;
	this->zOrder = zOrder;
	this->layerId = layerId;
}

void RenderingStack::Clear()
{
	renderQueue.clear();
	renderLayers.clear();
}

void RenderingStack::DivisionOfObjectsIntoLayersByLayerId()
{
	for (int i = 0; i < renderQueue.size(); i++)
	{
		renderLayers[renderQueue[i]->layerId].push_back(renderQueue[i]);
	}
}

void RenderingStack::RemoveFromRenderLayers(RenderObject* renderObjectToRemove)
{
	for (auto itr = renderLayers[renderObjectToRemove->layerId].begin(); itr != renderLayers[renderObjectToRemove->layerId].end(); ++itr)
	{
		if (*itr == renderObjectToRemove)
		{
			renderLayers[renderObjectToRemove->layerId].erase(itr);
			return;
		}
	}
}

void Renderer::SortRenderLayers(RenderingStack* renderStack)
{
	for (auto itr = renderStack->renderLayers.begin(); itr != renderStack->renderLayers.end(); ++itr)
	{
		SortLayer(itr->second);
	}
}

void Renderer::SortLayer(std::vector<RenderObject*> &layer)
{
	if (layer.size() < 2)
	{
		return;
	}

	int k;
	RenderObject* pom;
	for (int i = 0; i < layer.size(); ++i)
	{
		k = 1;
		for (int j = i + 1; j < layer.size(); j++)
		{
			if (layer[j]->zOrder < layer[k]->zOrder)
			{
				k = j;
			}
		}
		pom = layer[k];
		layer[k] = layer[i];
		layer[i] = pom;
	}
}

void Renderer::ProcessDrawingElements(RenderingStack *renderStack)
{
	for (auto itr = renderStack->renderLayers.begin(); itr != renderStack->renderLayers.end(); ++itr)
	{
		DrawLayer(itr->second);
	}
}

void Renderer::DrawLayer(std::vector<RenderObject*>& layer)
{
	for (int i = 0; i < layer.size(); ++i)
	{
		sf::RectangleShape* rectangleShape = layer[i]->drawable;
		window->draw(*rectangleShape);
	}
}

#pragma optimize("", on)