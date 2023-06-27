#include "Renderer.h"
#include <SFML/Graphics.hpp>

void Renderer::Initialize(sf::RenderWindow* inWindow)
{
	window = inWindow;
}

void Renderer::ProcessDrawingElements(RenderingStack *renderStack)
{
	//std::vector<int> sortedQueue;

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

	for (int i = 0; i<renderStack->renderQueue.size(); ++i)
	{		
		sf::RectangleShape* rectangleShape = renderStack->renderQueue[i]->drawable;
		sf::Texture texture = *renderStack->renderQueue[i]->texcure;

		rectangleShape->setTexture(&texture);
		window->draw(*rectangleShape);
	}

	//for (int i = 0; sortedQueue.size(); ++i)
	//{
	//	int indexInQueue = sortedQueue[i];
	//	sf::Drawable* drawable = renderStack->renderQueue[indexInQueue].drawable;
	//	window->draw(*drawable);
	//}
}
