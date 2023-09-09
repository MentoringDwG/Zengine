#pragma once

#include <functional>
#include <iostream>
#include "Collider.h"

struct Vector2;

class CircleCollider2D: public Collider
{
public:
	CircleCollider2D(Vector2* position, float radius, class ZenObject* owner, Collider::ColliderTags tag);
	~CircleCollider2D();

	bool CheckCircleCollision(CircleCollider2D* otherCollider);
	bool CheckBoxCollision(class BoxCollider2D* otherCollider);
	bool HasCollision();
	void SetPosition(sf::Vector2f vector);

	sf::CircleShape debugCircle;

private:
	bool bIsColliding = false;
	bool hasCollisionBefore = false;
	float radius;
	
	//check collision
	Vector2* testPoint = nullptr;
};

