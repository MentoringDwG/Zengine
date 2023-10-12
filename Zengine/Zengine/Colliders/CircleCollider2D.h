// Copyright Z.Z. Zengine (c)

#pragma once

#include <functional>
#include "Collider.h"

struct Vector2;

class CircleCollider2D: public Collider
{
public:
	CircleCollider2D(Vector2 position, float radius, class ZenObject* owner, Collider::ColliderTags tag);

	bool CheckCircleCollision(CircleCollider2D* otherCollider);
	bool CheckBoxCollision(class BoxCollider2D* otherCollider);
	bool HasCollision();
	void SetPosition(sf::Vector2f vector);

	sf::CircleShape debugCircle;

private:
	float radius;
	bool bIsColliding = false;
	bool hasCollisionBefore = false;
	
	//check collision
	Vector2 testPoint = Vector2(0, 0);
};

