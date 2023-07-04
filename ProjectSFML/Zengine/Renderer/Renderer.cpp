#include "Renderer.h"
#include <SFML/Graphics.hpp>


void Renderer::Initialize(sf::RenderWindow* inWindow)
{
	window = inWindow;
}

void RenderingStack::Clear()
{
	renderQueue.clear();
	renderQueueLayer0.clear();
	renderQueueLayer1.clear();
	renderQueueLayer2.clear();
}

void RenderingStack::DivisionOfObjectsIntoLayersByLayerId()
{
	for (int i = 0; i < renderQueue.size(); i++)
	{
		switch (renderQueue[i]->layerId)
		{
		case 0:
		{
			renderQueueLayer0.push_back(renderQueue[i]);
			break;
		}
		case 1:
		{
			renderQueueLayer1.push_back(renderQueue[i]);
			break;
		}
		case 2:
		{
			renderQueueLayer2.push_back(renderQueue[i]);
			break;
		}
		default:
		{
			renderQueueLayer0.push_back(renderQueue[i]);
			break;
		}
		}
	}
}

//RenderingStack getters 
std::vector<RenderObject*>* RenderingStack::GetRenderQueueLayer0()
{
	return &renderQueueLayer0;
}

std::vector<RenderObject*>* RenderingStack::GetRenderQueueLayer1()
{
	return &renderQueueLayer1;
}

std::vector<RenderObject*>* RenderingStack::GetRenderQueueLayer2()
{
	return &renderQueueLayer2;
}

void Renderer::SortRenderLayers(RenderingStack* renderStack)
{
	SortLayer(*renderStack->GetRenderQueueLayer0());

	SortLayer(*renderStack->GetRenderQueueLayer1());

	SortLayer(*renderStack->GetRenderQueueLayer2());

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
	DrawLayer(*renderStack->GetRenderQueueLayer0());

	DrawLayer(*renderStack->GetRenderQueueLayer1());

	DrawLayer(*renderStack->GetRenderQueueLayer2());
}

void Renderer::DrawLayer(std::vector<RenderObject*>& layer)
{
	for (int i = 0; i < layer.size(); ++i)
	{
		sf::RectangleShape* rectangleShape = layer[i]->drawable;
		window->draw(*rectangleShape);
	}
}