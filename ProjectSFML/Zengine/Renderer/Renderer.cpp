#include "Renderer.h"
#include <SFML/Graphics.hpp>

#pragma optimize("", off)

void Renderer::Initialize(sf::RenderWindow* inWindow)
{
	window = inWindow;
}

void RenderingStack::DivisionOfObjectsIntoLayersByLayerId()
{
	renderQueueLayer0.clear();
	renderQueueLayer1.clear();
	renderQueueLayer2.clear();

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

std::vector<RenderObject*> RenderingStack::GetRenderQueueLayer0()
{
	return renderQueueLayer0;
}

std::vector<RenderObject*> RenderingStack::GetRenderQueueLayer1()
{
	return renderQueueLayer1;
}

std::vector<RenderObject*> RenderingStack::GetRenderQueueLayer2()
{
	return renderQueueLayer2;
}

void RenderingStack::SetRenderQueueLayer0(std::vector<RenderObject*> sortedLayer)
{
	renderQueueLayer0 = sortedLayer;
}

void RenderingStack::SetRenderQueueLayer1(std::vector<RenderObject*> sortedLayer)
{
	renderQueueLayer1 = sortedLayer;
}

void RenderingStack::SetRenderQueueLayer2(std::vector<RenderObject*> sortedLayer)
{
	renderQueueLayer2 = sortedLayer;
}

void Renderer::SortRenderLayers(RenderingStack* renderStack)
{
	std::vector<RenderObject*> layer;

	layer = renderStack->GetRenderQueueLayer0();
	SortLayer(layer);
	renderStack->SetRenderQueueLayer0(layer);

	layer = renderStack->GetRenderQueueLayer1();
	SortLayer(layer);
	renderStack->SetRenderQueueLayer1(layer);

	layer = renderStack->GetRenderQueueLayer2();
	SortLayer(layer);
	renderStack->SetRenderQueueLayer2(layer);
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
	std::vector<RenderObject*> layer;

	layer = renderStack->GetRenderQueueLayer0();
	DrawLayer(layer);

	layer = renderStack->GetRenderQueueLayer1();
	DrawLayer(layer);

	layer = renderStack->GetRenderQueueLayer2();
	DrawLayer(layer);
}

void Renderer::DrawLayer(std::vector<RenderObject*>& layer)
{
	for (int i = 0; i < layer.size(); ++i)
	{
		sf::RectangleShape* rectangleShape = layer[i]->drawable;
		window->draw(*rectangleShape);
	}
}

#pragma optimize("", off)