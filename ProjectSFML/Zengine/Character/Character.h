#pragma once

#include <iostream>
#include "../InputModule/CharacterInputHandler.h"
#include "../ZenObject/MovableObject.h"
#include "../World/TextureAsset.h"
#include "../Renderer/Renderer.h"
#include "../ZenObject/ZenShape.h"
#include "../Colliders/CircleCollider2D.h";

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
	void SetCollider(Vector2* position, float radius);

private:
	CharacterInputHandler inputHandler;

	TextureAsset* textureAsset;
	RenderObject* characterRenderObject = nullptr;
	ZenShape* zenShape = nullptr;

	float moveSpeed;

	CircleCollider2D* collider2D;
	void HandleCollisionStart(const CircleCollider2D* other);
};

