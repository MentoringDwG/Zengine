#pragma once

#include <functional>
#include <iostream>
#include "../ZenObject/ZenObject.h"
#include "../Structs/Vector2.h"
#include "../Colliders/BoxCollider2D.h"

class CircleCollider2D
{
public:
	CircleCollider2D(Vector2* position, float radius, ZenObject* owner);
	bool CheckCircleCollision(CircleCollider2D* otherCollider);
	bool CheckBoxCollision(BoxCollider2D* otherCollider);
	bool HasCollision();
	ZenObject* GetOwner();
	void SetOwner(ZenObject* inOwner);
	void SetPosition(sf::Vector2f vector);

	std::function<void(CircleCollider2D*)> OnCircleCollisionStart;
	std::function<void(BoxCollider2D*)> OnBoxCollisionStart;

	sf::CircleShape debugCircle;

private:
	Vector2* position;
	ZenObject* owner;
	float radius;
	bool bIsColliding = false;
	
	//check collision
	Vector2* testPoint = nullptr;
};

