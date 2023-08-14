#pragma once

#include <functional>
#include <iostream>
#include "Collider.h"
#include "../ZenObject/ZenObject.h"
#include "../Structs/Vector2.h"

class BoxCollider2D: public Collider
{
public:
	BoxCollider2D(Vector2* position, Vector2* size, ZenObject* owner, Collider::ColliderTags tag);
	bool CheckBoxCollision(BoxCollider2D* other);
	bool HasCollision();
	Vector2* GetSize();
	void SetPosition(sf::Vector2f vector);

	sf::RectangleShape debugRectangleShape;

private:
	Vector2* size;
	bool bIsColliding = false;
};

