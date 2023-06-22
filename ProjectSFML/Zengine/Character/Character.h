#pragma once
#include <iostream>
#include "../InputModule/CharacterInputHandler.h"

class Character
{
public:
	Character(std::string name)
	{
		InputHandler.name = name;
	}
	CharacterInputHandler InputHandler;
};

