#pragma once
#include <iostream>
#include "../InputModule/CharacterInputHandler.h"
#include "../ZenObject/MovableObject.h"
#include "../World/TextureAsset.h"
#include "../Renderer/Renderer.h"

class Character : public MovableObject
{
public:
	virtual void MoveLeft() override;
	virtual void MoveRight() override;
	virtual void MoveUp() override;
	virtual void MoveDown() override;

	Character(std::string name, string Path, float playerMoveSpeed);

	CharacterInputHandler GetInputHandler();
	void SetTextureAsset(string Path, string Name);
	TextureAsset GetTextureAsset();
	void Draw(RenderingStack* renderStack);

private:
	//Input
	CharacterInputHandler inputHandler;

	//Renderer
	TextureAsset* textureAsset;
	sf::RectangleShape character;
	RenderObject* characterRenderObject = nullptr;

	//movement
	float moveSpeed;
};

