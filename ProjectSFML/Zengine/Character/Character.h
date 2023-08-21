#pragma once

#include <iostream>
#include "../InputModule/CharacterInputHandler.h"
#include "../ZenObject/MovableObject.h"
#include "../World/TextureAsset.h"
#include "../Renderer/Renderer.h"
#include "../ZenObject/ZenShape.h"
#include "../Colliders/CircleCollider2D.h"
#include "../Colliders/BoxCollider2D.h"
#include "../Physics2D/ZenPhysics2D.h"
#include "../Physics2D/PhysicalZenObject2D.h"
#include "../Structs/Vector2.h"

class Character : public MovableObject
{
public:
	virtual void MoveLeft() override;
	virtual void MoveRight() override;
	virtual void MoveUp() override;

	Character(std::string name, string Path, float playerMoveSpeed);

	CharacterInputHandler GetInputHandler();
	void SetTextureAsset(string Path, string Name);
	TextureAsset GetTextureAsset();
	void Draw(RenderingStack* renderStack);
	void SetCollider(Vector2* position, Vector2* size);
	PhysicalZenObject2D* physicalZenObject2D = nullptr;
	void UpdateCharacter();

	bool IsCharacterGrounded();
	Vector2* deltaPositions;

private:
	CharacterInputHandler inputHandler;

	TextureAsset* textureAsset;
	RenderObject* characterRenderObject = nullptr;
	sf::Texture* texture = nullptr;
	float moveSpeed;

	BoxCollider2D* collider2D = nullptr;
	void HandleCollisionStart(Collider* other);
	void HandleCollisionEnd(Collider* other);
	int listenerIndexStart;
	int listenerIndexEnd;

	bool isGrounded = false;
	std::map<Collider::ColliderTags, std::vector<Collider*>> collisionColliders;
};

