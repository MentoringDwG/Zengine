#pragma once

#include "InputHandler.h"
#include <SFML/Window/Event.hpp>

class CharacterInputHandler : public InputHandler
{
public:
	// Inherited via InputHandler
	virtual bool ProcessInput(sf::Event& event) override;
	virtual bool CanConsumeInput() override;

	std::string name;
};