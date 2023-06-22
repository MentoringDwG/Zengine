#pragma once
#include <SFML/Window/Event.hpp>
#include <iostream>

using namespace std;

class InputHandler
{
public:
	int ID;
	virtual bool ProcessInput(sf::Event& event) = 0;
	virtual bool CanConsumeInput() = 0;
};
