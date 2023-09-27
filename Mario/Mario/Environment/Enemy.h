#pragma once

#include "Zengine/Physics2D/PhysicalZenObject2D.h"

class Enemy
{
private:
	void HandleCollisionStart(Collider* other);
	void HandleCollisionEnd(Collider* other);

	class HeartsPanel* heartsPanel = nullptr;
	PhysicalZenObject2D* physicalZenObject = nullptr;
	class CircleCollider2D* circleCollider = nullptr;
	bool isCollisionWithCharacter = false;

	sf::Vector2f colliderPosition;

public:
	Enemy(int inID, string inName, string enemySpritePath, sf::Vector2f startPosition, sf::Vector2f inSize, class HeartsPanel* heartsPanelIn);
	~Enemy();

	void AddForce(float mass, Vector2 force, float time);
	Vector2* GetTransposition();
	Vector2* GetVelocity();
	void Update();
};

