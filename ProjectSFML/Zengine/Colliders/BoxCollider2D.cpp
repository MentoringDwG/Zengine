#include "BoxCollider2D.h"

BoxCollider2D::BoxCollider2D(Vector2* position, Vector2* size, ZenObject* owner, Collider::ColliderTags tag) :Collider(tag)
{
	SetPosition(sf::Vector2f(position->x, position->y));
	this->size = size;
	SetOwner(owner);

	debugRectangleShape.setSize(sf::Vector2f(size->x, size->y));

	debugRectangleShape.setFillColor(sf::Color::Transparent);
	debugRectangleShape.setOutlineColor(sf::Color::Green);
	debugRectangleShape.setOutlineThickness(1);
}

bool BoxCollider2D::CheckBoxCollision(BoxCollider2D* other)
{
	if (other->debugRectangleShape.getGlobalBounds().intersects(debugRectangleShape.getGlobalBounds()))
	{
		bIsColliding=true;
	}
	else
	{
		bIsColliding=false;
	}

	if (HasCollision())
	{
		OnCollisionStart.Invoke(other);
	}
	else
	{
		OnCollisionEnd.Invoke(other);
	}

	return bIsColliding;
}

bool BoxCollider2D::HasCollision()
{
	return bIsColliding;
}

void BoxCollider2D::SetPosition(sf::Vector2f vector)
{
	debugRectangleShape.setPosition(vector);
	GetPosition()->x = vector.x;
	GetPosition()->y = vector.y;
}

Vector2* BoxCollider2D::GetSize()
{
	return size;
}