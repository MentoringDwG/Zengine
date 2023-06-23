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

	Character(std::string name, string Path)
		{
			inputHandler.SetName(name);
			inputHandler.SetOwningCharacter(this);
			SetTextureAsset(Path, name);
		}

	CharacterInputHandler GetInputHandler();
	void SetTextureAsset(string Path, string Name);
	TextureAsset GetTextureAsset();

private:
	CharacterInputHandler inputHandler;
	TextureAsset *texcureAsset;
};

