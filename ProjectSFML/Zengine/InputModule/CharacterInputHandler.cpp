#include "CharacterInputHandler.h"
#include "../Character/Character.h"

enum CharacterInputHandler::MovingStates
{
	standing = 0,
	movingLeft = 1,
	movingRight = 2,
	movingUp = 3,
	movingDown = 4
};


bool CharacterInputHandler::ProcessInput(sf::Event& event)
{
	KeyPressed(event);
	KeyReleased(event);

	CallingTheMovementFunction();

    return false;
}

void CharacterInputHandler::KeyPressed(sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::A)
		{
			CheckAndAddMovingState(movingLeft);
		}

		if (event.key.code == sf::Keyboard::D)
		{
			CheckAndAddMovingState(movingRight);
		}

		if (event.key.code == sf::Keyboard::W)
		{
			CheckAndAddMovingState(movingUp);
		}

		if (event.key.code == sf::Keyboard::S)
		{
			CheckAndAddMovingState(movingDown);
		}
	}
}

void CharacterInputHandler::CheckAndAddMovingState(MovingStates state)
{
	bool canmove = true;
	itr = movingStatesList.begin();
	for (itr; itr != movingStatesList.end(); itr++)
	{
		if (*itr == state)
		{
			canmove = false;
		}
	}

	if (canmove)
	{
		movingStatesList.push_back(state);
	}
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

		if (event.key.code == sf::Keyboard::S)
		{
			movingStatesList.remove(movingDown);
		}
	}
}

void CharacterInputHandler::CallingTheMovementFunction()
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
		if (*itr == movingDown)
		{
			owningCharacter->MoveDown();
		}
	}
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