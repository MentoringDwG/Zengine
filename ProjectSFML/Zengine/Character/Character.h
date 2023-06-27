#pragma once
#include <iostream>
#include "../InputModule/CharacterInputHandler.h"
#include "../ZenObject/MovableObject.h"
#include "../World/TextureAsset.h"
#include "../Renderer/Renderer.h"

class Character:public MovableObject
{
public:
	virtual void MoveLeft() override;
	virtual void MoveRight() override;

	Character(std::string name, string Path, float playerMoveSpeed)
		{
			inputHandler.SetName(name);
			inputHandler.SetOwningCharacter(this);
			SetTextureAsset(Path, name);

			moveSpeed = playerMoveSpeed;
			
			character.setOrigin(sf::Vector2f(character.getSize().x / 2, character.getSize().y / 2));
		}

	CharacterInputHandler GetInputHandler();
	void SetTextureAsset(string Path, string Name);
	TextureAsset GetTextureAsset();
	void DrawCharacter(RenderingStack* renderStack);

private:
	//Input
	CharacterInputHandler inputHandler;

	//Renderer
	TextureAsset * textureAsset;
	sf::RectangleShape character;
	RenderObject* characterRenderObject=nullptr;
	sf::Texture* texture = nullptr;

	//movement
	float moveSpeed;
};

