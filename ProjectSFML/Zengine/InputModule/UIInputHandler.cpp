#include "UIInputHandler.h"
#include <iostream>

UIInputHandler UIInputHandler::instance;

bool UIInputHandler::ProcessInput(sf::Event& event, sf::RenderWindow* inWindow)
{
	if (widgets.size() == 0) return false;

	if (event.type = sf::Event::MouseMoved)
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(*inWindow);
		sf::Vector2f mousePositionF = sf::Vector2f(mousePosition.x, mousePosition.y);

		for (auto* widget : widgets)
		{
			if (widget->IsMouseOver(&mousePositionF) == true)
			{
				widget->OnMouseHover();
			}
			else
			{
				widget->OnMouseUnHover();
			}
		}
	}


	return false;
}

bool UIInputHandler::CanConsumeInput()
{
	return false;
}

void UIInputHandler::AddWidget(Widget* widget)
{
	widgets.push_back(widget);
}