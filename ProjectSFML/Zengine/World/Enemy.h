#pragma once

#include "../Physics2D/PhysicalZenObject2D.h"
#include "../Physics2D/ZenPhysics2D.h"
#include "../Colliders/CircleCollider2D.h"

class Enemy
{
private:
	PhysicalZenObject2D* physicalZenObject;
	CircleCollider2D* circleCollider;

	void HandleCollisionStart(Collider* other);
	void HandleCollisionEnd(Collider* other);
	bool isCollisionWithCharacter = false;

public:
	Enemy(int inID, string inName, string enemySpritePath, sf::Vector2f startPosition, sf::Vector2f inSize);
	void AddForce(float mass, Vector2 force, float time);
	Vector2* GetTransposition();
	Vector2* GetVelocity();
	void Update();
};

