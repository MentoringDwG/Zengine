#pragma once
#include "InputHandler.h"
#include <SFML/Window/Event.hpp>
#include <iostream>

using namespace std;

class Character;

class CharacterInputHandler : public InputHandler
{
public:
	// Inherited via InputHandler
	virtual bool ProcessInput(sf::Event& event) override;
	virtual bool CanConsumeInput() override;

	void SetOwningCharacter(Character* character);
	void SetName(string nameIN);
	string GetName();

private:
	Character* owningCharacter;
	string name;

	bool isMovingRight;
	bool isMovingLeft;
};