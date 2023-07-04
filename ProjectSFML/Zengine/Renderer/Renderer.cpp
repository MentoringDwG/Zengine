#include "Renderer.h"
#include <SFML/Graphics.hpp>

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

void Renderer::SortRenderStack(RenderingStack* renderStack)
{
	int k;
	RenderObject* pom;
	for (int i = 0; i < renderStack->renderQueue.size(); ++i)
	{
		k = 1;
		for (int j = i + 1; j < renderStack->renderQueue.size(); j++)
		{
			if (renderStack->renderQueue[j]->zOrder < renderStack->renderQueue[k]->zOrder)
			{
				k = j;
			}
		}
		pom = renderStack->renderQueue[k];
		renderStack->renderQueue[k] = renderStack->renderQueue[i];
		renderStack->renderQueue[i] = pom;
	}
}

void Renderer::ProcessDrawingElements(RenderingStack *renderStack)
{
	for (int i = 0; i<renderStack->renderQueue.size(); ++i)
	{		
		sf::RectangleShape* rectangleShape = renderStack->renderQueue[i]->drawable;
		window->draw(*rectangleShape);
	}
}
