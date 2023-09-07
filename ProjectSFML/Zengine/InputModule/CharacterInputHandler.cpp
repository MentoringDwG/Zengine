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
			AddMovingState(movingLeft);
			movingStatesList.remove(movingRight);
		}

		if (event.key.code == sf::Keyboard::D)
		{
			AddMovingState(movingRight);
			movingStatesList.remove(movingLeft);
		}

		if (event.key.code == sf::Keyboard::W)
		{
			AddMovingState(movingUp);
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
			movingStatesList.remove(movingLeft);
		}

		if (event.key.code == sf::Keyboard::D)
		{
			movingStatesList.remove(movingRight);
		}

		if (event.key.code == sf::Keyboard::W)
		{
			movingStatesList.remove(movingUp);
		}
	}
}

void CharacterInputHandler::ProcesMovement()
{
	itr = movingStatesList.begin();
	for (itr; itr != movingStatesList.end(); itr++)
	{
		if (*itr == movingLeft)
		{
			owningCharacter->MoveLeft();
		}
		if (*itr == movingRight)
		{
			owningCharacter->MoveRight();
		}
		if (*itr == movingUp)
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
		if (*itr == movingUp)
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