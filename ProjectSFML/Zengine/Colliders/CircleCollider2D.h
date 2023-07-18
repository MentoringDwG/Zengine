#pragma once

#include <functional>
#include <iostream>
#include "../ZenObject/ZenObject.h"
#include "../Structs/Vector2.h"

class CircleCollider2D
{
public:
	CircleCollider2D(Vector2* position, float radius, ZenObject* owner);
	bool CheckCollision(CircleCollider2D* otherCollider);
	bool HasCollision();

	std::function<void(CircleCollider2D*)> OnCollisionStart;
	ZenObject* GetOwner();
	void SetOwner(ZenObject* inOwner);
	void SetPosition(sf::Vector2f vector);

	sf::CircleShape circle;

private:
	Vector2* position;
	float radius;
	bool bIsColliding = false;
	ZenObject* owner;
};

