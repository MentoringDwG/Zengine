// Copyright Z.Z. Zengine (c)

#pragma once

#include <functional>
#include "Collider.h"

struct Vector2;

class BoxCollider2D: public Collider
{
public:
	BoxCollider2D(Vector2 position, Vector2 size, class ZenObject* owner, Collider::ColliderTags tag);

	bool CheckBoxCollision(BoxCollider2D* other);
	bool HasCollision();
	Vector2 GetSize();
	void SetPosition(sf::Vector2f vector);

	sf::RectangleShape debugRectangleShape;

private:
	Vector2 size = Vector2(0, 0);
	bool bIsColliding = false;
};

