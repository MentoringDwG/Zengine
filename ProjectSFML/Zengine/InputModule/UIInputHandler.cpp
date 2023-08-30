#include "UIInputHandler.h"
#include <iostream>

UIInputHandler UIInputHandler::instance;

bool UIInputHandler::ProcessInput(sf::Event& event, sf::RenderWindow* inWindow)
{
	if (widgets.size() == 0) return false;

	sf::Vector2i mousePosition = sf::Mouse::getPosition(*inWindow);
	sf::Vector2f mousePositionF = sf::Vector2f(mousePosition.x, mousePosition.y);


	if (event.type == sf::Event::MouseMoved)
	{
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

	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.key.code == sf::Mouse::Button::Left)
		{
			for (auto* widget : widgets)
			{
				if (widget->IsMouseOver(&mousePositionF) == true)
				{
					widget->OnMousePressed();
				}
			}
		}
	}

	if (event.type == sf::Event::MouseButtonReleased)
	{
		if (event.key.code == sf::Mouse::Button::Left)
		{
			for (auto* widget : widgets)
			{
				if (widget->IsMouseOver(&mousePositionF) == true)
				{
					widget->OnMouseUnPressed();
				}
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

void UIInputHandler::Clear()
{
	widgets.clear();
}