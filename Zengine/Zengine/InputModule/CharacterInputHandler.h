#pragma once

#include "InputHandler.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <list>

using namespace std;

class Character;

class CharacterInputHandler : public InputHandler
{
public:
	virtual bool ProcessInput(sf::Event& event, sf::RenderWindow* inWindow) override;
	virtual bool CanConsumeInput() override;

	void SetOwningCharacter(class MovableObject* character);
	void SetName(string nameIN);
	string GetName();
	void ProcesMovement();

private:
	enum class MovingStates
	{
		standing = 0,
		movingLeft = 1,
		movingRight = 2,
		movingUp = 3,
	};

	void KeyPressed(sf::Event& event);
	void KeyReleased(sf::Event& event);
	bool CanAddMovingState(MovingStates state);
	void AddMovingState(MovingStates state);
	bool IsMovingUp();

	string name;
	list<MovingStates> movingStatesList;
	list <MovingStates>::iterator itr;
	class MovableObject* owningCharacter = nullptr;
	MovingStates movingStates = CharacterInputHandler::MovingStates::standing;
};