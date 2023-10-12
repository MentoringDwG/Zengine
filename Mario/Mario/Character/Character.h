#pragma once

#include <Zengine/InputModule/CharacterInputHandler.h>
#include <Zengine/ZenObject/MovableObject.h>
#include <Zengine/Colliders/Collider.h>

class TextureAsset;
class PhysicalZenObject2D;
struct Vector2;

class Character : public MovableObject
{
public:
	virtual void MoveLeft() override;
	virtual void MoveRight() override;
	virtual void MoveUp() override;
	virtual void MoveDown() override;

	Character(std::string name, string Path, float playerMoveSpeed, class AudioSystem* audioSystem);
	~Character();

	CharacterInputHandler* GetInputHandler();
	void SetTextureAsset(string Path, string Name);
	TextureAsset GetTextureAsset();
	void Draw(struct RenderingStack* renderStack);
	void SetCollider(Vector2 position, Vector2 size);
	void UpdateCharacter();
	bool IsCharacterGrounded();
	void ClearCollisionColliders();

	PhysicalZenObject2D* physicalZenObject2D = nullptr;

private:
	void HandleCollisionStart(Collider* other);
	void HandleCollisionEnd(Collider* other);
	bool IsCollisionWithOneGround();

	std::map<Collider::ColliderTags, std::vector<Collider*>> collisionColliders;
	CharacterInputHandler inputHandler;
	int listenerIndexStart;
	int listenerIndexEnd;
	int walkAnimationId = 0;
	float moveSpeed;
	class BoxCollider2D* collider2D = nullptr;
	TextureAsset* textureAsset = nullptr;
	struct RenderObject* characterRenderObject = nullptr;
	sf::Texture* texture = nullptr;
	bool isGrounded = false;

	class Animation* walkAnimation = nullptr;
	class Animator* animator = nullptr;
	class AudioSystem* audioSystem = nullptr;
};

