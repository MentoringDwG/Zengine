#pragma once

#include <functional>
#include <iostream>
#include "../ZenObject/ZenObject.h"
#include "../Structs/Vector2.h"
#include "../Colliders/CircleCollider2D.h"

class BoxCollider2D
{
public:
	BoxCollider2D(Vector2* position, Vector2* size, ZenObject* owner);
	bool CheckBoxCollision(BoxCollider2D* other);
	bool CheckCircleCollision(CircleCollider2D* other);
	bool HasCollision();
	ZenObject* GetOwner();
	void SetOwner(ZenObject* inOwner);
	void SetPosition(sf::Vector2f vector);

	std::function<void(BoxCollider2D*)> OnBoxCollisionStart;
	std::function<void(CircleCollider2D*)> OnCircleCollisionStart;

	sf::RectangleShape debugRectangleShape;

private:
	Vector2 position;
	Vector2 size;
	ZenObject* owner;
	bool bIsColliding = false;
};

