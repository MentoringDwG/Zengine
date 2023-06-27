#include "Renderer.h"
#include <SFML/Graphics.hpp>

void Renderer::Initialize(sf::RenderWindow* inWindow)
{
	window = inWindow;
}

void Renderer::ProcessDrawingElements(RenderingStack *renderStack)
{
	//std::vector<int> sortedQueue;
	//for (int i = 0; renderStack->renderQueue.size(); ++i)
	//{		
		// Przetwarzanie naszego stosu.
		// Sortujemy sobie po zetce
	//}

	//for (int i = 0; sortedQueue.size(); ++i)
	//{
	//	int indexInQueue = sortedQueue[i];
	//	sf::Drawable* drawable = renderStack->renderQueue[indexInQueue].drawable;
	//	window->draw(*drawable);
	//}
	sf::RectangleShape* rectangleShape = renderStack->renderQueue[0]->drawable;
	sf::Texture texture=*renderStack->renderQueue[0]->texcure;

	rectangleShape->setTexture(&texture);
	window->draw(*rectangleShape);
}
