#pragma once
#include "InputHandler.h"
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <list>

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

	enum MovingStates;
	MovingStates movingStates;
	list<MovingStates> movingStatesList;
	list <MovingStates>::iterator itr;
	void CheckAndAddMovingState(MovingStates state);
	void CallingTheMovementFunction();
};