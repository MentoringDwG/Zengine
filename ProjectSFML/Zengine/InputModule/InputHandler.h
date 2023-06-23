#pragma once
#include <SFML/Window/Event.hpp>

class InputHandler
{
public:
	virtual bool ProcessInput(sf::Event& event) = 0;
	virtual bool CanConsumeInput() = 0;

private:
	int ID;
};
