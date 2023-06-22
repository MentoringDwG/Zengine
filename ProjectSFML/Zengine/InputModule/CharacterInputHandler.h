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

		string name;

		void SetOwningCharacter(Character* character);

	private:
		class Character* OwningCharacter;

};