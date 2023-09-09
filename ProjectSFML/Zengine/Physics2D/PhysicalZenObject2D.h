#pragma once

#include "../ZenObject/ZenObject.h"
#include "../Renderer/Renderer.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Structs/Vector2.h"
#include "../ZenObject/ZenShape.h"
#include "../Colliders/Collider.h"

class PhysicalZenObject2D:public ZenObject
{
public:
	enum class CollisionPushSide
	{
		NONE = 0,
		TOP = 1,
		BOTTOM = 2,
		RIGHT = 3,
		LEFT = 4,
		Max,
	};

	CollisionPushSide collisionPushSide = CollisionPushSide::NONE;

	ZenShape* zenShape;
	PhysicalZenObject2D(int inID, string inName, string enemySpritePath, sf::Vector2f startPosition, sf::Vector2f inSize);
	void CalculatePhysics();
	void AddForce(float mass, Vector2 force, float time);

	Vector2* GetTransposition();
	Vector2* GetVelocity();

	void SetCollider(class Collider* collider);
	void SetGravity(float gravity);
	float GetGravity();

private:
	void CalculationColliderPush();
	Vector2* deltaPositions;

	float mass = 1.0f;
	float fakeDrag = 0.05f;
	float gravity = 0.0f;
	Vector2* force;

	Vector2* velocity;
	Vector2* transposition;
	Vector2* acceleration;

	bool canUseGravity = false;
	Collider* collider = nullptr;
	std::map<Collider::ColliderTags, std::vector<Collider*>> collisionColliders;
	void ResettingVariables();
	void HandleCollisionStart(Collider* other);
	void HandleCollisionEnd(Collider* other);
};

