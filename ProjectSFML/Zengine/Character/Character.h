#pragma once
#include <iostream>
#include "../InputModule/CharacterInputHandler.h"
#include "../ZenObject/MovableObject.h"
#include "../World/TextureAsset.h"

class Character:public MovableObject
{
public:
	virtual void MoveLeft() override;
	virtual void MoveRight() override;

	CharacterInputHandler InputHandler;

	Character(std::string name)
	{
		InputHandler.name = name;
		InputHandler.SetOwningCharacter(this);
	}

};

