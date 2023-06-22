#pragma once
#include <iostream>
#include "../InputModule/CharacterInputHandler.h"
#include "../ZenObject/MovableObject.h"

class Character:public MovableObject
{
public:
	virtual void MoveLeft() override;
	virtual void MoveRight() override;

	Character(std::string name)
	{
		InputHandler.name = name;
		InputHandler.SetOwningCharacter(this);
	}

	CharacterInputHandler InputHandler;
};

