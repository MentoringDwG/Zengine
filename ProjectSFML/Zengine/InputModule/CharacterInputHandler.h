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
	virtual bool ProcessInput(sf::Event& event) override;
	virtual bool CanConsumeInput() override;

	void SetOwningCharacter(Character* character);
	void SetName(string nameIN);
	string GetName();
	void Start();
	void ProcesMovement();

private:
	Character* owningCharacter;
	string name;

	enum MovingStates;
	MovingStates movingStates;
	list<MovingStates> movingStatesList;
	list <MovingStates>::iterator itr;
	void KeyPressed(sf::Event& event);
	void KeyReleased(sf::Event& event);
	bool CanAddMovingState(MovingStates state);
	void AddMovingState(MovingStates state);
	bool IsMovingUp();
	void UseGravity();
};