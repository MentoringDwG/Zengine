#pragma once

#include <iostream>
#include "../InputModule/CharacterInputHandler.h"
#include "../ZenObject/MovableObject.h"
#include "../World/TextureAsset.h"
#include "../Renderer/Renderer.h"
#include "../ZenObject/ZenShape.h"
#include "../Colliders/CircleCollider2D.h"
#include "../Physics2D/ZenPhysics2D.h"

class Character : public MovableObject
{
public:
	virtual void MoveLeft() override;
	virtual void MoveRight() override;
	virtual void MoveUp() override;
	virtual void MoveDown() override;

	Character(std::string name, string PathR, string PathL, float playerMoveSpeed);

	CharacterInputHandler GetInputHandler();
	void SetTextureAsset(string Path, string Name);
	TextureAsset GetTextureAsset();
	void Draw(RenderingStack* renderStack);
	void SetCollider(Vector2* position, float radius, ZenPhysics2D* zenPhysics2D);
	ZenShape* zenShape = nullptr;

private:
	CharacterInputHandler inputHandler;

	TextureAsset* textureAsset;
	RenderObject* characterRenderObject = nullptr;
	sf::Texture* texture = nullptr;
	CircleCollider2D* collider2D = nullptr;
	string PathR;
	string PathL;
	float moveSpeed;

	void HandleCollisionStart(CircleCollider2D* other);
	void SetGraphicsForMovement(string Path);
};

