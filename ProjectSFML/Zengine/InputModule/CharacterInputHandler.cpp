#include "CharacterInputHandler.h"
#include "../Character/Character.h"

bool CharacterInputHandler::ProcessInput(sf::Event& event)
{
    // Tutaj mozemy zaimplementowaæ nasz input dla gracza.
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::A)
        {
            // Move left
            printf("%s : Move left\n", name.c_str());
        }

        if (event.key.code == sf::Keyboard::D)
        {
            // Move right
            printf("%s : Move right\n", name.c_str());            
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