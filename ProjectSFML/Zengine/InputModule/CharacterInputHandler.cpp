#include "CharacterInputHandler.h"
#include "../Character/Character.h"

bool CharacterInputHandler::ProcessInput(sf::Event& event)
{
    // Tutaj mozemy zaimplementować nasz input dla gracza.
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::A)
        {
            OwningCharacter->MoveLeft();
        }

        if (event.key.code == sf::Keyboard::D)
        { 
            OwningCharacter->MoveRight();
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
    CharacterInputHandler::OwningCharacter = character;
}