#include "CharacterInputHandler.h"
#include "../Character/Character.h"

bool CharacterInputHandler::ProcessInput(sf::Event& event)
{
    // Tutaj mozemy zaimplementowaæ nasz input dla gracza.
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::A)
        {
			isMovingLeft = true;
        }

        if (event.key.code == sf::Keyboard::D)
        { 
			isMovingRight = true;
        }
    }

	if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::A)
		{
			isMovingLeft = false;
		}

		if (event.key.code == sf::Keyboard::D)
		{
			isMovingRight = false;
		}
	}

	if (isMovingLeft)
	{
		owningCharacter->MoveLeft();
	}
	if (isMovingRight)
	{
		owningCharacter->MoveRight();
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