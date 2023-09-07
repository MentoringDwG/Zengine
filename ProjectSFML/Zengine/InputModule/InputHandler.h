#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>

class InputHandler
{
public:
	virtual bool ProcessInput(sf::Event& event, sf::RenderWindow* inWindow) = 0;
	virtual bool CanConsumeInput() = 0;

private:
	int ID = 0;
};
