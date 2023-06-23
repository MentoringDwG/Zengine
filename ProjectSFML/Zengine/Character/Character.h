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

	Character(std::string name)
		{
			inputHandler.name = name;
			inputHandler.SetOwningCharacter(this);
		}
	CharacterInputHandler GetInputHandler();

private:
	CharacterInputHandler inputHandler;
};

