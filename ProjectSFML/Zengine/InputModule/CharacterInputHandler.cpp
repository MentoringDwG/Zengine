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
    // Tutaj mozemy zaimplementowaæ nasz input dla gracza.
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::A)
        {
			movingStatesList.push_back(movingLeft);
        }

        if (event.key.code == sf::Keyboard::D)
        { 
			movingStatesList.push_back(movingRight);
        }

		if (event.key.code == sf::Keyboard::W)
		{
			movingStatesList.push_back(movingUp);
		}

		if (event.key.code == sf::Keyboard::S)
		{
			movingStatesList.push_back(movingDown);
		}
    }

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

	list <MovingStates>::iterator itr;
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
		else
		{
			continue;
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