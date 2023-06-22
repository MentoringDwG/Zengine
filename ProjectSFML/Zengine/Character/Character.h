#pragma once
#include <iostream>
#include "../InputModule/CharacterInputHandler.h"
#include "../ZenObject/MovableObject.h"

class Character:public MovableObject
{
public:
	Character(std::string name)
	{
		InputHandler.name = name;
	}

	CharacterInputHandler InputHandler;
};

