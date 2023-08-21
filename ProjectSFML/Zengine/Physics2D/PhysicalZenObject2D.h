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
	void CalculateDeltaPositions();
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

