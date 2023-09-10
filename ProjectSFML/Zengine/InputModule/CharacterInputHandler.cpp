#include "CharacterInputHandler.h"
#include "../Character/Character.h"

bool CharacterInputHandler::ProcessInput(sf::Event& event, sf::RenderWindow* inWindow)
{
	KeyPressed(event);
	KeyReleased(event);

    return false;
}

void CharacterInputHandler::KeyPressed(sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::A)
		{
			AddMovingState(MovingStates::movingLeft);
			movingStatesList.remove(MovingStates::movingRight);
		}

		if (event.key.code == sf::Keyboard::D)
		{
			AddMovingState(MovingStates::movingRight);
			movingStatesList.remove(MovingStates::movingLeft);
		}

		if (event.key.code == sf::Keyboard::W)
		{
			AddMovingState(MovingStates::movingUp);
		}
	}
}

void CharacterInputHandler::AddMovingState(MovingStates state)
{
	if (CanAddMovingState(state))
	{
		movingStatesList.push_back(state);
	}
}

bool CharacterInputHandler::CanAddMovingState(MovingStates state)
{
	itr = movingStatesList.begin();
	for (itr; itr != movingStatesList.end(); itr++)
	{
		if (*itr == state)
		{
			return false;
		}
	}

	return true;
}

void CharacterInputHandler::KeyReleased(sf::Event& event)
{
	if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::A)
		{
			movingStatesList.remove(MovingStates::movingLeft);
		}

		if (event.key.code == sf::Keyboard::D)
		{
			movingStatesList.remove(MovingStates::movingRight);
		}

		if (event.key.code == sf::Keyboard::W)
		{
			movingStatesList.remove(MovingStates::movingUp);
		}
	}
}

void CharacterInputHandler::ProcesMovement()
{
	itr = movingStatesList.begin();
	for (itr; itr != movingStatesList.end(); itr++)
	{
		if (*itr == MovingStates::movingLeft)
		{
			owningCharacter->MoveLeft();
		}
		if (*itr == MovingStates::movingRight)
		{
			owningCharacter->MoveRight();
		}
		if (*itr == MovingStates::movingUp)
		{
			owningCharacter->MoveUp();
		}
	}
}

bool CharacterInputHandler::IsMovingUp()
{
	itr = movingStatesList.begin();
	for (itr; itr != movingStatesList.end(); itr++)
	{
		if (*itr == MovingStates::movingUp)
		{
			return true;
		}
	}

	return false;
}

bool CharacterInputHandler::CanConsumeInput()
{
    return false;
}

void CharacterInputHandler::SetOwningCharacter(Character* character)
{
    owningCharacter = character;
}

void CharacterInputHandler::SetName(string nameIn)
{
    name = nameIn;
}

string CharacterInputHandler::GetName()
{
    return name;
}