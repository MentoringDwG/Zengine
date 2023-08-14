#pragma once

#include <functional>
#include <iostream>
#include "Collider.h"
#include "../ZenObject/ZenObject.h"
#include "../Structs/Vector2.h"
#include "../Colliders/BoxCollider2D.h"

class CircleCollider2D: public Collider
{
public:
	CircleCollider2D(Vector2* position, float radius, ZenObject* owner, Collider::ColliderTags tag);
	bool CheckCircleCollision(CircleCollider2D* otherCollider);
	bool CheckBoxCollision(BoxCollider2D* otherCollider);
	bool HasCollision();
	void SetPosition(sf::Vector2f vector);

	sf::CircleShape debugCircle;

private:
	float radius;
	bool bIsColliding = false;
	bool hasCollisionBefore = false;
	
	//check collision
	Vector2* testPoint = nullptr;
};

